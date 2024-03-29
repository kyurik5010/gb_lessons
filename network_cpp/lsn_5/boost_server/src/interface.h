
#ifndef BOOST_SERVER_INTERFACE_H
#define BOOST_SERVER_INTERFACE_H

#pragma once
#include "common.h"
#include "server.h"



class Interface
{
private:
    int _timer = 60;
    int _port;
public:
    Interface();
    ~Interface();
    void launch_server_on_port(int);
    void change_server_port(int);
    void set_timer(int);
    void stop_server();
    int get_port() const;
};


#endif //BOOST_SERVER_INTERFACE_H
