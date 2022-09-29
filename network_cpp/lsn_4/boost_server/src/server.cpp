#include "server.h"


F_Server::~F_Server()
{
    _io->stop();
}

F_Server::F_Server(int port, int timer):
        _io(std::make_shared<io_context>()),
        _timer(timer),
        _acceptor(*_io),
        _port(port)
{
    _acceptor.open(ip::tcp::v4());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(ip::tcp::endpoint(ip::tcp::v4(), port));
    _acceptor.listen();
    std::cout << "Server listening on port " << port << std::endl;
}

bool F_Server::check_client_operations()
{
    if(client_operations.empty())
    {
        return false;
    }

    for(int x=0, state; x < client_operations.size(); ++x, state = client_operations[x]->get_connection_state())
    {
        switch (state)
        {
            case STATE::ERROR:
            {
                std::cout << "WARNING: client operation failed" << std::endl;
                client_operations.erase(client_operations.begin() + x);
                continue;
            }
            case STATE::COMPLETE:
            {
                std::cout << "Client operation complete" << std::endl;
                client_operations.erase(client_operations.begin() + x);
                continue;
            }
            default:
                continue;
        }
    }
    return true;
}

void F_Server::deadline_handler(const boost::system::error_code & error)
{
    std::cout << "No connections recieved" << std::endl;
    std::this_thread::sleep_for(s{2});

    if(error)
        std::cerr << "ERROR timer: " << error.message() << std::endl;
    else if(!check_client_operations())
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

    _acceptor.async_accept(*sock, [&](const boost::system::error_code& error){
        if(error)
        {
            std::cerr << "ERROR Accepting connection: " << error.message() << std::endl;
            // в случае ошибки последующие соединения не ожидаются
        }   // но таймер будет перезапущен и по истечении минуты, если вектор пуст, accept_connection() завершится
        else
            F_Server::get_client(std::move(*sock));
    });

    deadline_timer t(*_io, boost::posix_time::seconds(_timer));
    /**аозможно стоит сделать вместо bind() лямбду*/
    t.async_wait(bind(&F_Server::deadline_handler, this, placeholders::error())); // если в течение 1 минуты список соединений пуст - сервер завершает работу
    _io->run();
}

void F_Server::get_client(ip::tcp::socket&& sock)
{

    client_operations.push_back(std::make_shared<NewCon>(*_io, _port, std::move(sock))); // вектор задач

    std::thread thr(&NewCon::send_file, &*client_operations.back());

    thr.detach();
                                                                                     /**!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    F_Server::accept_connection(); // ждать следующее подключение
}

void F_Server::set_timer(int new_timer)
{
    _timer = new_timer;
}