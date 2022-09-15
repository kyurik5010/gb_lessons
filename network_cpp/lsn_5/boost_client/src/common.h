/**
 * содержит основные инклуды и сигнальую структуру
 * передаваемую между клиентом и соединениями
 */

#ifndef BOOST_CLIENT_COMMON_H
#define BOOST_CLIENT_COMMON_H

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <memory>
#include <future>
#include <list>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>

namespace TASK
{
    static union state
    {
        int READY;                   // задача выполнена
        int ERROR;                   // ошибка
        int BUSY;                    // задача в работе
    }STATE;
}


#pragma pack (push, 1)
struct client_request
{
    int cr_port;                     // порт сервера
    std::string cr_ip_address;       // IP адрес сервера
    std::string cr_file_name;        // имя файла (здесь для удобства вывода информации в консоль)
                                     /** в целом удобней было бы передавать серверу только имя файла, который он должен найти в хранилище
                                         да и клиент может не всегда знать  какой у сервера путь к требуемому ему файлу*/
    std::string cr_path;             // путь к файлу сервера
    std::string cr_download;         // путь к месту сохранения файла
    int status;                      // статус задачи - парсится клиентом и соединением
    bool keep_connection = true;     /** может и ненадо */
};
#pragma pack (pop)



#endif //BOOST_CLIENT_COMMON_H
