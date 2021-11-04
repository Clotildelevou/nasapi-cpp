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

/*!\class The client class which sends the API request */

class Client {
private:
    Logger logger_;  //! Logger
                      /*!< Logger used by client, prints on std::cout */
    std::string header_;  //! String
                        /*!< String containing the header of the response */

    std::string jsonRep_;  //! String
                        /*!< String containing the json response */

    void onError(const std::string &log);
    void onAction(const std::string &log);

    int buildJson(const char *filename);

    int connect(ssl_socket &socket, tcp::resolver &resolver);
    int send(ssl_socket &socket, tcp::resolver &resolver, Query &query);
    int receive(ssl_socket &socket);
    int disconnect(ssl_socket &socket);

public:
    //! Constructor.
    /*!< Only initializes the logger */
    Client()
    {
        this->logger_ = Logger();
        onAction("Client created.");
    }

    //! Calls APOD API without args. Calls APOD on today's date.
    /*!
      \param apiKey an std::string argument.
    */
    void Apod(std::string &apiKey);

    //! Calls APOD API for a specific date
    /*!
      \param apiKey an std::string argument.
      \param thumb a boolean.
      \param date a const std::string argument with YYYY-MM-DD format.
    */
    void Apod(std::string &apiKey, bool thumb, const std::string &date);

    //! Calls APOD API for all days between startDate end endDate
    /*!
      \param apiKey an std::string argument.
      \param thumb a boolean.
      \param startDate a const std::string argument with YYYY-MM-DD format.
      \param endDate a const std::string argument with YYYY-MM-DD format.
    */
    void Apod(std::string &apiKey, bool thumb, const std::string &startDate, const std::string &endDate);
};

