#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
using namespace std;

class Client{

    public:
    int fd;
    struct sockaddr_in client_addr;
    time_t lastActive;

    Client(int fd, struct sockaddr_in addr) : fd(fd), client_addr(addr), lastActive(time(nullptr)) {}

    void updateActivity() { 
        lastActive = time(nullptr); 
    }

    std::string getIpAddress() const {
        return inet_ntoa(client_addr.sin_addr);
    }

    int getPort() const {
        return ntohs(client_addr.sin_port);
    }

};

#endif