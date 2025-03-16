#include "Server.h"
using namespace std;

void log(string msg) {
    cout << "[INFO]: " << msg << "\n";
}

void errorLog(string errorMsg) {
    cerr << "[ERROR]: " << errorMsg << "\n";
}

Server::Server() : socket_fd(-1), epoll_fd(-1) {}

Server::~Server() {
    log("Shutting down server...");
    
    if (socket_fd >= 0) close(socket_fd);
    if (epoll_fd >= 0) close(epoll_fd);

    for (int fd : monitoredFds) {
        close(fd);
    }

    log("Server shutdown complete.");
}

void Server::init() {
    try {
        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            throw runtime_error("Failed to create server socket: " + string(strerror(errno)));
        }
        log("Server socket created successfully");

        configureSocketOptions();
        configureServerAddress();
        bindServer();
        listenServer();
        setupEpoll();

    } catch (const exception &e) {
        errorLog(e.what());
        cleanup();
        exit(EXIT_FAILURE);
    }
}

void Server::setPort(int port){
    this->port = port ? port : 6379;
}

void Server::configureSocketOptions() {
    int reuse = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        throw runtime_error("setsockopt failed: " + string(strerror(errno)));
    }
    log("Socket option SO_REUSEADDR set successfully");
}

void Server::configureServerAddress() {
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
}

void Server::bindServer() {
    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        throw runtime_error("Failed to bind to port: " + to_string(port));
    }
    log("Server successfully bound to port: " + to_string(port));
}

void Server::listenServer() {
    int connection_backlog = 5;
    if (listen(socket_fd, connection_backlog) != 0) {
        throw runtime_error("Listen failed: " + string(strerror(errno)));
    }
    log("Server is listening for incoming connections");
}

void Server::setupEpoll() {
    epoll_fd = epoll_create1(0);
    if (epoll_fd < 0) {
        throw runtime_error("Failed to create epoll: " + string(strerror(errno)));
    }

    struct epoll_event ev{};
    ev.events = EPOLLIN;
    
    ev.data.fd = socket_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &ev) < 0) {
        throw runtime_error("Failed to add socket_fd to epoll: " + string(strerror(errno)));
    }

    log("Epoll setup complete.");
}

int handleClientRequest(int fd) {
    try {
        char buffer[BUFFER_SIZE];  
        std::memset(buffer, 0, sizeof(buffer)); // Clear buffer to avoid garbage data

        ssize_t bytesRead = recv(fd, buffer, sizeof(buffer) - 1, 0); // Leave space for null-terminator

        if (bytesRead <= 0) {
            if (bytesRead == 0) {
                log("Client FD " + std::to_string(fd) + " closed the connection.");
            } else {
                errorLog("Error receiving data from FD " + std::to_string(fd) + ": " + strerror(errno));
            }
            return -1;
        }

        buffer[bytesRead] = '\0'; // Null-terminate to safely handle as a string
        log("Data received from client FD " + std::to_string(fd) + ": " + buffer);

        CommandHandler cmdHandler;
        std::string response = cmdHandler.handleCommand(buffer, bytesRead); // Process command

        ssize_t bytesSent = send(fd, response.c_str(), response.size(), 0);
        if (bytesSent < 0) {
            errorLog("Failed to send response to FD " + std::to_string(fd) + ": " + strerror(errno));
            return -1;
        }

        log("Response sent to FD " + std::to_string(fd) + ": " + response);
        return 1;

    } catch (const std::exception& e) {
        errorLog("Exception in handleClientRequest for FD " + std::to_string(fd) + ": " + e.what());
        return -1;
    }
}

void Server::removeClient(int fd) {
    try {
        log("Removing FD " + to_string(fd) + " from epoll.");

        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
            errorLog("Failed to remove FD " + to_string(fd) + " from epoll: " + strerror(errno));
        }

        close(fd);
        monitoredFds.erase(remove(monitoredFds.begin(), monitoredFds.end(), fd), monitoredFds.end());

        log("Closed connection with client FD: " + to_string(fd));
    } catch (const exception &e) {
        errorLog("Exception during client cleanup: " + string(e.what()));
    }
}

int Server::acceptClient() {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    log("Waiting for a client to connect...");

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

    monitoredFds.push_back(client_fd);
    log("Client successfully added. FD: " + to_string(client_fd));

    return client_fd;
}

void Server::startEventLoop() {
    try {
        while (true) {
            struct epoll_event evlist[MAX];
            int numberOfReadyFDs = epoll_wait(epoll_fd, evlist, MAX, -1);

            if (numberOfReadyFDs < 0) {
                throw runtime_error("Error occurred during epoll wait: " + string(strerror(errno)));
            }

            for (int i = 0; i < numberOfReadyFDs; i++) {
                int fd = evlist[i].data.fd;

                try {
                    if (fd == socket_fd) {
                        acceptClient();
                    }
                    else {
                        int res = handleClientRequest(fd);
                        if (res <= 0) removeClient(fd);
                    }
                } catch (const exception &e) {
                    errorLog("Exception in event handling for FD " + to_string(fd) + ": " + e.what());
                    removeClient(fd);
                }
            }
        }
    } catch (const exception &e) {
        errorLog("Critical error in event loop: " + string(e.what()));
    }
}

void Server::cleanup() {
    if (socket_fd >= 0) close(socket_fd);
    if (epoll_fd >= 0) close(epoll_fd);
    for (int fd : monitoredFds) {
        close(fd);
    }
}

