#pragma once

#include <filesystem>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <netdb.h>
#include <cstring>
#include <fstream>
#include <string>


#include "json.h"

#include "logger.hpp"
#include "query.hpp"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace nasapi
{
    class Client {
    private:
        Logger logger_;
        std::string header_;
        std::string jsonRep_;

        void onError(const std::string &log);
        void onAction(const std::string &log);

        int buildJson();
        int buildHeader();

        int connect(ssl_socket &socket, tcp::resolver &resolver);
        int send(ssl_socket &socket, tcp::resolver &resolver, Query &query);
        int receive(ssl_socket &socket);
        int disconnect(ssl_socket &socket);

        void queryLaunch(ssl_socket &socket, tcp::resolver &resolver, Query &query);

    public:
        Client()
        {
            this->logger_ = Logger();
            onAction("Client created.");
        }

        void Apod(std::string &apiKey);

        void Apod(std::string &apiKey, bool thumb, const std::string &date);

        void Apod(std::string &apiKey, bool thumb, const std::string &startDate, const std::string &endDate);

        void Apod(std::string &apiKey, bool thumb, int count);

        void NeoFeed(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void NeoLookup(std::string &apiKey, int asteroidId);

        void NeoBrowse(std::string &apiKey);
    };
}


