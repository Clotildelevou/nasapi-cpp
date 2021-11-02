#include "query.hpp"

void Query::Apod(bool thumb, std::string date) {
    std::stringstream ss;
    ss << "https://api.nasa.gov/planetary/apod?api_key=" << this->apiKey;

    if (date == "today")
        ss << "&date=" << this->today;
    else
        ss << date;

    if (thumb)
        ss << "&thumb=true";
    this->query = ss.str();
}

void Query::Apod(std::string &startDate, std::string &endDate, bool thumb) {
    std::stringstream ss;

    ss << "https://api.nasa.gov/planetary/apod?api_key=" << this->apiKey
    << "&start_date=" << startDate
    << "&end_date=" << endDate;

    if (thumb)
        ss << "&thumb=true";
    this->query = ss.str();
}

void Query::Apod(int count, bool thumb) {
    std::stringstream ss;

    ss << "https://api.nasa.gov/planetary/apod?api_key=" << this->apiKey
    << "&count=" << count;
    this->query = ss.str();
}
