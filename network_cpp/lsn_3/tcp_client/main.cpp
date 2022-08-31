#include "TCP_client.cpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    if(argc != 2)
        std::cerr << "usage: <IP_address> <port>" << std::endl;
    
    TCP_client *client = new TCP_client((char*)argv[0], (char*)argv[1]);
    
    if(client->ConnectToServer())
    {
        std::cerr << "ERROR connecting to server at " << argv[0] << std::endl;
    }
    
    client->CommenceExchange();
    
    delete client;
    return 0;
}
