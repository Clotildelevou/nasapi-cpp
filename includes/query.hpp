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

        const std::string &getQuery();

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

        void DonkiCME(const std::string &startDate, const std::string &endDate);

        void DonkiCMEAnalysis(const std::string &startDate, const std::string &endDate, bool mostAccurateOnly,
                              bool completeEntryOnly, int speed, int halfAngle, const std::string &catalog,
                              const std::string &keyword);

        void DonkiGST(const std::string &startDate, const std::string &endDate);

        void DonkiIPS(const std::string &startDate, const std::string &endDate, const std::string &location,
                      const std::string &catalog);

        void DonkiFLR(const std::string &startDate, const std::string &endDate);

        void DonkiSEP(const std::string &startDate, const std::string &endDate);

        void DonkiMPC(const std::string &startDate, const std::string &endDate);

        void DonkiRBE(const std::string &startDate, const std::string &endDate);

        void DonkiHSS(const std::string &startDate, const std::string &endDate);

        void DonkiWSA(const std::string &startDate, const std::string &endDate);
    };
}



