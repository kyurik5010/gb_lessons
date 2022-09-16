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
    boost::asio::ip::tcp::socket _sock;
    //boost::asio::ip::tcp::endpoint _ep;
    std::shared_ptr<boost::asio::io_context> _io;
    client_request _task;
public:
    Connection(client_request&&, std::shared_ptr<boost::asio::io_context> context);

    void connect_to_server(); // выполняет соединение с сервером

    bool establish_connection();

    bool send_request();      // посылает запрос

    bool recieve_file();      // получает и сохраняет файл

    void set_signal(int);     // устанавливает status в структуре запроса для сигнализирования об окончании работы соединения

    bool task_complete();     // парсит значение result в структуре client_request

    [[nodiscard]] const client_request* task_info() const; //возвращает  ссылку на структуру задачи

    void kill();              // ставит флаг keep_connection в false

    ~Connection();



};


#endif //BOOST_CLIENT_CONNECTION_H
