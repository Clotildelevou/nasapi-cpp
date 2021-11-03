#include "query.hpp"


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

    ss << "GET / https://api.nasa.gov/planetary/apod?api_key=" << this->apiKey
    << "&start_date=" << startDate
    << "&end_date=" << endDate;

    if (thumb)
        ss << "&thumbs=true";

    ss << " HTTP/1.0"
    << "\\r\\n\\r\\n";;
    this->query = ss.str();
}

void Query::Apod(int count, bool thumb) {
    std::stringstream ss;

    ss << "GET / https://api.nasa.gov/planetary/apod?api_key=" << this->apiKey
    << "&count=" << count
    << " HTTP/1.0"
    << "\\r\\n\\r\\n";
    this->query = ss.str();
}

const std::string &Query::getQuery() {
    return this->query;
}
