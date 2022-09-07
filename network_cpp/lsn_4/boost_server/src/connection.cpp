#ifndef BOOST_SERVER_CONNECTION_CPP
#define BOOST_SERVER_CONNECTION_CPP

#include "connection.h"

std::string make_daytime_string()
{
    using namespace std; // time_t, time и ctime;
    time_t now = time(0);
    return ctime(&now);
}

using namespace boost::asio;

typedef std::shared_ptr<TcpConnection> pointer;

TcpConnection::pointer create(boost::asio::io_context& io_context)
{
    return pointer(new TcpConnection(io_context));
}

ip::tcp::socket& TcpConnection::socket()
{
    return socket_;
}

void TcpConnection::start()
{
    // The data to be sent is stored in the class member message_ as we need to keep the data valid until the asynchronous operation is complete.
    message_ = make_daytime_string();
    auto s = shared_from_this();

    // Здесь вместо boost::bind используется std::bind, чтобы уменьшить число зависимостей от Boost.
    // Он не работает с плейсхолдерами из Boost.
    // В комментариях указаны альтернативные плейсхолдеры.
    boost::asio::async_write(socket_, boost::asio::buffer(message_),
            // handle_write() выполнит обработку запроса клиента.
                             [s] (const boost::system::error_code& error, size_t bytes_transferred)
                             {
                                 s->handle_write(error, bytes_transferred);
                             }
    );
}

TcpConnection::TcpConnection(boost::asio::io_context& io_context) : socket_(io_context) {}

void TcpConnection::handle_write(const boost::system::error_code& /*error*/, size_t bytes_transferred)
{
    std::cout << "Bytes transferred: " << bytes_transferred << std::endl;
}

#endif