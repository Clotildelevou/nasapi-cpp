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
    std::string query;

public:
    Query(std::string &apiKey, enum QueryType type):
            apiKey(apiKey),
            type(type)
    {}

    void Apod(bool thumb, const std::string& date = "today");

    void Apod(const std::string &startDate, const std::string &endDate, bool thumb);

    void Apod(int count, bool thumb);

    const std::string &getQuery();

};


