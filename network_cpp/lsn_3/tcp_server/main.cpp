#include "TCP_server.cpp"
#include "stdlib.h"
#include <iostream>

int main(int argc, char const *argv[]){
    std::cout << "Please provide port number: ";
    std::string argument;
    std::cin >> argument;

    std::shared_ptr<TCP_server> serv = TCP_server::getServerInstatnce();

    const int port = std::stoi(argument);

    serv->StartServerOnPort(port);

    return EXIT_SUCCESS;
}
