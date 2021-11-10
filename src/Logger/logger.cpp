#include "logger.hpp"

namespace nasapi
{
    enum LoggerStatus Logger::getStatus() {
        return this->status;
    }

    void Logger::setStatus(enum LoggerStatus newStatus) {
        this->status = newStatus;
    }

    void Logger::printLog(const std::string &log) {
        std::string color;
        std::string header = "[INFO]";
        std::string reset = "\033[0m";
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);

        if (this->status == OK)
            color = "\033[1;32m";
        else {
            color = "\033[1;31m";
            header = "[ERROR]";
        }

        std::stringstream ss;
        ss << color << header << "[" << std::put_time(&tm, "%a %b %d %H:%M:%S %Y") << "] " << reset << log << "\n";
        std::cout << ss.str();
    }
}



