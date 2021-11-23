#pragma once

#include <filesystem>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <netdb.h>
#include <cstring>
#include <fstream>
#include <string>


#include <json-c/json.h>

#include "logger.hpp"
#include "query.hpp"

using boost::asio::ip::tcp;
namespace ssl = boost::asio::ssl;
typedef ssl::stream<tcp::socket> ssl_socket;

namespace nasapi
{
    class Client {
    private:
        Logger logger_;
        std::string header_;
        std::string jsonRep_;
        std::string htmlRep_;

        void onError(const std::string &log);
        void onAction(const std::string &log);

        int buildJson();
        int buildHeader();
        int buildHTML();

        int connect(ssl_socket &socket, tcp::resolver &resolver);
        int send(ssl_socket &socket, Query &query);
        int receive(ssl_socket &socket, bool isJSON);
        int disconnect(ssl_socket &socket);

        void queryLaunch(ssl_socket &socket, tcp::resolver &resolver, Query &query);

    public:
        Client()
        {
            this->logger_ = Logger();
            onAction("Client created.");
        }

        void Apod(std::string &apiKey);

        void Apod(std::string &apiKey, bool thumb, const std::string &date);

        void Apod(std::string &apiKey, bool thumb, const std::string &startDate, const std::string &endDate);

        void Apod(std::string &apiKey, bool thumb, int count);

        void NeoFeed(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void NeoLookup(std::string &apiKey, int asteroidId);

        void NeoBrowse(std::string &apiKey);

        void DonkiCME(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void DonkiHSS(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void DonkiWSA(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void DonkiRBE(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void DonkiMPC(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void DonkiFLR(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void DonkiGST(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void DonkiIPS(std::string &apiKey, const std::string &startDate, const std::string &endDate,
                      const std::string &location,
                      const std::string &catalog);

        void DonkiCMEAnalysis(std::string &apiKey, const std::string &startDate, const std::string &endDate,
                         bool mostAccurateOnly, bool completeEntryOnly, int speed, int halfAngle,
                         const std::string &catalog, const std::string &keyword);

        void DonkiSEP(std::string &apiKey, const std::string &startDate, const std::string &endDate);

        void EarthImagery(std::string &apiKey, float lat, float lon, float dim, const std::string &date);

        void EarthAssets(std::string &apiKey, float lat, float lon, const std::string &date, float dim);

        void
        EonetEvents(std::string &apiKey, const std::string &source, const std::string &status, int limit, int days);

        void
        EonetCategories(std::string &apiKey, int categorieID, const std::string &source, const std::string &status,
                        int limit,
                        int days);

        void EonetLayers(std::string &apiKey, int categorieID);


        void EpicNatural(std::string &apiKey);

        void EpicNaturalDate(std::string &apiKey, const std::string &date);

        void EpicNaturalAll(std::string &apiKey);

        void EpicNaturalAvailable(std::string &apiKey);

        void EpicEnhanced(std::string &apiKey);

        void EpicEnhancedDate(std::string &apiKey, const std::string &date);

        void EpicEnhancedAll(std::string &apiKey);

        void EpicEnhancedAvailable(std::string &apiKey);

        void EpicArchive(std::string &apiKey, const std::string &collection, const std::string &year,
                         const std::string &month,
                         const std::string &day, const std::string &imageType, const std::string &filename);

        void
        Exoplanet(std::string &apiKey, const std::string &table, const std::string &select, const std::string &count,
                  const std::string &where, const std::string &order, int ra, int dec, const std::string &radius,
                  const std::string &format);

        void GeneLabData(std::string &apiKey, const std::string &gldsStudyId, int pageNum, int resultsPPage);

        void GeneLabMeta(std::string &apiKey, int gldsStudyId);

        void GeneLabSearchJSON(std::string &apiKey, const std::string &term, int from, int size,
                               const std::string &datasource,
                               const std::string &field, const std::string &order, const std::string &ffield,
                               const std::string &fvalue);

        void GeneLabSearchHTML(std::string &apiKey, const std::string &term, const std::string &dataSource);
    };
}


