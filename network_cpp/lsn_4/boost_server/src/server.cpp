#ifndef BOOST_SERVER_SERVER_CPP
#define BOOST_SERVER_SERVER_CPP


#pragma once

#include "server.h"
#include "connection.h"

using namespace boost::asio;

// В конструкторе инициализируется акцептор, начинается прослушивание TCP порта.
TcpServer::TcpServer(boost::asio::io_context& io_context) :
_io_context(io_context),
_acceptor(io_context, ip::tcp::endpoint(ip::tcp::v4(), echo_port))
{
    start_accept();
}

// Метод start_accept() создаёт сокет и выполняет асинхронный `accept()`, при соединении.
void TcpServer::start_accept()
{
    TcpConnection::pointer new_connection = TcpConnection::create(_io_context);

    _acceptor.async_accept(new_connection->socket(),
                           [this, new_connection] (const boost::system::error_code& error)
                           {
                               this->handle_accept(new_connection, error);
                           }
    );
}

// Метод handle_accept() вызывается, когда асинхронный accept, инициированный в start_accept() завершается.
// Она выполняет обработку запроса клиента и запуск нового акцептора.
void TcpServer::handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->start();
    }

    start_accept();
}

#endif