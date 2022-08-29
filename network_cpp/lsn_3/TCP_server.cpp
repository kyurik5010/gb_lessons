#include <iostream>
#include <vector>
#include "sys/socket.h"
#include "netinet/in.h"
#include "unistd.h"
#include "netdb.h"

class TCP_server
{
private:
//    std::vector<int*> sockets;
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(sockaddr_in);
    ssize_t recv_len = 0;
    char client_address_buf[INET_ADDRSTRLEN];
    char client_name_buf[NI_MAXHOST];
    char serv_name_buf[NI_MAXSERV];
    static TCP_server* instance;
    int port;
    TCP_server(){
        client_address = {0};
    };
public:
    static TCP_server* getServerInstatnce(){
        if(instance == nullptr)
            instance = new TCP_server;
        return instance;
    }

    int bindSocket(int socket, const sockaddr_in& addr)
    {
        if (bind(socket, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) != 0)
        {
            std::cerr << "\nBIND_ERROR" << std::endl;
            // Socket will be closed in the Socket destructor.
            close(socket);
            return EXIT_FAILURE;
        }
        return 0;
    }
    
    int createTcpSocket(int port)
    {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (!sock)
        {
            std::cerr << "\nSOCKET_ERROR" << std::endl;
            return EXIT_FAILURE;
        }
        
        std::cout << "Starting echo server on the port " << port << "...\n";
        
        struct sockaddr_in addr = {0};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = INADDR_ANY;
        
        bindSocket(sock, addr);
        return 0;
    }
};


TCP_server* TCP_server::instance = nullptr;



//struct sockaddr_in {
//    __uint8_t       sin_len;
//    sa_family_t     sin_family;
//    in_port_t       sin_port;
//    struct  in_addr sin_addr;
//    char            sin_zero[8];
//};
