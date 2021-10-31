#include "client.hpp"

int Client::connect() {

    if(::connect(this->socket_, reinterpret_cast<const sockaddr *>(&this->sin_), sizeof(this->sin_)) != -1)
    {
        std::stringstream ss;
        ss << "Connection to " << inet_ntoa(sin_.sin_addr) << " on the " << htons(sin_.sin_port) << " port.";
        this->logger.printLog(ss.str());
        return 0;
    }
    else {
        this->logger.setStatus(ERROR);
        this->logger.printLog("Connection failed");
        this->logger.setStatus(OK);
        return -1;
    }
}
