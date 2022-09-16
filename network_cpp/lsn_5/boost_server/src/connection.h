#ifndef BOOST_SERVER_CONNECTION_H
#define BOOST_SERVER_CONNECTION_H

#pragma once
#include "common.h"


using namespace boost::asio;
namespace FS = std::filesystem;

class NewCon
{
private:
    FS::path _file_path;
    ip::tcp::socket _client;
    int _state;
public:
    std::string get_request();                                      // получить сырой путь

    std::optional<FS::path> reinterpret(std::string raw_path);      // перевести сырой путь в объект пути

    int send_file();                                               // отправить файл

    explicit NewCon(io_context &connection);

    int get_connection_state() const { return _state };

    ~NewCon();
};




#endif //BOOST_SERVER_CONNECTION_H
