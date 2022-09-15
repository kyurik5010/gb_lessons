#ifndef BOOST_SERVER_CONNECTION_H
#define BOOST_SERVER_CONNECTION_H

#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <optional>
#include <array>
#include <filesystem>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>


using namespace boost::asio;
namespace FS = std::filesystem;

class NewCon
{
private:
    FS::path _file_path;
    ip::tcp::socket _client;
public:
    std::string get_request();                                      // получить сырой путь

    std::optional<FS::path> reinterpret(std::string raw_path);      // перевести сырой путь в объект пути

    int send_file();                                               // отправить файл

    explicit NewCon(io_context &connection);

    ~NewCon();
};




#endif //BOOST_SERVER_CONNECTION_H
