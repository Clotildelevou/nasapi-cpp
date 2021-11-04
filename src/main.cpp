#include "query.hpp"
#include "client.hpp"


int main(void)
{
    Client client = Client();
    std::string apiKey = "byBP90bGzkOdifclHdWVeUecgGg8oj9IoxnTLqW1";
    client.Apod(apiKey);
}
