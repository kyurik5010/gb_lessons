#ifndef BOOST_SERVER_SERVER_H
#define BOOST_SERVER_SERVER_H

#pragma once
#include "common.h"
#include "connection.h"



using namespace boost::asio;

class F_Server{
private:
    int _timer;
    int _port;
    std::vector<std::shared_ptr<NewCon>> client_operations;
    std::shared_ptr<io_context> _io;
    ip::tcp::acceptor _acceptor;
    typedef std::shared_ptr<ip::tcp::socket> socket_ptr;
    bool check_client_operations();    // в цикле проверяет статус соединений, имеющихся в векторе client_operations
public:
    F_Server(int, int);                // инициализирует и настраивает акцептор,контекст и таймер (принимает порт и значение таймера)

    ~F_Server();                       // останавливает контекст

    void accept_connection();          // в цикле принимает соединение и вызывает get_client()

    void set_timer(int);               // установка таймера ожидания подключений (здесь пока не используется т.к. значение передается в конструктор)

    void deadline_handler(const boost::system::error_code &); //таймер ожидания подключений,
                                                              // если вектор пуст, то вызывает деструктор, иначе - accept_connection()

    void get_client(ip::tcp::socket&& sock);                 // создает объект соединения, кладет в вектор и запускает его работу в отдельном потоке
};

#endif //BOOST_SERVER_SERVER_H
