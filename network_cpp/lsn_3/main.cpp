#include "TCP_server.cpp"
#include "stdlib.h"
#include <iostream>

int main(int argc, const char* argv[]){
    if(argc != 1)
    {
        std::cerr << "usage: <port>\n";
        return EXIT_FAILURE;
    }
    
    
    TCP_server* serv = TCP_server::getServerInstatnce();
    
    if(serv->createTcpSocket(atoi(argv[0])) != 0)
    {
        std::cerr << "Closing\n";
        return EXIT_FAILURE;
    }
    
    
    
    
    
    return EXIT_SUCCESS;
}
