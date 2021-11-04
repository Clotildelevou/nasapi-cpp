#include "query.hpp"
#include "client.hpp"


int main(int argc, char *argv[])
{
    Client client = Client();
    std::string apiKey = "DEMO_KEY";
    client.Apod(apiKey, true, 5);
}
