
#include "src/Client.h"

#include <iostream>


int main(int argc, const char *argv[]){
    if(argc > 1)
        std::cout << "Command line arguments ignored" << std::endl;

    bool run = true;

//    IP_address = "127.0.0.1";
//    port = 6667;
//    destination folder = "download";

    Client client("127.0.0.1", 6667, "download");

    client.get_file("dummy.txt");

    client.get_file("nonexistent.txt");

    client.get_file("dummy2.txt");

    while(run)
    {
        run = client.check_tasks();
    }

    return EXIT_SUCCESS;
}