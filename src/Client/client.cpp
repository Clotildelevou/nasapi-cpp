#include "client.hpp"

int Client::connect() {
    try {
        tcp::resolver::query query("api.nasa.gov", "https");
        boost::asio::connect(this->socket_->lowest_layer(), this->resolver_->resolve(query));
        this->socket_->set_verify_mode(ssl::verify_peer);
        this->socket_->set_verify_callback(ssl::rfc2818_verification("api.nasa.gov"));
        this->socket_->handshake(ssl_socket::client);

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
    this->logger.setStatus(ERROR);
    this->logger.printLog(log);
    this->logger.setStatus(OK);
}

void Client::onAction(const std::string &log) {
    this->logger.printLog(log);
}


int Client::disconnect() {
    boost::system::error_code error;
    this->socket_->lowest_layer().close(error);

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

int Client::send(Query &query) {
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(query.getQuery()),error);

    if(error) {
        std::stringstream ss;
        ss << "Couldn't send request: "
           << error.message();
        onError(ss.str());
        return -1;
    }
    else {
        std::stringstream ss;
        ss << "Request sent : \n"
           << query.getQuery();
        onAction(ss.str());
        return 0;
    }
}

int Client::receive() {

    boost::system::error_code error;
    boost::asio::streambuf receive_buffer;


    boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
    if( error && error != boost::asio::error::eof ) {
        onError("Error in response reception.");
        return -1;
    }
    else
    {
        std::stringstream ss;
        ss << boost::asio::buffer_cast<const char*>(receive_buffer.data());

        const char *filename = genFilename();
        this->jsonRep = ss.str().c_str();
        onAction("Response received.");

        buildJson(filename);
        ss.clear();
        ss << "JSON file " << filename << " successfully received.";
        onAction(ss.str());
        return 0;
    }
}

const char *Client::genFilename() {
    int id_file = 1;
    std::string filename = "nasapi-cpp";
    while (std::filesystem::exists(filename + std::to_string(id_file)))
        id_file++;
    filename.append(std::to_string(id_file));
    const char *res = filename.c_str();
    return res;
}

int Client::buildJson(const char *filename) {
    json_object *root = json_tokener_parse(this->jsonRep);
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


