#include <iostream>
#include<bits/stdc++.h>
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
#include <sys/epoll.h>
#include <fcntl.h>
#include "core/Validator.h"
#include "core/CommandHandler.h"
using namespace std;

#define MAX 1024
#define BUFFERSIZ 1024

void log(string msg){
   std::cout<<msg + "\n";
   return;
}

void errorLog(string errorMsg){
    std::cerr << errorMsg + "\n";
    return;
}

int handlePingReq(int client_fd) {
  try{
    char buffer[BUFFERSIZ];
    CommandHandler cmdHandler;

    std::memset(buffer, 0, sizeof(buffer));
    int n = read(client_fd, buffer, BUFFERSIZ - 1);

    if (n <= 0) {
        errorLog("Client disconnected: FD " + to_string(client_fd) + " n is:" + to_string(n));
        return n;
    }

    log("Data received from client Fd: " + to_string(client_fd));

    buffer[n] = '\0'; // Null-terminate the string
    
    string response = cmdHandler.handleCommand(buffer,n);

    write(client_fd, response.c_str(), response.size());
   
  }
  catch(const exception& e){
    cerr << "Error :" << e.what() << endl;
    return 1;
  }
  
  return 1;
}

int main(int argc, char **argv) {
  // Flush after every std::cout / std::cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  int ret;
  int epoll_fd;
  struct epoll_event ev;
  struct epoll_event evlist[MAX];

  int numberOfReadyFDs;

  vector<int> moniteredFds;
  
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
   errorLog("Failed to create server socket");
   return 1;
  }
  
  // Since the tester restarts your program quite often, setting SO_REUSEADDR
  // ensures that we don't run into 'Address already in use' errors
  int reuse = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
    errorLog("setsockopt failed");
    return 1;
  }
  
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(6379);
  
  if (bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
    errorLog("Failed to bind to port 6379");
    return 1;
  }
  
  int connection_backlog = 5;
  if (listen(socket_fd, connection_backlog) != 0) {
    errorLog("listen failed");
    return 1;
  }
  
  
  log("Logs from your program will appear here!");
  
  epoll_fd = epoll_create1(0);

  if(epoll_fd < 0 ){
    errorLog("error while creating epoll");
    return 1;
  }
  
  ev.events = EPOLLIN;
  ev.data.fd = STDIN_FILENO;

  ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &ev);

  if(ret < 0 ){
    errorLog("Error while adding STDIN_FILENO to epoll");
    return 1;
  }

  ev.data.fd = socket_fd;
  ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, socket_fd, &ev);

  if(ret < 0 ){
    errorLog("Error while adding socket fd to epoll");
    close(socket_fd);
    return 1;
  }


  while(true){

    numberOfReadyFDs = epoll_wait(epoll_fd, evlist,MAX, -1 );

    if(numberOfReadyFDs < 0){
      errorLog("Error occured during epoll wait");
      break;
    }

    for(int i = 0; i<numberOfReadyFDs; i++){

      struct epoll_event epv = evlist[i];

      if(epv.data.fd == STDIN_FILENO){
         char buff[BUFFERSIZ];
         fgets(buff, BUFFERSIZ-1,stdin);

         if(!strcmp(buff,"quit") || !strcmp(buff,"exit")){
            close(socket_fd);
            return 1;
         }
      }
      if(epv.data.fd == socket_fd){
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);

            log("Waiting for a client to connect...");

            int client_fd = accept(socket_fd, (struct sockaddr *) &client_addr, (socklen_t *) &client_addr_len);
            
            if(client_fd < 0 ) {
                errorLog("Failed to accept client connection");
                continue;
            }

            struct epoll_event cev;

            cev.events = EPOLLIN;
            cev.data.fd = client_fd;
            ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &cev);

            if(ret < 0) {
              errorLog("Error while adding client fd to epoll");
              continue;
            }

            log("Client successfully added client FD: " + to_string(client_fd));
      }
      else{
          int client_fd = epv.data.fd;
          int res =  handlePingReq(client_fd);

          if (res <= 0) {
            close(client_fd);
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, client_fd, &evlist[i]);
          }
      }

    }
    
  }

  close(socket_fd);

  return 0;
}
