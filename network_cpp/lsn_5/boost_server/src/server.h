#ifndef BOOST_SERVER_SERVER_H
#define BOOST_SERVER_SERVER_H

#pragma once
#include "common.h"
#include "connection.h"



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

    void set_timer(int); //установка таймера ожидания подключений (здесь пока не используется т.к. значение передается в конструктор)

    void deadline_handler(const boost::system::error_code &);

    void get_client();
};

#endif //BOOST_SERVER_SERVER_H
