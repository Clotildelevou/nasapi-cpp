#include "client.hpp"

int Client::connect() {

    if(::connect(this->socket_, reinterpret_cast<const sockaddr *>(&this->sin_), sizeof(this->sin_)) != -1)
    {
        std::stringstream ss;
        ss << "Connected to " << inet_ntoa(sin_.sin_addr) << " on the " << htons(sin_.sin_port) << " port.";
        onAction(ss.str());
        return 0;
    }
    else {
        onError("Connection failed");
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
