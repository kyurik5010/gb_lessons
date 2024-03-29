#include "connection.h"

#ifndef MAX_PATH
#define MAX_PATH (256)
#endif

#ifndef MAX_BUF
#define MAX_BUF (4096)
#endif

namespace INTERNAL{ //убрать потом, не удобно
    union MY_ERRORS{
        int BAD_PATH = 1;
        int NO_FILE;
        int NO_PATH;
   } my_errors;
}

NewCon::~NewCon()
{
    std::cout << "Connection '" << std::this_thread::get_id() << "' pending termination" << std::endl;
    while(_keep_alive)
    {
        std::this_thread::sleep_for(s{1});
    }
    std::cout << "Connection '" << std::this_thread::get_id() << "' closed" << std::endl;
}

NewCon::NewCon(io_context &connection, int port, ip::tcp::socket &&sock):

_state(STATE::RUNNING),
_keep_alive(true),
_port(port),
_sock(std::make_shared<ip::tcp::socket>(std::move(sock)))
{
    std::cout << _sock->remote_endpoint().address().to_string() << ":" << _sock->remote_endpoint().port() << " connected!" << std::endl;
}

std::string NewCon::get_request()
{

    std::this_thread::sleep_for(s{1});
    size_t test;
    if((test = _sock->available()) == 0)
    {
        std::cout << "ERROR No data on socket" << std::endl;
        return "";
    }
    else
        std::cout << test << " bytes available on socket" << std::endl;

    boost::asio::streambuf::mutable_buffers_type bufs = _buffer.prepare(MAX_PATH);

    _sock -> async_receive(bufs,
        [&](const boost::system::error_code& er, size_t bytes_read)
        {
            if (er)
            {
                if(er.value() == 2)
                {
                    std::cout << "End of incoming transmission " << std::endl;
                }
                else
                {
                    std::cout << "ERROR Socket read: " << er.value() << ": " << er.message() << std::endl;
                    _state = STATE::ERROR;
                }
            }
            else{
                std::cout << bytes_read << " bytes read from docket" << std::endl;

                _buffer.commit(bytes_read);
                std::cout << _buffer.in_avail() << " bytes bytes available to read from buffer" << std::endl;

                std::istream i_stream(&_buffer);
                std::getline(i_stream, _raw_line);

                std::cout << "Client request " << _raw_line << std::endl;
            }
        });

    std::this_thread::sleep_for(s{2});
    if(_raw_line.empty())
    {
        std::cout << "_raw_line still empty" << std::endl;
        std::this_thread::sleep_for(s{2});
    }
    return _raw_line;
}

std::optional<FS::path> NewCon::reinterpret(std::string raw)
{

    std::cout << "Analyzing clients' path: " << std::endl;
    std::string cur_path = static_cast<std::string>(FS::path(FS::current_path()));

    if(raw.empty())
    {
        std::cerr << "Raw path not provided" << std::endl;
        return std::nullopt;
    }

    auto pos = std::mismatch(cur_path.begin(), cur_path.end(), raw.begin());

    std::cout << "Clients request: " << std::string(pos.second, raw.end()) << std::endl;

    if(pos.second != cur_path.begin())
        _file_path = FS::weakly_canonical(raw);
    else
        _file_path = FS::weakly_canonical(cur_path + FS::path::preferred_separator + raw);

    return _file_path;
}

int NewCon::send_file()
{
    using namespace INTERNAL;

    if (std::nullopt == reinterpret(get_request()))
    {
        std::cerr << "ERROR Getting path to file" << std::endl;
        _state = STATE::ERROR;
        return 1;
    }

    else if( !(FS::exists(_file_path) && FS::is_regular_file(_file_path)) )
    {
        std::cerr << "ERROR Bad file" << std::endl;
        _state = STATE::ERROR;
        return 1;
    }

    std::ifstream input_fs(_file_path, std::istream::binary);

    if (!input_fs)
    {
        std::cerr << "ERROR Opening file" << std::endl;
        _state = STATE::ERROR;
        return 1;
    }

    std::string bufr;

    std::getline(input_fs, bufr);

    size_t bytes_to_send = bufr.length();

    std::cout << "Sending file " << _file_path << "..." << std::endl;

    std::cout << bufr << " prepared for transmission (" << bytes_to_send << " bytes)" << std::endl; // размер показывает корректный

    _sock ->async_send(boost::asio::buffer(bufr), [&](const boost::system::error_code& er, size_t written_to_socket)
    {
        if(er)
        {
            if (er.value() == 2)
                std::cout << "End of file" << std::endl;
            else
            {
                std::cout << "ERROR async_send: " << er.value() << " - " << er.message() << std::endl;
                _state = STATE::ERROR;
            }
        }
        else
        {
            bytes_to_send -= written_to_socket;
            std::cout << "Transmission complete: " << written_to_socket <<" bytes written to socket" << std::endl;
            input_fs.close();
        }
    });


    if(bytes_to_send != 0)
    {
        std::cout << "Waiting for transmission end" << std::endl;
        std::this_thread::sleep_for(s{4});
        if (bytes_to_send != 0) {
            std::cout << "Transmission failure" << std::endl;
            _state = STATE::ERROR;
        }
    }
    else
        _state = STATE::COMPLETE;
    return 0;
}

int NewCon::get_connection_state() const {
    return _state;
}

void NewCon::set_connection_state(int new_state) {
    _state = new_state;
}

