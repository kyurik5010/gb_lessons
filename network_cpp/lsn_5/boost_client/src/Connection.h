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
    std::shared_ptr<boost::asio::io_context> _io;
    client_request _task;
    struct __session{
        size_t total_bytes = 0;
        bool run;
    }_session;

public:
    Connection(client_request&&, std::shared_ptr<boost::asio::io_context> context);

    void connect_to_server();    // выполняет соединение с сервером

    bool establish_connection(); //выполняет содеинение с сервером

    bool wait_for_data();         // цикл ожидания появления данных на сокете

    bool send_request();         // посылает запрос

    void check_file( std::filesystem::path& );

    bool recieve_file();         // получает и сохраняет файл

    void set_signal(int);        // устанавливает status в структуре запроса для сигнализирования об окончании работы соединения

    bool task_complete();        // парсит значение result в структуре client_request (не используется)

    [[nodiscard]] const client_request* task_info() const; //возвращает  ссылку на структуру задачи

    void kill();              // ставит флаг keep_connection в false

    ~Connection();



};


#endif //BOOST_CLIENT_CONNECTION_H
