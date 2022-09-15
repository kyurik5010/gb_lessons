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
#include <memory>
#include <future>
#include <list>
//#include <utility>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>

namespace TASK{
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
    std::string cr_path;             // путь к файлу сервера
    std::string cr_download;         // путь к месту сохранения файла
    int status;                      // статус задачи - парсится клиентом и соединением
    bool keep_connection = true;     /** может и ненадо */
};
#pragma pack (pop)



#endif //BOOST_CLIENT_COMMON_H
