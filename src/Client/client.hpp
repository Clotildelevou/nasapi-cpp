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
#include <netdb.h>
#include <cstring>

#include "logger.hpp"

class Client {
private:
    int port_;
    struct hostent *host;
    sockaddr_in sin_;
    int socket_;
    Logger logger;

    void onError(const std::string &log);
    void onAction(const std::string &log);


public:
    Client()
    {
        this->port_ = 80;

        this->logger = Logger();

        this->host = gethostbyname("api.nasa.gov");
        if ( (host == nullptr) || (host->h_addr == nullptr) ) {
            onError("Error retrieving DNS information.");
            exit(1);
        }

        memcpy(&sin_.sin_addr, this->host->h_addr, this->host->h_length);
        this->sin_.sin_port = htons(this->port_);
        this->sin_.sin_family = AF_INET;

        this->socket_ = socket(AF_INET, SOCK_STREAM, 0);
        if (this->socket_ == -1)
        {
            onError("Error in socket creation.");
            exit(-1);
        }
        onAction("Client created.");
    }

    int connect();
};

