#include "ClientHandler.h"

void log(string msg){
    cout<<"[INFO] : "+ msg + "\n";
}

void errorLog(string msg){
    cout<<"[ERROR] : "+ msg + "\n";
}



int ClientHandler::acceptClient(int socket_fd, int epoll_fd){
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    cout<<"Waiting for a client to connect...";

    int client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    if (client_fd < 0) {
        throw runtime_error("Failed to accept client connection: " + string(strerror(errno)));
    }

    struct epoll_event cev{};
    cev.events = EPOLLIN;
    cev.data.fd = client_fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &cev) < 0) {
        close(client_fd);
        throw runtime_error("Failed to add client fd to epoll: " + string(strerror(errno)));
    }

    addClient(client_fd,client_addr);
    // log("Client successfully added. FD: " + to_string(client_fd));

    return client_fd;
}

bool ClientHandler::processRequest(int fd) {
    try {
        char buffer[BUFFER_SIZE];
        std::memset(buffer, 0, sizeof(buffer));

        ssize_t bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            if (bytesRead == 0) {
                log("Client FD " + std::to_string(fd) + " disconnected.");
            } else {
                errorLog("Error receiving data from FD " + std::to_string(fd) + ": " + strerror(errno));
            }
            
            return false;
        }

        buffer[bytesRead] = '\0';
        log("Received from FD " + std::to_string(fd) + ": " + buffer);

        clients[fd]->updateActivity();  // Update last active time

        std::string response = CommandHandler::handleCommand(buffer, bytesRead);

        ssize_t bytesSent = send(fd, response.c_str(), response.size(), 0);
        if (bytesSent < 0) {
            errorLog("Failed to send response to FD " + std::to_string(fd) + ": " + strerror(errno));
            
            return false;
        }

        log("Response sent to FD " + std::to_string(fd));
        return true;
    } catch (const std::exception& e) {
        errorLog("Exception in processRequest for FD " + std::to_string(fd) + ": " + e.what());
        return false;
    }
}

void ClientHandler::addClient(int fd, struct sockaddr_in addr) {
    if (clients.find(fd) == clients.end()) {
        clients[fd] = new Client(fd, addr);
        cout<<"Client added: FD " + std::to_string(fd) +
            " IP: " + clients[fd]->getIpAddress() +
            " Port: " + std::to_string(clients[fd]->getPort());
    }
}

void ClientHandler::removeClient(int fd, int epoll_fd) {
    try {
        if (clients.find(fd) == clients.end()) {
            log("Attempted to remove non-existent client FD: " + std::to_string(fd));
            return;
        }

        log("Removing client FD: " + std::to_string(fd));

        // Remove from epoll
        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
            errorLog("Failed to remove FD " + std::to_string(fd) + " from epoll: " + strerror(errno));
        }

        // Close the socket
        close(fd);

        // Remove from the clients map
        delete clients[fd];  // Free allocated memory
        clients.erase(fd);

        log("Client FD " + std::to_string(fd) + " successfully removed.");
    } catch (const std::exception &e) {
        errorLog("Exception while removing client FD " + std::to_string(fd) + ": " + std::string(e.what()));
    }
}


void ClientHandler::cleanupClients(int epoll_fd) {
    log("Cleaning up all client connections...");

    for (auto it = clients.begin(); it != clients.end(); ) {
        int fd = it->first;

        // Remove from epoll
        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
            errorLog("Failed to remove FD " + std::to_string(fd) + " from epoll: " + strerror(errno));
        }

        // Close the socket
        close(fd);

        // Free allocated memory and erase from the map
        delete it->second;
        it = clients.erase(it);  // Use iterator returned by erase() to safely continue iteration
    }

    log("All clients cleaned up successfully.");
}


