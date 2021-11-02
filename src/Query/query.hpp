#pragma once

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

enum QueryType
{
    APOD,
    ANW,
    DONKI,
    EARTH,
    EONET,
    EPIC,
    EXOPLANET,
    GENELAB,
    INSIGHT,
    MRP,
    NIVL,
    TECHTRANS,
    SSC,
    SSDCNEOS,
    TECHPORT,
    VMMT
};

class Query {
private:
    std::string apiKey;
    enum QueryType type;
    std::string today;
    std::string query;

    void Apod(bool thumb, std::string date = "today");

    void Apod(std::string &startDate, std::string &endDate, bool thumb);

    void Apod(int count, bool thumb);

public:
    Query(std::string &apiKey, enum QueryType type):
            apiKey(apiKey),
            type(type)
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y");
        this->today = oss.str();

    }

};


