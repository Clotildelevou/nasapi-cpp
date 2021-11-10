#include "client.hpp"

using namespace nasapi;

int main(void)
{
    Client client = Client();
    std::string apiKey = "DEMO_KEY";
    client.Apod(apiKey);
}
