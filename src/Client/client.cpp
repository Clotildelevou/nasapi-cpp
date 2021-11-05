#include <fstream>
#include "../../includes/client.hpp"

int Client::connect(ssl_socket &socket, tcp::resolver &resolver) {
    try {
        tcp::resolver::query query("api.nasa.gov", "https");
        boost::asio::connect(socket.lowest_layer(), resolver.resolve(query));
        socket.set_verify_mode(ssl::verify_peer);
        socket.set_verify_callback(ssl::rfc2818_verification("api.nasa.gov"));
        socket.handshake(ssl_socket::client);

        std::stringstream ss;
        ss << "Client connected using TLS protocol.";
        onAction(ss.str());
        return 0;
    }
    catch (std::exception &e) {
        onError(e.what());
        return -1;
    }
}

void Client::onError(const std::string &log) {
    this->logger_.setStatus(ERROR);
    this->logger_.printLog(log);
    this->logger_.setStatus(OK);
}

void Client::onAction(const std::string &log) {
    this->logger_.printLog(log);
}

int Client::disconnect(ssl_socket &socket) {
    boost::system::error_code error;
    socket.lowest_layer().close(error);

    if(error) {
        std::stringstream ss;
        ss << "Couldn't close connection: "
           << error.message();
        onError(ss.str());
        return -1;
    }
    else
    {
        onAction("Connection closed.");
        return 0;
    }
}

int Client::send(ssl_socket &socket, tcp::resolver &resolver, Query &query) {

    std::stringstream ss;
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(query.getQuery()),error);
    if(error) {
        ss.str(std::string());
        ss << "Couldn't send request: "
           << error.message();
        onError(ss.str());
        return -1;
    }
    else {
        ss.str(std::string());
        ss << "Request sent.";
        onAction(ss.str());
    }
    return 0;
}

int Client::receive(ssl_socket &socket) {

    boost::system::error_code error;
    char data[BUFF_SIZE];
    auto buf = boost::asio::buffer(data, BUFF_SIZE);

    boost::asio::read(socket, boost::asio::buffer(data, BUFF_SIZE), boost::asio::transfer_at_least(1));
    if(error && error != boost::asio::error::eof) { //Error handling
        onError("Error in response reception.");
        return -1;
    }
    else // will build the JSON file response
    {
        this->jsonRep_ = reinterpret_cast<const char *>(boost::asio::buffer_cast<unsigned char *>(buf));
        size_t start = this->jsonRep_.find('{');
        this->header_ = this->jsonRep_.substr(0, start);

        this->jsonRep_.erase(0, start);
        onAction("Response received.");

        char filename[16] = "nasapi-cpp.json";
        if (buildJson(filename) == 0)
        {
            std::stringstream ss;
            ss.str(std::string());
            ss << "JSON file " << filename << " successfully received.";
            onAction(ss.str());
        }
        else
        {
            onError("Error in JSON creation");
            return -1;
        }

        std::ofstream hfile("nasapi-cpp-header.txt");
        if (hfile)
        {
            hfile << this->header_;
            onAction("Corresponding header file created\n");
        }
        else
        {
            onError("Couldn't create corresponding header file.");
            return -1;
        }

    }
    return 0;
}

int Client::buildJson(const char *filename) {
    json_object *root = json_tokener_parse(this->jsonRep_.c_str());
    if (!root) {
        onError("Couldn't parse response.");
        printf("The json object to string:\n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
        if (json_object_put(root) != 1)
        {
            onError("Couldn't free the JSON object.");
            return -1;
        }
        return -1;
    }
    if(json_object_to_file(filename, root) == -1)
    {
        onError("Couldn't build JSON file.");
        if (json_object_put(root) != 1)
        {
            onError("Couldn't free the JSON object.");
            return -1;
        }
        return -1;
    }
    else
    {
        onAction("Response file created.");
    }
    if (json_object_put(root) != 1)
    {
        onError("Couldn't free the JSON object.");
        return -1;
    }
    return 0;
}

void Client::Apod(std::string &apiKey) {
    // Create a context that uses the default paths for
    // finding CA certificates.
    ssl::context context(ssl::context::sslv23);
    context.set_default_verify_paths();
    boost::asio::io_service io_service;
    ssl_socket socket(io_service, context);
    tcp::resolver resolver(io_service);

    Query query(apiKey, APOD);
    query.Apod();

    if (connect(socket, resolver) == -1)
    {
        onError("Couldn't make connection");
        exit(-1);
    }

    if (send(socket, resolver, query) == -1)
    {
        onError("send");
        exit(-1);
    }

    if(receive(socket) == -1)
    {
        onError("recv");
        exit(-1);
    }

    if (disconnect(socket) == -1)
    {
        onError("disconnect");
        exit(-1);
    }

    onAction("APOD written.");
    exit(-1);
}

void Client::Apod(std::string &apiKey, bool thumb, const std::string &date) {
    // Create a context that uses the default paths for
    // finding CA certificates.
    ssl::context context(ssl::context::sslv23);
    context.set_default_verify_paths();
    boost::asio::io_service io_service;
    ssl_socket socket(io_service, context);
    tcp::resolver resolver(io_service);

    Query query(apiKey, APOD);
    query.Apod(date, thumb);

    if (connect(socket, resolver) == -1)
    {
        onError("Couldn't make connection");
        exit(-1);
    }

    if (send(socket, resolver, query) == -1)
    {
        onError("send");
        exit(-1);
    }

    if(receive(socket) == -1)
    {
        onError("recv");
        exit(-1);
    }

    if (disconnect(socket) == -1)
    {
        onError("disconnect");
        exit(-1);
    }

    onAction("APOD written.");
    exit(-1);
}

void Client::Apod(std::string &apiKey, bool thumb, const std::string &startDate, const std::string &endDate) {
    // Create a context that uses the default paths for
    // finding CA certificates.
    ssl::context context(ssl::context::sslv23);
    context.set_default_verify_paths();
    boost::asio::io_service io_service;
    ssl_socket socket(io_service, context);
    tcp::resolver resolver(io_service);

    Query query(apiKey, APOD);
    query.Apod(startDate, endDate, thumb);

    if (connect(socket, resolver) == -1)
    {
        onError("Couldn't make connection");
        exit(-1);
    }

    if (send(socket, resolver, query) == -1)
    {
        onError("send");
        exit(-1);
    }

    if(receive(socket) == -1)
    {
        onError("recv");
        exit(-1);
    }

    if (disconnect(socket) == -1)
    {
        onError("disconnect");
        exit(-1);
    }

    onAction("APOD written.");
    exit(-1);
}