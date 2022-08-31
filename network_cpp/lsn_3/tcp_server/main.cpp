#pragma once

#include "TCP_server.cpp"
#include "stdlib.h"
#include <iostream>

int main(int argc, char const *argv[]){
    if(argc < 1)
    {
        std::cerr << argv[0] << "Usage: <port>" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << argv[0] << std::endl;

    TCP_server *serv = TCP_server::getServerInstatnce();

    const int port = std::atoi(argv[0]);

    if(serv->StartServerOnPort(port) != 0)
    {
        std::cerr << "Closing\n";
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
