#pragma once

#include <string>
#include <sstream>

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

    std::string buildApod(bool thumb, std::string date = "today", bool conceptTags = false, bool hd = true);
    std::string buildApod(std::string startDate, std::string endDate, bool thumb, bool conceptTags = false, bool hd = true);
    std::string buildApod(int count, bool thumb, bool conceptTags = false, bool hd = true);

public:

};


