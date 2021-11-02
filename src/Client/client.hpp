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

const int BUFF_SIZE = 1024;

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

class Client {
private:
    std::shared_ptr<ssl::context> context_;
    std::shared_ptr<boost::asio::io_service> io_service_;
    std::shared_ptr<ssl_socket> socket_;
    std::shared_ptr<tcp::resolver> resolver_;
    Logger logger;
    const char *jsonRep;

    void onError(const std::string &log);
    void onAction(const std::string &log);
    const char *genFilename();
    int buildJson(const char *filename);


public:
    Client()
    {
        // Create a context that uses the default paths for
        // finding CA certificates.
        this->context_ = std::make_shared<ssl::context>(ssl::context::sslv23);
        this->context_->set_default_verify_paths();

        // Open a socket and connect it to the remote host.
        this->socket_ = std::make_shared<ssl_socket>(this->io_service_, *this->context_);
        tcp::resolver resolver(*this->io_service_);
        onAction("Client created.");
    }

    int connect();
    int send(Query &query);
    int receive();
    int disconnect();
};

