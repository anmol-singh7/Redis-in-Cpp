#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdexcept>
#include <sys/epoll.h>
#include <unordered_map>
#include "Client.h"
#include "core/CommandHandler.h"
using namespace std;

#define BUFFER_SIZE 1024

class ClientHandler{

    private:
    unordered_map<int, Client*> clients; 


    public:
        void addClient(int fd, sockaddr_in addr);

        int acceptClient(int socket_fd, int epoll_fd);

        bool processRequest(int fd);

        void removeClient(int socket_fd, int epoll_fd);

        void cleanupClients(int epoll_fd);

};

#endif