
#include "src/interface.h"
#include <iostream>

int main(int argc, const char *argv[]){
    if(argc < 2)
    {
        std::cerr << "Usage: <port>" << std::endl;
        return EXIT_FAILURE;
    }

    Interface inter;
    int port = std::stoi(argv[1]);

    if(argv[2])
    {
        inter.set_timer(std::stoi(argv[2]));
        std::cout << "Client connection timeout set to " << argv[2] << " seconds" << std::endl;
    }
    else
        std::cout << "Default client connection timeout: 60 seconds" << std::endl;

    std::cout << "Starting server on port " << argv[1] << std::endl;

    inter.launch_server_on_port(port);

    return EXIT_SUCCESS;
}