#pragma once

#include <filesystem>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
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


#include "json.h"

#include "logger.hpp"
#include "query.hpp"

const int BUFF_SIZE = 4096;

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

class Client {
private:
    Logger logger_;
    std::string header_;
    std::string jsonRep_;

    void onError(const std::string &log);
    void onAction(const std::string &log);
    int buildJson(const char *filename);
    int connect(ssl_socket &socket, tcp::resolver &resolver);
    int send(ssl_socket &socket, tcp::resolver &resolver, Query &query);
    int receive(ssl_socket &socket);
    int disconnect(ssl_socket &socket);


public:
    Client()
    {
        this->logger_ = Logger();
        onAction("Client created.");
    }

    int Apod(std::string &apiKey);
};

