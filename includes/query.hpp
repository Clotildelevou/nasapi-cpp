#pragma once

#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

namespace nasapi
{
    class Query {
    private:
        std::string apiKey;
        std::string query;

    public:
        Query(std::string &apiKey):
                apiKey(apiKey)
        {}

        void Apod(const std::string& date = "today", bool thumb = true);

        void Apod(const std::string &startDate, const std::string &endDate, bool thumb);

        void Apod(int count, bool thumb);

        void NeoFeed(const std::string &startDate, const std::string &endDate);

        void NeoLookup(int asteroidId);

        void NeoBrowse();

        const std::string &getQuery();

    };
}



