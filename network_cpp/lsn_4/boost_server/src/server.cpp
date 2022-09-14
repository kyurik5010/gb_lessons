#include "server.h"

using ms = std::chrono::milliseconds;
using s = std::chrono::seconds;

namespace INTERNAL
{
    std::vector<std::shared_ptr<NewCon>> requests;
}

F_Server::~F_Server()
{
    _io->stop();
}

F_Server::F_Server(int port, int timer):
    _io(std::make_shared<io_context>()),
    _timer(timer),
    _acc(*_io)
{
    _acc.open(ip::tcp::v4());
    _acc.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acc.bind(ip::tcp::endpoint(ip::tcp::v4(), port));
    _acc.listen();
    std::cout << "Server listening on port " << port << std::endl;
}

int F_Server::check_client_operations()
{
    for(auto x = client_operations.begin(); x != client_operations.end(); ++x)
    {
        if(x->wait_for(ms{100}) == std::future_status::ready)
        {
            if(x->get() != 0)
                std::cout << "WARNING: client operation failed" << std::endl;
            client_operations.erase(x);
        }
    }
    return (!client_operations.empty()? 1 : 0);
}

void F_Server::deadline_handler(const boost::system::error_code & error)
{
    std::cout << "No connections recieved" << std::endl;
    std::this_thread::sleep_for(s{2});

    if(0 != error.value())
        std::cerr << "ERROR timer: " << error.value() << std::endl;
    else if(0 == check_client_operations())
    {
        std::cout << "No active client operations" << std::endl;
        std::this_thread::sleep_for(s{2});
        std::cout << "Server stopping" << std::endl;
        F_Server::~F_Server();
    }
    else
    {
        std::cout << client_operations.size() << "Client operations active" << std::endl;
        F_Server::accept_connection(); //если в векторе еще есть соединения - перезапустить таймер и ждать подключений
    }
}

void F_Server::accept_connection()
{

    std::cout << "Waiting for client connections..." << std::endl;

    socket_ptr sock(new ip::tcp::socket(*_io));

    _acc.async_accept(*sock,[&](const boost::system::error_code& error){
        if(0 != error.value())
        {
            std::cerr << "ERROR Accepting connection: " << error.value() << std::endl;
            // в случае ошибки последующие соединения не ожидаются
        }   // но таймер будет перезапущен и по истечении минуты, если вектор пуст, accept_connection() завершится
        else
            F_Server::get_client();
    });

    deadline_timer t(*_io, boost::posix_time::seconds(_timer));
    /**аозможно стоит сделать вместо bind() лямбду*/
    t.async_wait(bind(&F_Server::deadline_handler, this, placeholders::error())); // если в течение 1 минуты список соединений пуст - сервер завершает работу
    _io->run();
}

int create_request(std::shared_ptr<NewCon>&& connection)
{
    INTERNAL::requests.push_back(connection);
    return INTERNAL::requests.back()->send_file();
}

void F_Server::get_client()
{
    std::cout << "New connection established" << std::endl;

    std::shared_ptr<NewCon> connection = std::make_shared<NewCon>(*_io);

    std::future<int> future = std::async(std::launch::async, create_request, std::move(connection));

    client_operations.push_back(std::move(future)); // вектор задач

    F_Server::accept_connection(); // ждать следующее подключение
}

void F_Server::set_timer(int new_timer)
{
    _timer = new_timer;
}