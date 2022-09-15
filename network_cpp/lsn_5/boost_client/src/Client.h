/**
 * Интерфейс
 * открывает сессию
 * создает соединения
 * закрывает соединения
 */


#ifndef BOOST_CLIENT_CLIENT_H
#define BOOST_CLIENT_CLIENT_H

#include "common.h"
#include "Connection.h"


class Client
{
private:
    boost::asio::io_context _io;
    std::string _file_name;
    std::string _download_path;
    int _port;
    std::string _server_ip;
    std::vector<Connection> _tasks;

public:
    Client();                // инициализирет контекст

    int check_tasks();       // проверяет флаги структур задач

    std::string get_file(std::string file_name); // получает от клиента имя файла

    bool set_download_dir(std::string name);

    bool check_path();       // проверяет правильность пути

    void push_task();        // создает объект соединения и передает ему структуру задачи

    void pop_task(int);         // ставит флаг keep_alive в false

    ~Client();
};


#endif //BOOST_CLIENT_CLIENT_H
