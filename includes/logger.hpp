#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

namespace nasapi
{
    enum LoggerStatus
    {
        ERROR,
        OK
    };

    class Logger {
    private:
        enum LoggerStatus status;

    public:

        Logger():
                status(OK)
        {}

        enum LoggerStatus getStatus();

        void setStatus(enum LoggerStatus newStatus);

        void printLog(const std::string &log);
    };
}



