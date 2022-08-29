#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#ifndef _WIN32
# include <sys/socket.h>
# include <unistd.h>
#else
# include <winsock2.h>
#endif
#include <netdb.h>
#include <arpa/inet.h>


// Trim from end (in place).
static inline std::string& rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base());
    return s;
}

class TCP_dump{
    TCP_dump* dumper;
public:
    TCP_dump()
};
int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }

    const int port { std::stoi(argv[1]) };

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    std::cout << "Starting echo server on the port " << port << "...\n";

    if (!sock)
    {
        std::cerr << "\nSOCKET_ERROR" << std::endl;
        return EXIT_FAILURE;
    }

    sockaddr_in addr =
    {
        .sin_family = PF_INET,
        .sin_port = htons(port),
    };

    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) != 0)
    {
        std::cerr << "\nBIND_ERROR" << std::endl;
        // Socket will be closed in the Socket destructor.
        close(sock);
        return EXIT_FAILURE;
    }

    char buffer[256];

    // socket address used to store client address
    struct sockaddr_in client_address = {0};
    socklen_t client_address_len = sizeof(sockaddr_in);
    ssize_t recv_len = 0;

    std::cout << "Running echo server...\n" << std::endl;
    char client_address_buf[INET_ADDRSTRLEN];
    char client_name_buf[NI_MAXHOST];
    char serv_name_buf[NI_MAXSERV];


    bool run = true;
    int status = 0;

    while (run)
    {
        // Read content into buffer from an incoming client.
        recv_len = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                            reinterpret_cast<sockaddr *>(&client_address),
                            &client_address_len);

        if(getnameinfo(reinterpret_cast<sockaddr*>(&client_address), client_address_len, client_name_buf,
                       sizeof(client_name_buf), serv_name_buf, sizeof(serv_name_buf), 0) != status)
        {
            std::cout << "HOST_NAME_RESOLVE_ERROR\n";
        }
//const char *inet_ntop(int af, const void *restrict src, char *restrict dst, socklen_t size);

        if (recv_len > 0)
        {
            buffer[recv_len] = '\0';
            std::cout
                << "Client with address "
                << inet_ntop(AF_INET, &client_address.sin_addr, client_address_buf, sizeof(client_address_buf) / sizeof(client_address_buf[0]))
                << ":" << ntohs(client_address.sin_port)
                << " and name '"
                << client_name_buf
                << "' sent datagram "
                << "[length = "
                << recv_len
                << "]:\n'''\n"
                << buffer
                << "\n'''"
                << std::endl;

            std::string command_string = buffer;
            rtrim(command_string);

            if (command_string == "exit")
                run = false;

            // Send same content back to the client ("echo").
            sendto(sock, buffer, recv_len, 0, reinterpret_cast<const sockaddr*>(&client_address),
                   client_address_len);
        }

        std::cout << std::endl;
    }
    close(sock);
    return EXIT_SUCCESS;
}

