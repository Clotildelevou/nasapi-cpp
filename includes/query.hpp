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
        bool isJSON;

    public:
        Query(std::string &apiKey):
                apiKey(apiKey),
                isJSON(true)
        {}


        const std::string &getQuery();

        void setHTML();

        bool isTypeJSON();


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

        void EarthImagery(float lat, float lon, float dim, const std::string &date);

        void EarthAssets(float lat, float lon, const std::string &date, float dim);

        void EonetEvents(const std::string &source, const std::string &status, int limit, int days);

        void EonetCategories(int categoryID, const std::string &source, const std::string &status, int limit, int days);

        void EonetLayers(int categoryID);

        void EpicNatural();

        void EpicNaturalDate(const std::string &naturalDate);

        void EpicNaturalAll();

        void EpicNaturalAvailable();

        void EpicEnhanced();

        void EpicEnhancedDate(const std::string &date);

        void EpicEnhancedAll();

        void EpicEnhancedAvailable();

        void
        EpicArchive(const std::string &collection, const std::string &year, const std::string &month,
                    const std::string &day,
                    const std::string &imageType, const std::string &filename);

        void Exoplanet(const std::string &table, const std::string &select, const std::string &count,
                       const std::string &where,
                       const std::string &order, int ra, int dec, const std::string &radius, const std::string &format);


        void GeneLabData(const std::string &gldsStudyId, int pageNum, int resultsPPage);

        void GeneLabMeta(int gldsStudyId);

        void GeneLabSearchJSON(const std::string &term, int from, int size, const std::string &datasource,
                           const std::string &field,
                           const std::string &order, const std::string &ffield, const std::string &fvalue);

        void GeneLabSearchHTML(const std::string &term, const std::string &dataSource);


        void Insight(const std::string &version, const std::string &feedtype);


        void MRPsol(int sol, const std::string &camera, int page);

        void MRPEarthDate(const std::string &sol, const std::string &camera, int page);
    };
}



