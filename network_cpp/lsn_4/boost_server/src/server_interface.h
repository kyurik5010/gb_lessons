#ifndef BOOST_SERVER_INTERFACE_H
#define BOOST_SERVER_INTERFACE_H

#include "server.h"

class Interface{
    int _port;
    static std::shared_ptr<Interface> _instance;

    Interface();
    ~Interface();
public:
    static std::shared_ptr<Interface> get_interface();

    void start_server_on_port(int) ;

};

#endif
