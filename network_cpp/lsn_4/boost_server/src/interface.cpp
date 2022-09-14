
#include "interface.h"

namespace S_INTER
{
    std::shared_ptr<F_Server> server_instance = nullptr;
}

using namespace S_INTER;

Interface::Interface(){};
Interface::~Interface(){};

void Interface::launch_server_on_port(int port){
    if(!server_instance)
    {
        _port = port;
        server_instance = std::make_shared<F_Server>(port, _timer);
        server_instance->accept_connection();
    }
    else if(server_instance)
    {
        std::cout << "WARNING: restarting server on port " << port << std::endl;
        Interface::change_server_port(port);
    }
}

void Interface::change_server_port(int p)
{
    Interface::stop_server();
    server_instance = nullptr;
    Interface::launch_server_on_port(p);
    _port = p;
}

void Interface::stop_server()
{
    if(server_instance)
        server_instance->~F_Server();
    else return;
}

int Interface::get_port() const {
    return _port;
}

void Interface::set_timer(int new_timer)
{
    _timer = new_timer;
//    if(nullptr != server_instance)
//        server_instance->set_timer(new_timer);
}
