#pragma once

#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include "sys/socket.h"
#include "netinet/in.h"
#include "unistd.h"
#include "netdb.h"
#include "arpa/inet.h"
//#include "sys/types.h"

class TCP_server
{

    static std::shared_ptr<TCP_server> instance;
    int port;
    int sock, sockfd;
    char buffer[256];
    
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(sockaddr_in);
    char client_address_buf[INET_ADDRSTRLEN];
    char client_name_buf[NI_MAXHOST];
    
    char serv_name_buf[NI_MAXSERV];
    struct sockaddr_in serv_addr;
    
private:
    
    TCP_server(){
        client_address = {0};
        serv_addr = {0};
    };

    static std::shared_ptr<TCP_server> recieve_pointer()
    {
        return std::make_shared<TCP_server>(TCP_server());
    }

public:

    static std::shared_ptr<TCP_server> getServerInstatnce()
    {
        std::mutex m1;
        m1.lock(); // в разделе про синглтоны советовали так делать для обеспечения их потокобезопасности
        if(!instance)
        {
            instance = recieve_pointer();
        }
        m1.unlock();
        return instance;
    }
    
    int StartServerOnPort(int p)
    {
        port = p;

        std::cout  << "Starting TCP server on port " << port << "...\n";
        
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port);
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

        sock = CreateSocket_IPv4();

        if(BindSocket(sock, serv_addr))
        {
            std::cout << "Session closed due to an error" << std::endl;
            return EXIT_FAILURE;
        }

        if(-1 == listen(sock, 0))
        {
            std::cerr << "ERROR #" << errno << " listening on port " << port << std::endl;
        }
        std::cout << "Socket listening on port " << port << std::endl;
        
        if(!GetConnection())
            return EXIT_FAILURE;
        
        CommenceExchange();

        CloseSession();

        return 0;
    }
    
    int CreateSocket_IPv4()
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            std::cerr << "SOCKET_ERROR #" << errno << std::endl;
            return EXIT_FAILURE;
        }
        
//        int reuseport = 1;
//
//        if(setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, reinterpret_cast<const char*>(&reuseport), sizeof(reuseport)) != 0)
//            std::cerr << "ERROR setting socket options" << std::endl;
        return sock;
    }
    
    int BindSocket(int socket, const sockaddr_in& addr)
    {
         if (bind(socket, reinterpret_cast<const sockaddr *>(&addr), sizeof(addr)) != 0)
         {
             std::cerr << "\nBIND_ERROR #" << errno <<  std::endl;
             close(socket);
             return EXIT_FAILURE;
         }
         return 0;
    }
    
    bool GetConnection()
    {
        sockfd = accept(sock, reinterpret_cast<sockaddr *>(&client_address), &client_address_len);
        if(sockfd <= 0)
        {
            std::cerr << "ERROR connecting to client #" << errno << std::endl;
            return false;
        }
        PrintClientID();
        return true;
    }
    
    int CommenceExchange()
    {
        std::cout << "Starting exchange on port " << port << std::endl;
        char outgoing_buffer[256];
        int run = 1;
        while (run)
        {
            if (recv(sockfd, buffer, sizeof(buffer) - 1, 0) < 0)
            {
	        std::cerr << "ERROR receiving message #" << errno << std::endl;
                return EXIT_FAILURE;
            }
            
            std::cout << buffer << std::endl;
            
            if((std::string)buffer == "exit")
            {
                std::string str = "'exit' command recieved";
                strncpy(outgoing_buffer, str.c_str(), sizeof(outgoing_buffer));
                send(sockfd, outgoing_buffer, sizeof(outgoing_buffer) - 1, 0);
                run = 0;
                close(sockfd);
            }
            else
            {
                std::string str = "Server has recieved ";
                str += std::to_string(strlen(buffer));
                str += " symbols from client\0";
                strncpy(outgoing_buffer, str.c_str(), sizeof(outgoing_buffer));
                send(sockfd, outgoing_buffer, sizeof(outgoing_buffer) - 1, 0);
            }
        }
        std::cout << "Session closed" << std::endl;
        return 0;
    }
    
    void PrintClientID()
    {
        char* buf[256];
        getnameinfo(reinterpret_cast<sockaddr *>(&client_address), client_address_len,
                    client_name_buf, NI_MAXHOST, serv_name_buf, NI_MAXSERV, 0);

        inet_ntop(AF_INET, &client_address.sin_addr.s_addr, *buf, sizeof(buf));

        std::cout << "Connected to client: " << (std::string)client_name_buf
                  << "\nat address: '"<< *buf << "'" << std::endl;
    }
    
    void CloseSession()
    {
        shutdown(sock, SHUT_RDWR);
        shutdown(sockfd, SHUT_RDWR);
        close(sock);
        close(sockfd);
        std::cout << "Session closed" << std::endl;
    }
    
    ~TCP_server(){
        shutdown(sock, SHUT_RDWR);
        shutdown(sockfd, SHUT_RDWR);
        close(sock);
        close(sockfd);
    };
};


std::shared_ptr<TCP_server> TCP_server::instance = nullptr;


