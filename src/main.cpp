#include "query.hpp"
#include "client.hpp"


int main(int argv, char *argv[])
{
    Client client = Client();
    std::string apiKey = std::string(argv[1]);
    client.Apod(apiKey);
}
