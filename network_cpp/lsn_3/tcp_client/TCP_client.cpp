#pragma once

#include <iostream>
#include <sstream>
#include "sys/socket.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include "unistd.h"
#include <arpa/inet.h>


class TCP_client
{
private:
    int port;
    int IP_address;
    
    int sock;
    char incoming_buffer[1024];
    struct sockaddr_in serv_addr;
    char* serv_name[NI_MAXSERV];
    
    char* client_name[NI_MAXHOST];
    
    
public:
    TCP_client(std::string ip, std::string p)
    {
        port = stoi(p);

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr);
        std::cout << "Attempt connecting to server at " << ip.c_str() << std::endl;
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
        
        if(setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, reinterpret_cast<const char*>(&broadcast), sizeof(broadcast)) < 0)
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
            std::cerr << "ERROR connecting to server #" << errno << std::endl;
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
            std::string str;
            std::cout << "Send message: ";
            std::cin >> str;
            str += '\0';
            char outgoing_buffer[256];

            strncpy(outgoing_buffer, str.c_str(), sizeof(outgoing_buffer));

            if(-1 == (send(sock, outgoing_buffer, sizeof(outgoing_buffer)-1, 0)))
            {
                std::cerr << "ERROR sending message: #" << errno << std::endl;
                close(sock);
                return EXIT_FAILURE;
            }
            
            if (recv(sock, incoming_buffer, sizeof(incoming_buffer), 0) < 0)
            {
                std::cerr << "ERROR receiving message: #" << errno << std::endl;
                close(sock);
                return EXIT_FAILURE;
            }

            if((std::string)outgoing_buffer == "exit")
            {
                run = 0;
                CloseSession();
                break;
            }
            else
                std::cout << incoming_buffer << std::endl;
        }
        return 0;
    }
    
    void CloseSession()
    {
        shutdown(sock, SHUT_RDWR);
        close(sock);
        std::cout << "Session closed" << std::endl;
    }
    
    ~TCP_client(){
        CloseSession();
    };
};
