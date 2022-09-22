
#include "src/Client.h"

#include <iostream>


int main(int argc, const char *argv[]){
    if(argc < 2)
        std::cout << "Usage <port>" << std::endl;
    std::cout << "\v" << std::endl;
    bool run = true;

//    IP_address = "127.0.0.1";
    int port = std::stoi(argv[1]);
//    destination folder = "download";

    Client client("127.0.0.1", port, "download");

    std::cout << "===============================| dummy.txt |===============================" << std::endl;
    client.get_file("dummy.txt");

//    std::cout << "============================| nonexistent.txt |============================" << std::endl;
//    client.get_file("nonexistent.txt");
//
//    std::cout << "==============================| dummy2.txt |===============================" << std::endl;
//    client.get_file("dummy2.txt");

    while(run)
    {
        std::this_thread::sleep_for(std::chrono::seconds{10});
        run = client.check_tasks();
    }

    return EXIT_SUCCESS;
}