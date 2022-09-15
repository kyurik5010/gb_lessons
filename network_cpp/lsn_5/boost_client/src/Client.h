#ifndef BOOST_CLIENT_CLIENT_H
#define BOOST_CLIENT_CLIENT_H

#include "common.h"
#include "Connection.h"


class Client
{
private:
    std::shared_ptr<boost::asio::io_context> _io;

    std::string _file_name;
    std::string _file_path;
    std::string _download_path;
    int _port;
    std::string _server_ip;

    std::vector<std::shared_ptr<Connection>> _tasks;

public:
    Client(std::string&&, int, std::string = ""); // инициализирет контекст создает дирректорию для сохранения

    bool check_tasks();                         // проверяет флаги структур задач

    void get_file_path(std::string&&);          // записывает имя файла

    bool set_download_dir(std::string&&);       // устанаваливает дирректорию для загрузки получаемых файлов

    bool get_file(std::string&&);               // запускает по очередности методы для получения файлов

    bool check_path(std::string&);              // проверяет правильность пути

    int push_task();                            // создает объект соединения и передает ему структуру задачи

    void pop_task(int);                         // ставит флаг keep_alive в false

    ~Client();
};


#endif //BOOST_CLIENT_CLIENT_H
