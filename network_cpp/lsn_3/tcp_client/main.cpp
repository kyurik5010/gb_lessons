#include "TCP_client.cpp"
#include <iostream>
#include <memory>

int main(int argc, const char * argv[]) {

    std::string IP_address, port;
    std::cout << "please provide IP address: ";
    std::getline(std::cin, IP_address);
    std::cout << "please provide port number: ";
    std::cin >> port;

    std::unique_ptr<TCP_client> client = std::make_unique<TCP_client>(IP_address, port);
    
    if(client->ConnectToServer())
    {
        std::cerr << "ERROR connecting to server at " << IP_address << std::endl;
    }
    
    client->CommenceExchange();

    return 0;
}
