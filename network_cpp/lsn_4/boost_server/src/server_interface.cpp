#ifndef BOOST_SERVER_INTERFACE_CPP
#define BOOST_SERVER_INTERFACE_CPP

#include "server_interface.h"

std::shared_ptr<Interface> Interface::_instance = nullptr;

Interface::Interface(){}

std::shared_ptr<Interface> Interface::get_interface()
{
    if(!_instance)
        _instance = std::make_shared<Interface>(Interface());
    return _instance;
}

void Interface::start_server_on_port(int port)
{
    _port = port;

}

#endif