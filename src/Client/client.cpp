#include "client.hpp"

namespace nasapi
{
    int Client::buildJson() {
        json_object *root = json_tokener_parse(this->jsonRep_.c_str());
        if (!root) {
            onError("Couldn't parse response.");
            printf("The json object to string:\n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));
            if (json_object_put(root) != 1)
            {
                onError("Couldn't free the JSON object.");
                return -1;
            }
            return -1;
        }
        if(json_object_to_file("nasapi-cpp.json", root) == -1)
        {
            onError("Couldn't build JSON file.");
            if (json_object_put(root) != 1)
            {
                onError("Couldn't free the JSON object.");
                return -1;
            }
            return -1;
        }
        else
        {
            onAction("Response file created.");
        }
        if (json_object_put(root) != 1)
        {
            onError("Couldn't free the JSON object.");
            return -1;
        }
        return 0;
    }

    int Client::buildHeader()
    {
        std::ofstream out("nasapi-cpp-header.txt");
        if (out)
        {
            out << this->header_;
            out.close();
            onAction("Header file created\n");
            return 0;
        }
        else
        {
            onError("Couldn't create corresponding header file.");
            return -1;
        }
    }

    int Client::buildHTML() {
        //TODO
        return 0;
    }

    std::string makeString(boost::asio::streambuf &streambuf)
    {
        return {buffers_begin(streambuf.data()),
                buffers_end(streambuf.data())};
    }

    int findParameter(const std::string &header, std::string &parameter)
    {
        auto retstring = header;
        size_t start = retstring.find(parameter);

        if (start == std::string::npos)
            return -1;

        start += parameter.length();
        retstring = retstring.substr(start, retstring.length());
        size_t end = retstring.find_first_of('\r');

        if (end == std::string::npos)
            return -1;
        return stoi(retstring.substr(0, end));
    }


    void Client::onError(const std::string &log) {
        this->logger_.setStatus(ERROR);
        this->logger_.printLog(log);
        this->logger_.setStatus(OK);
    }

    void Client::onAction(const std::string &log) {
        this->logger_.printLog(log);
    }


    int Client::connect(ssl_socket &socket, tcp::resolver &resolver) {
        try {
            tcp::resolver::query query("api.nasa.gov", "https");
            boost::asio::connect(socket.lowest_layer(), resolver.resolve(query));
            socket.set_verify_mode(ssl::verify_peer);
            socket.set_verify_callback(ssl::rfc2818_verification("api.nasa.gov"));
            socket.handshake(ssl_socket::client);

            std::stringstream ss;
            ss << "Client connected using TLS protocol.";
            onAction(ss.str());
            return 0;
        }
        catch (std::exception &e) {
            onError(e.what());
            return -1;
        }
    }

    int Client::disconnect(ssl_socket &socket) {
        boost::system::error_code error;
        socket.lowest_layer().close(error);

        if(error) {
            std::stringstream ss;
            ss << "Couldn't close connection: "
               << error.message();
            onError(ss.str());
            return -1;
        }
        else
        {
            onAction("Connection closed.");
            return 0;
        }
    }

    int Client::send(ssl_socket &socket, Query &query) {

        std::stringstream ss;
        boost::system::error_code error;
        boost::asio::write(socket, boost::asio::buffer(query.getQuery()),error);
        if(error) {
            ss.str(std::string());
            ss << "Couldn't send request: "
               << error.message();
            onError(ss.str());
            return -1;
        }
        else {
            ss.str(std::string());
            ss << "Request sent.";
            onAction(ss.str());
        }
        return 0;
    }

    int Client::receive(ssl_socket &socket, bool isJSON) {

        boost::system::error_code error;
        auto buffer = boost::asio::streambuf();
        size_t headerSize = boost::asio::read_until(socket, buffer,"\r\n\r\n" , error);
        if(error && error != boost::asio::error::eof) { //Error handling
            onError("Error in response reception.");
            return -1;
        }
        else
        {
            this->header_ = makeString(buffer);
            this->header_.erase(headerSize, this->header_.size());
            onAction("Header received.");
        }

        std::string param = "Content-Length: ";
        size_t contentLength = findParameter(this->header_, param);

        buffer.consume(headerSize);
        boost::asio::read(socket, buffer,  boost::asio::transfer_exactly(contentLength - buffer.size()), error);
        if(error && error != boost::asio::error::eof) { //Error handling
            onError("Error in response reception.");
            return -1;
        }
        else
        {
            this->jsonRep_ = makeString(buffer);
            onAction("Json received.");
        }
        //TODO : add the HTML possibility
        return (buildJson() == 0 && buildHeader() == 0);
    }

    void Client::queryLaunch(ssl_socket &socket, tcp::resolver &resolver, Query &query) {
        if (connect(socket, resolver) == -1)
        {
            onError("Couldn't make connection");
            exit(-1);
        }

        if (send(socket, query) == -1)
        {
            onError("send");
            exit(-1);
        }

        if(receive(socket, query.isTypeJSON()) == -1)
        {
            onError("recv");
            exit(-1);
        }

        if (disconnect(socket) == -1)
        {
            onError("disconnect");
            exit(-1);
        }
    }


    void Client::Apod(std::string &apiKey) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.Apod();

        queryLaunch(socket, resolver, query);

        onAction("APOD written.");
        exit(-1);
    }

    void Client::Apod(std::string &apiKey, bool thumb, const std::string &date) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.Apod(date, thumb);

        queryLaunch(socket, resolver, query);

        onAction("APOD written.");
        exit(-1);
    }

    void Client::Apod(std::string &apiKey, bool thumb, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.Apod(startDate, endDate, thumb);

        queryLaunch(socket, resolver, query);

        onAction("APOD written.");
        exit(-1);
    }

    void Client::Apod(std::string &apiKey, bool thumb, int count) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.Apod(count, thumb);

        queryLaunch(socket, resolver, query);

        onAction("APOD written.");
        exit(-1);
    }


    void Client::NeoFeed(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.NeoFeed(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("NeoFeed written.");
        exit(-1);
    }

    void Client::NeoLookup(std::string &apiKey, int asteroidId) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.NeoLookup(asteroidId);

        queryLaunch(socket, resolver, query);

        onAction("Neo Lookup written.");
        exit(-1);
    }

    void Client::NeoBrowse(std::string &apiKey) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.NeoBrowse();

        queryLaunch(socket, resolver, query);

        onAction("Neo Browse written.");
        exit(-1);
    }


    void Client::DonkiCME(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiCME(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiCME written.");
        exit(-1);
    }

    void Client::DonkiCMEAnalysis(std::string &apiKey, const std::string &startDate, const std::string &endDate,
                                  bool mostAccurateOnly = true, bool completeEntryOnly = true, int speed = 0,
                                  int halfAngle = 0, const std::string& catalog = "ALL",
                                  const std::string& keyword = "NONE")
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiCMEAnalysis(startDate, endDate, mostAccurateOnly, completeEntryOnly, speed,
                               halfAngle, catalog, keyword);

        queryLaunch(socket, resolver, query);

        onAction("DonkiCME written.");
        exit(-1);
    }

    void Client::DonkiGST(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiGST(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiGST written.");
        exit(-1);
    }

    void Client::DonkiIPS(std::string &apiKey, const std::string &startDate, const std::string &endDate, const std::string& location = "ALL",
                          const std::string& catalog = "ALL") {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiIPS(startDate, endDate, location, catalog);

        queryLaunch(socket, resolver, query);

        onAction("DonkiIPS written.");
        exit(-1);
    }

    void Client::DonkiFLR(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiFLR(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiFLR written.");
        exit(-1);
    }

    void Client::DonkiSEP(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiSEP(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiSEP written.");
        exit(-1);
    }

    void Client::DonkiMPC(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiMPC(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiMPC written.");
        exit(-1);
    }

    void Client::DonkiRBE(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiRBE(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiRBE written.");
        exit(-1);
    }

    void Client::DonkiHSS(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiHSS(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiHSS written.");
        exit(-1);
    }

    void Client::DonkiWSA(std::string &apiKey, const std::string &startDate, const std::string &endDate) {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.DonkiWSA(startDate, endDate);

        queryLaunch(socket, resolver, query);

        onAction("DonkiWSA written.");
        exit(-1);
    }


    void Client::EarthImagery(std::string &apiKey, float lat, float lon, float dim = 0.25, const std::string& date = "today")
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EarthImagery(lat, lon, dim, date);

        queryLaunch(socket, resolver, query);

        onAction("EarthImagery written.");
        exit(-1);
    }

    void Client::EarthAssets(std::string &apiKey, float lat, float lon, const std::string& date, float dim = 0.25)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EarthAssets(lat, lon, date, dim);

        queryLaunch(socket, resolver, query);

        onAction("EarthAsset written.");
        exit(-1);
    }


    void Client::EonetEvents(std::string &apiKey, const std::string& source = "", const std::string& status = "", int limit = 0, int days = 0)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EonetEvents(source, status, limit, days);

        queryLaunch(socket, resolver, query);

        onAction("EonetEvents written.");
        exit(-1);
    }

    void Client::EonetCategories(std::string &apiKey, int categorieID, const std::string& source = "", const std::string& status = "", int limit = 0, int days = 0)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EonetCategories(categorieID, source, status, limit, days);

        queryLaunch(socket, resolver, query);

        onAction("EonetCategories written.");
        exit(-1);
    }

    void Client::EonetLayers(std::string &apiKey, int categorieID)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EonetLayers(categorieID);

        queryLaunch(socket, resolver, query);

        onAction("EonetLayers written.");
        exit(-1);
    }


    void Client::EpicNatural(std::string &apiKey)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicNatural();

        queryLaunch(socket, resolver, query);

        onAction("EpicNatural written.");
        exit(-1);
    }

    void Client::EpicNaturalDate(std::string &apiKey, const std::string &date)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicNaturalDate(date);

        queryLaunch(socket, resolver, query);

        onAction("EpicNaturalDate written.");
        exit(-1);
    }

    void Client::EpicNaturalAll(std::string &apiKey)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicNaturalAll();

        queryLaunch(socket, resolver, query);

        onAction("EpicNaturalAll written.");
        exit(-1);
    }

    void Client::EpicNaturalAvailable(std::string &apiKey)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicNaturalAvailable();

        queryLaunch(socket, resolver, query);

        onAction("EpicNaturalAvailable written.");
        exit(-1);
    }

    void Client::EpicEnhanced(std::string &apiKey)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicEnhanced();

        queryLaunch(socket, resolver, query);

        onAction("EpicEnhanced written.");
        exit(-1);
    }

    void Client::EpicEnhancedDate(std::string &apiKey, const std::string &date)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicEnhancedDate(date);

        queryLaunch(socket, resolver, query);

        onAction("EpicEnhancedDate written.");
        exit(-1);
    }

    void Client::EpicEnhancedAll(std::string &apiKey)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicEnhancedAll();

        queryLaunch(socket, resolver, query);

        onAction("EpicEnhancedAll written.");
        exit(-1);
    }

    void Client::EpicEnhancedAvailable(std::string &apiKey)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicEnhancedAvailable();

        queryLaunch(socket, resolver, query);

        onAction("EpicEnhancedAvailable written.");
        exit(-1);
    }

    void Client::EpicArchive(std::string &apiKey, const std::string &collection, const std::string &year,
                             const std::string &month, const std::string &day,
                             const std::string &imageType, const std::string &filename)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.EpicArchive(collection, year, month, day, imageType, filename);

        queryLaunch(socket, resolver, query);

        onAction("EpicArchive written.");
        exit(-1);
    }

    void Client::Exoplanet(std::string &apiKey, const std::string &table, const std::string &select,
                           const std::string &count, const std::string &where, const std::string &order, int ra = 0,
                           int dec = 0, const std::string &radius = "", const std::string &format = "")
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.Exoplanet(table, select, count, where, order, ra, dec, radius, format);

        queryLaunch(socket, resolver, query);

        onAction("EpicArchive written.");
        exit(-1);
    }


    void Client::GeneLabData(std::string &apiKey, const std::string& gldsStudyId, int pageNum = 0, int resultsPPage = 0)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.GeneLabData(gldsStudyId, pageNum, resultsPPage);

        queryLaunch(socket, resolver, query);

        onAction("GeneLabData written.");
        exit(-1);
    }

    void Client::GeneLabMeta(std::string &apiKey, int gldsStudyId)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.GeneLabMeta(gldsStudyId);

        queryLaunch(socket, resolver, query);

        onAction("GeneLabMeta written.");
        exit(-1);
    }

    void Client::GeneLabSearchJSON(std::string &apiKey, const std::string &term, int from, int size, const std::string &datasource,
                                   const std::string &field, const std::string &order = "", const std::string &ffield = "",
                                   const std::string &fvalue = "")
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.GeneLabSearchJSON(term, from, size, datasource, field, order, ffield, fvalue);

        queryLaunch(socket, resolver, query);

        onAction("GeneLabSearchJSON written.");
        exit(-1);
    }

    void Client::GeneLabSearchHTML(std::string &apiKey, const std::string &term, const std::string &dataSource)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.GeneLabSearchHTML(term, dataSource);

        queryLaunch(socket, resolver, query);

        onAction("GeneLabSearchHTML written.");
        exit(-1);
    }


    void Client::Insight(std::string &apiKey, const std::string &version, const std::string &feedtype)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.Insight(version, feedtype);

        queryLaunch(socket, resolver, query);

        onAction("Feedtype written.");
        exit(-1);
    }


    void Client::MRPsol(std::string &apiKey, int sol, const std::string &camera = "all", int page = 1)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.MRPsol(sol, camera, page);

        queryLaunch(socket, resolver, query);

        onAction("MRPsol written.");
        exit(-1);
    }

    void Client::MRPEarthDate(std::string &apiKey, const std::string &sol, const std::string &camera = "all", int page = 1)
    {
        ssl::context context(ssl::context::sslv23);
        context.set_default_verify_paths();
        boost::asio::io_service io_service;
        ssl_socket socket(io_service, context);
        tcp::resolver resolver(io_service);

        Query query(apiKey);
        query.MRPEarthDate(sol, camera, page);

        queryLaunch(socket, resolver, query);

        onAction("MRPEarthDate written.");
        exit(-1);
    }

}