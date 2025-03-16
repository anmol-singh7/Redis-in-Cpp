#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <thread>
#include <stdexcept>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unordered_map>
#include "core/Validator.h"

#include "ClientHandler.h"

#define MAX_EVENTS 1024


using namespace std;

class Server {
private:
    int socket_fd;
    int epoll_fd;
    struct sockaddr_in server_addr;
    int port;
    ClientHandler clientHandler;

public:
    Server();
    ~Server();
    void init();
    void configureSocketOptions();
    void configureServerAddress();
    void bindServer();
    void listenServer();
    void setupEpoll();
    void startEventLoop();
    void cleanup();
    void setPort(int port);
};

#endif
