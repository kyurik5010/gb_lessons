#pragma once

#include <iostream>
#include "sys/socket.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include "unistd.h"


class TCP_client
{
private:
    int port;
    int IP_address;
    
    int sock;
    char* message_buffer[256];
    struct sockaddr_in serv_addr;
    char* serv_name[NI_MAXSERV];
    
    char* client_name[NI_MAXHOST];
    
    
public:
    TCP_client(char* ip, char* p)
    {
        IP_address = atoi(ip);
        port = atoi(p);
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr = htonl(IP_address);
        serv_addr.sin_len = sizeof(sockaddr_in);
    }
    
    
    int CreateSocket_IPv4()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if(!sock)
        {
            std::cerr << "ERROR creating socket" << std::endl;
            return EXIT_FAILURE;
        }
        
        int broadcast = 1;
        
        if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char*>(&broadcast), sizeof(broadcast)) < 0)
        {
            std::cerr << "WARNING - failed setting options for cocket: " << errno << std::endl;
        }
        return 0;
    }
    
    int ConnectToServer()
    {
        CreateSocket_IPv4();
        
        if(connect(sock, reinterpret_cast<sockaddr *>(&serv_addr), sizeof(serv_addr)) < 0)
        {
            std::cerr << "ERROR '" << errno << "' connecting to server at " << ntohl(serv_addr.sin_addr.s_addr) << std::endl;
            return EXIT_FAILURE;
        }
        
        std::cout << "Connection established >>>" << std::endl;
        
        return 0;
    }
    
    int CommenceExchange()
    {
        int run = 1;
        while(run)
        {
            std::string buf;
            std::cout << "Send message: ";
            std::cin >> buf;
            
            send(sock, buf.c_str(), sizeof(message_buffer)-1, 0);
            
            if (recv(sock, message_buffer, sizeof(message_buffer), 0) < 0)
            {
                std::cerr << "ERROR receiving message from client" << std::endl;
                return EXIT_FAILURE;
            }
            
            if(buf == "exit")
            {
                std::cout << "Terminating";
            }
            
        }
        return 0;
    }
    
    void CloseSession()
    {
        shutdown(sock, SHUT_RDWR);
        close(sock);
    }
    
    ~TCP_client(){};
};
