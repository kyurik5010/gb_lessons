/**
 * устанавливает соединение с адресом и портом сервера, а также путем к файлу, указанными в полученной структуре
 * передает серверу путь
 * получает файл и сохраняет в текущую дирректорию
 * возвращает сигнальную структуру
 */


#ifndef BOOST_CLIENT_CONNECTION_H
#define BOOST_CLIENT_CONNECTION_H


#include "common.h"

class Connection
{
private:
    boost::asio::io_context& _io;
    boost::asio::ip::tcp::socket _sock;
    boost::asio::ip::tcp::endpoint _ep;
    client_request _task;
public:
    Connection(const client_request&&, boost::asio::io_context&);

    //void setup_connection();  // инициализирует и настраивает сокет

    void connect_to_server(); // выполняет соединение с сервером

    void send_request();      // посылает запрос

    void recieve_file();      // получает и сохраняет файл

    void set_signal(int);     // устанавливает status в структуре запроса для сигнализирования об окончании работы соединения

    bool task_complete();     // парсит значение result в структуре client_request

    const client_request* task_info() const; //возвращает  ссылку на структуру задачи

    void kill();              // ставит флаг keep_connection в false

    ~Connection();



};


#endif //BOOST_CLIENT_CONNECTION_H
