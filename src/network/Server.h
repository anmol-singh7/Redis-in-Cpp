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
#include <algorithm>
#include "core/Validator.h"
#include "core/CommandHandler.h"

#define MAX 1024
#define BUFFER_SIZE 1024
#define PING_PACKET_SIZE 1024

using namespace std;

class Server {
private:
    int socket_fd;
    int epoll_fd;
    struct sockaddr_in server_addr;
    int port;
    int numberOfReadyFDs;
    vector<int> monitoredFds; // For tracking clients (future improvement)

public:
    Server();
    ~Server(); // Destructor to clean up resources

    void init();
    void configureSocketOptions();
    void configureServerAddress();
    void bindServer();
    void listenServer();
    void setupEpoll();
    void removeClient(int fd);
    int acceptClient();
    void startEventLoop();
    void cleanup();
    void setPort(int port);
};

#endif
