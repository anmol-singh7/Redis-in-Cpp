/* Server.cpp */
#include "Server.h"

Server::Server() : socket_fd(-1), epoll_fd(-1), port(8080) {}

Server::~Server() {
    cleanup();
}

void Server::init() {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        throw runtime_error("Failed to create socket");
    }
    configureSocketOptions();
    configureServerAddress();
    bindServer();
    listenServer();
    setupEpoll();
}

void Server::configureSocketOptions() {
    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        throw runtime_error("Failed to set socket options");
    }
}

void Server::configureServerAddress() {
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
}

void Server::bindServer() {
    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        throw runtime_error("Failed to bind socket");
    }
}

void Server::listenServer() {
    if (listen(socket_fd, SOMAXCONN) == -1) {
        throw runtime_error("Failed to listen on socket");
    }
}

void Server::setupEpoll() {
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        throw runtime_error("Failed to create epoll instance");
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = socket_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &event) == -1) {
        throw runtime_error("Failed to add server socket to epoll");
    }
}

void Server::startEventLoop() {
    struct epoll_event events[MAX_EVENTS];
    while (true) {
        int num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            cerr << "epoll_wait failed" << endl;
            break;
        }

        for (int i = 0; i < num_events; i++) {
            int fd = events[i].data.fd;

            if (fd == socket_fd) {
                clientHandler.acceptClient(socket_fd, epoll_fd);
            } else {
                if (!clientHandler.processRequest(fd)) {
                    clientHandler.removeClient(fd, epoll_fd);
                }
            }
        }
    }
}

void Server::cleanup() {
    clientHandler.cleanupClients(epoll_fd);
    if (socket_fd != -1) close(socket_fd);
    if (epoll_fd != -1) close(epoll_fd);
 
}

void Server::setPort(int port) {
    this->port = port;
}
