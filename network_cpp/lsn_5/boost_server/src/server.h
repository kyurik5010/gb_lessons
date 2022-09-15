#ifndef BOOST_SERVER_SERVER_H
#define BOOST_SERVER_SERVER_H

#pragma once

#include "connection.h"

#include <iostream>
#include <memory>
#include <future>
#include <vector>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>

using namespace boost::asio;

class F_Server{
private:
    int _timer;
    std::vector<std::future<int>> client_operations;
    std::shared_ptr<io_context> _io;
    ip::tcp::acceptor _acc;
    typedef std::shared_ptr<ip::tcp::socket> socket_ptr;
    int check_client_operations();
public:
    F_Server(int, int);

    ~F_Server();

    void accept_connection(); //в цикле принимает соединение и вызывает get_client()

    void set_timer(int); //установка таймера ожидания подключений

    void deadline_handler(const boost::system::error_code &);

    void get_client();
};

#endif //BOOST_SERVER_SERVER_H
