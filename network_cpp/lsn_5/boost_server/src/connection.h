#ifndef BOOST_SERVER_CONNECTION_H
#define BOOST_SERVER_CONNECTION_H

#pragma once
#include "common.h"


using namespace boost::asio;
namespace FS = std::filesystem;

class NewCon
{
private:
    std::shared_ptr<ip::tcp::socket> _sock;
    int _port;
    boost::system::error_code error;

    int _state;
    bool _keep_alive;

    FS::path _file_path;
    std::string _raw_line;
    boost::asio::streambuf _buffer;

public:
    std::string get_request();                                      // получить сырой путь

    std::optional<FS::path> reinterpret(std::string raw_path);      // перевести сырой путь в объект пути

    size_t resend_data(std::vector<std::vector<char>>&);

    int send_file();                                               // отправить файл

    explicit NewCon(io_context &connection, int port, ip::tcp::socket &&sock);

    int get_connection_state() const;
    void set_connection_state(int);
    ~NewCon();
};




#endif //BOOST_SERVER_CONNECTION_H
