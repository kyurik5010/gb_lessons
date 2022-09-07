#ifndef BOOST_SERVER_SERVER_H
#define BOOST_SERVER_SERVER_H

#pragma once

#include "connection.h"

#include <ctime>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>


const int echo_port = 1300;

using namespace boost::asio;
class TcpServer
{
private:
    io_context& _io_context;
    ip::tcp::acceptor _acceptor;

public:
    TcpServer(boost::asio::io_context& io_context);

private:
    void start_accept();
    void handle_accept(TcpConnection::pointer new_connection, const boost::system::error_code& error);
};

#endif