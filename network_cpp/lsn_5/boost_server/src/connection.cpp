#include "connection.h"

#ifndef MAX_PATH
#define MAX_PATH (256)
#endif

#ifndef MAX_BUF
#define MAX_BUF (4096)
#endif

namespace INTERNAL{
    union MY_ERRORS{
        int BAD_PATH = 1;
        int NO_FILE;
        int NO_PATH;
   } my_errors;
}

NewCon::~NewCon() {}

NewCon::NewCon(io_context &connection): _client(connection), _state(STATE::RUNNING) {}

std::string NewCon::get_request()
{
    std::vector<char> buf;
    std::string raw_path;

    _client.async_read_some(boost::asio::buffer(buf),[&]
        (const boost::system::error_code& error, size_t bytes_transferred)
        {
            if(!error)
            {
                std::cout << bytes_transferred << " bytes recieved from client" << std::endl;
                auto iter = std::find_if(buf.begin(), buf.end(), [](char sym)
                {
                    return sym == '\n' || sym == '\r';
                });

                    if (buf.end() != iter)
                        *iter = '\0';
            }
            else
            {
                std::cerr << "ERROR Socket read: " << error.message() << std::endl;
                _state = STATE::ERROR;
            }
        });

    std::copy(buf.begin(), buf.end(), raw_path.begin());
    std::cout << "Client request: " << raw_path << std::endl;
    return raw_path;
}

std::optional<FS::path> NewCon::reinterpret(std::string raw)
{

    std::string cur_path = static_cast<std::string>(FS::path(FS::current_path()));

    if(raw.empty())
    {
        std::cerr << "Raw path not provided" << std::endl;
        return std::nullopt;
    }

    std::size_t found = raw.find(cur_path);

    if(found != std::string::npos)
        raw = raw.substr(found, cur_path.length());

    return _file_path = FS::weakly_canonical(cur_path + FS::path::preferred_separator + raw);
}

int NewCon::send_file()
{
    using namespace INTERNAL;
    if(std::nullopt == reinterpret(get_request()))
    {
        std::cerr << "ERROR Getting path to file" << std::endl;
        _state = STATE::ERROR;
        return my_errors.NO_PATH;
    }

    if ( !(FS::exists(_file_path) && FS::is_regular_file(_file_path)) )
    {
        std::cerr << "ERROR Opening file" << std::endl;
        _state = STATE::ERROR;
        return my_errors.BAD_PATH;
    }

    std::vector<char> buffer(MAX_BUF);
    std::ifstream f_stream(_file_path);

    if (!f_stream)
    {
        std::cerr << "ERROR Opening file" << std::endl;
        _state = STATE::ERROR;
        return my_errors.NO_FILE;
    }

    std::cout << "Sending file " << _file_path << "..." << std::endl;

    while (f_stream)
    {
        f_stream.read(&buffer[0], buffer.size()); // читаем в буфер из файлового потока по 4096 байт

        _client.async_send(boost::asio::buffer(buffer), [&]
                (const boost::system::error_code& error, size_t bytes_transferred)
        {
            if(error)
            {
                std::cerr << "ERROR Socket send: " << error.message() << std::endl;
                _state = STATE::ERROR;
            }
        });
    }
    _state = STATE::COMPLETE;
    return 0;
}

