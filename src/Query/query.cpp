#include "query.hpp"

std::string Query::buildApod(bool thumb, std::string date = "today", bool conceptTags = false, bool hd = true) {
    std::stringstream ss;
    ss << "https://api.nasa.gov/planetary/apod?";
}

std::string Query::buildApod(std::string startDate, std::string endDate, bool conceptTags, bool hd, bool thumb) {
    return std::string();
}

std::string Query::buildApod(int count, bool conceptTags, bool hd, bool thumb) {
    return std::string();
}
