#ifndef BOOST_SERVER_CONNECTION_H
#define BOOST_SERVER_CONNECTION_H


#pragma once

#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>

std::string make_daytime_string();

// Указатель shared_ptr и enable_shared_from_this нужны для того,
// чтобы сохранить объект tcp_connection до завершения выполнения операции.

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
private:
    boost::asio::ip::tcp::socket socket_;
    std::string message_;

private:
    TcpConnection(boost::asio::io_context& io_context);

    void handle_write(const boost::system::error_code& /*error*/, size_t bytes_transferred);

public:
    typedef std::shared_ptr<TcpConnection> pointer;

    static pointer create(boost::asio::io_context& io_context);

    boost::asio::ip::tcp::socket& socket();

    // В методе start(), вызывается asio::async_write(), отправляющий данные клиенту.
    // Здесь используется asio::async_write(), вместо ip::tcp::socket::async_write_some(), чтобы весь блок данных был гарантированно отправлен.
    void start();
};


#endif