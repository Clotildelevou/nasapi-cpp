#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>

#include "logger.hpp"

class Client {
private:
    int port_;
    std::string ip_;
    sockaddr_in sin_;
    int socket_;
    Logger logger;


public:
    Client(std::string &ip, int port)
    {
        this->port_ = port;

        this->ip_ = ip;

        this->logger = Logger();

        this->sin_.sin_addr.s_addr = inet_addr(this->ip_.c_str());
        this->sin_.sin_port = htons(this->port_);
        this->sin_.sin_family = AF_INET;

        this->socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (this->socket_ == -1)
        {
            perror("Error in socket creation :");
            exit(-1);
        }
    }

    int connect();
};


