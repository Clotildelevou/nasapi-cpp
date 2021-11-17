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
           << "&count=" << count;
        if (!thumb)
            ss << "&thumb=false";

        ss << " HTTP/1.0\r\n"
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


    void Query::EarthImagery(float lat, float lon, float dim = 0.25, const std::string& date = "today")
    {
        std::stringstream ss;

        ss << "GET /planetary/earth/imagery?"
           << "lat=" << lat
           << "&lon=" << lon;
        if (dim != 0.25)
            ss << "&dim=" << dim;
        if (date != "today")
            ss << "&date=" << date;

        ss << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EarthAssets(float lat, float lon, const std::string& date, float dim = 0.25)
    {
        std::stringstream ss;

        ss << "GET /planetary/earth/assets?"
           << "lat=" << lat
           << "&lon=" << lon
           << "&date=" << date;

        if (dim != 0.25)
            ss << "&dim=" << dim;

        ss << "&api_key=" << this->apiKey;

        ss << " HTTP/1.1\r\n"
           << "Host: api.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }


    void Query::EonetEvents(const std::string& source = "", const std::string& status = "", int limit = 0, int days = 0)
    {
        std::stringstream ss;

        ss << "GET /api/v2.1/events?";

        if (!source.empty())
            ss << "&source=" << source;
        if (!status.empty())
            ss << "&status=" << status;
        if (limit != 0)
            ss << "&limit=" << limit;
        if (days != 0)
            ss << "&days=" << days;

        ss << " HTTP/1.1\r\n"
           << "Host: eonet.sci.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EonetCategories(int categoryID, const std::string& source = "", const std::string& status = "", int limit = 0, int days = 0)
    {
        std::stringstream ss;

        ss << "GET /api/v2.1/categories/" << categoryID << "?";

        if (!source.empty())
            ss << "&source=" << source;
        if (!status.empty())
            ss << "&status=" << status;
        if (limit != 0)
            ss << "&limit=" << limit;
        if (days != 0)
            ss << "&days=" << days;

        ss << " HTTP/1.1\r\n"
           << "Host: eonet.sci.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EonetLayers(int categoryID)
    {
        std::stringstream ss;

        ss << "GET /api/v2.1/layers/"
        << categoryID;

        ss << " HTTP/1.1\r\n"
           << "Host: eonet.sci.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }


    void Query::EpicNatural()
    {
        std::stringstream ss;

        ss << "GET /api/natural/";
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicNaturalDate(const std::string& naturalDate)
    {
        std::stringstream ss;

        ss << "GET /api/natural/date/" << naturalDate;
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicNaturalAll()
    {
        std::stringstream ss;

        ss << "GET /api/natural/all";
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicNaturalAvailable()
    {
        std::stringstream ss;

        ss << "GET /api/natural/available";
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicEnhanced()
    {
        std::stringstream ss;

        ss << "GET /api/enhanced";
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicEnhancedDate(const std::string &date)
    {
        std::stringstream ss;

        ss << "GET /api/enhanced/" << date;
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicEnhancedAll()
    {
        std::stringstream ss;

        ss << "GET /api/enhanced/all";
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicEnhancedAvailable()
    {
        std::stringstream ss;

        ss << "GET /api/enhanced/available";
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::EpicArchive(const std::string &collection, const std::string &year, const std::string &month,
                            const std::string &day, const std::string &imageType, const std::string &filename)
    {
        std::stringstream ss;

        ss << "GET /api/archive/"
        << collection << "/" << year << "/" << month << "/" << day << "/" << imageType << "/" << filename;
        ss << " HTTP/1.1\r\n"
           << "Host: epic.gsfc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }


    void Query::Exoplanet(const std::string &table, const std::string &select, const std::string &count,
                          const std::string &where, const std::string &order, int ra = 0, int dec = 0,
                          const std::string &radius = "", const std::string &format = "")
    {
        std::stringstream ss;

        ss << "GET /nstedAPI/nph-nstedAPI?";
        if (!table.empty())
            ss << "&table=" << table;
        if (!select.empty())
            ss << "&select=" << select;
        if (!count.empty())
            ss << "&count=" << count;
        if (!where.empty())
            ss << "&where=" << where;
        if (!order.empty())
            ss << "&order=" << order;
        if (ra != 0)
            ss << "&ra=" << ra;
        if (dec != 0)
            ss << "&dec=" << dec;
        if (!radius.empty())
            ss << "&radius=" << radius;
        if (!format.empty())
            ss << "&format=" << format;

        ss << " HTTP/1.1\r\n"
           << "Host: exoplanetarchive.ipac.caltech.edu"
           << "\r\n\r\n";;
        this->query = ss.str();
    }


    void Query::GeneLabData(const std::string& gldsStudyId, int pageNum = 0, int resultsPPage = 0)
    {
        std::stringstream ss;

        ss << "GET /genelab/data/glds/files/" << gldsStudyId << "/?";

        if (pageNum != 0)
            ss << "page=" << pageNum;
        if (resultsPPage != 0)
            ss << "&size=" << resultsPPage;

        ss << " HTTP/1.1\r\n"
           << "Host: genelab-data.ndc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::GeneLabMeta(int gldsStudyId)
    {
        std::stringstream ss;

        ss << "GET /genelab/data/glds/meta/" << gldsStudyId << "/?";

        ss << " HTTP/1.1\r\n"
           << "Host: genelab-data.ndc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::GeneLabSearchJSON(const std::string &term, int from, int size, const std::string &datasource,
                              const std::string &field, const std::string &order = "", const std::string &ffield = "",
                              const std::string &fvalue = "")
    {
        std::stringstream ss;

        ss << "GET /genelab/data/glds/search?term=" << term
        << "&from=" << from << "&type=" << datasource;

        if (!order.empty())
            ss << "&order=" << order;
        if (!ffield.empty() && !fvalue.empty())
            ss << "&ffield=" << ffield << "&fvalue=" << fvalue;

        ss << " HTTP/1.1\r\n"
           << "Host: genelab-data.ndc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

    void Query::GeneLabSearchHTML(const std::string &term, const std::string &dataSource)
    {
        std::stringstream ss;

        ss << "GET /genelab/data/glds/search?q=" << term
           << "&data_source=" << dataSource;

        ss << " HTTP/1.1\r\n"
           << "Host: genelab-data.ndc.nasa.gov"
           << "\r\n\r\n";;
        this->query = ss.str();
    }

}
