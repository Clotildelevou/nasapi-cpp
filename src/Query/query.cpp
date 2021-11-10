#include "query.hpp"

namespace nasapi
{
    const std::string &Query::getQuery() {
        return this->query;
    }

    void Query::Apod(const std::string& date, bool thumb) {
        std::stringstream ss;
        ss << "GET /planetary/apod?api_key=" << this->apiKey;

        if (date != "today")
            ss << "&date=" << date;

        if (thumb)
            ss << "&thumbs=true";

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";
        this->query = ss.str();
    }

    void Query::Apod(const std::string &startDate, const std::string &endDate, bool thumb) {
        std::stringstream ss;

        ss << "GET /planetary/apod?api_key=" << this->apiKey
           << "&start_date=" << startDate
           << "&end_date=" << endDate;

        if (thumb)
            ss << "&thumbs=true";

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::Apod(int count, bool thumb) {
        std::stringstream ss;

        ss << "GET /planetary/apod?api_key=" << this->apiKey
           << "&count=" << count
           << " HTTP/1.0\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";
        this->query = ss.str();
    }

    void Query::NeoFeed(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /neo/rest/v1/feed?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::NeoLookup(int asteroidId) {
        std::stringstream ss;

        ss << "GET /neo/rest/v1/neo/"
           << asteroidId << "?"
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";
        this->query = ss.str();
    }

    void Query::NeoBrowse() {
        std::stringstream ss;

        ss << "GET /neo/rest/v1/neo/browse/?"
           << "api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiCME(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/CME?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiCMEAnalysis(const std::string &startDate, const std::string &endDate, bool mostAccurateOnly = true,
                                 bool completeEntryOnly = true, int speed = 0, int halfAngle = 0,
                                 const std::string& catalog = "ALL", const std::string& keyword = "NONE") {
        std::stringstream ss;

        ss << "GET /DONKI/CMEAnalysis?"
           << "start_date=" << startDate
           << "&end_date=" << endDate;

        if (!mostAccurateOnly)
            ss << "&mostAccurateOnly=false";
        if (!completeEntryOnly)
            ss << "&completeEntryOnly=false";
        if (speed != 0)
            ss << "&speed=" << speed;
        if (halfAngle != 0)
            ss << "&halfAngle=" << halfAngle;
        if (catalog != "ALL")
            ss << "&catalog=" << catalog;
        if (keyword != "NONE")
            ss << "&keyword=" << keyword;

        ss << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiGST(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/GST?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiIPS(const std::string &startDate, const std::string &endDate, const std::string& location = "ALL",
                         const std::string& catalog = "ALL") {
        std::stringstream ss;

        ss << "GET /DONKI/IPS?"
           << "start_date=" << startDate
           << "&end_date=" << endDate;

        if (location != "ALL")
            ss << "&location=" << location;

        if (catalog != "ALL")
            ss << "&catalog=" << catalog;

        ss << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiFLR(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/FLR?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiSEP(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/SEP?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiMPC(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/MPC?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiRBE(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/RBE?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiHSS(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/HSS?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::DonkiWSA(const std::string &startDate, const std::string &endDate) {
        std::stringstream ss;

        ss << "GET /DONKI/WSAEnlilSimulation?"
           << "start_date=" << startDate
           << "&end_date=" << endDate
           << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }
}
