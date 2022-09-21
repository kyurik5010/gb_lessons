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
_sock(std::make_shared<ip::tcp::socket>(std::move(sock)))                                                            // запомнить: сокет нужно передавать с сервера
{
    std::cout << _sock->remote_endpoint().address().to_string() << ":" << _sock->remote_endpoint().port() << " connected!" << std::endl;
}

std::string NewCon::get_request()
{

    boost::asio::streambuf::mutable_buffers_type bufs = _buffer.prepare(MAX_PATH);

    std::this_thread::sleep_for(s{1});

    if(_sock->available() == 0)
        std::cout << "ERROR No data on socket" << std::endl;

    size_t bytes_read = 0;

    while(bytes_read != MAX_PATH)
    {
        bytes_read += _sock->read_some(boost::asio::buffer(bufs), error);
        if (error)
        {
            if(error.value() == 2)
            {
                std::cout << "End of incoming transmission " << std::endl;
                break;
            }
            std::cout << "ERROR Socket read: " << error.value() << ": " << error.message() << std::endl;
            _state = STATE::ERROR;
        }
        else
        {
            std::cout << bytes_read << " bytes recieved from client" << std::endl;
        }
    }

    _buffer.commit(bytes_read);

    std::istream i_stream(&_buffer);

    std::getline(i_stream, _raw_line);

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

    std::ifstream f_stream(_file_path);

    if (!f_stream)
    {
        std::cerr << "ERROR Opening file" << std::endl;
        _state = STATE::ERROR;
        return 1;
    }

    std::cout << "Sending file " << _file_path << "..." << std::endl;

    std::vector<std::vector<char>> buffer;

    std::cout << "Preparing data for transmission" << std::endl;

    char c;
    while(f_stream)
    {
        std::vector<char> arr;
        while (arr.size() < MAX_BUF && !f_stream.eof())
        {
            f_stream.get(c);
            arr.push_back(c);
        }
        buffer.push_back(arr);
    }

    size_t bytes_count = 0;

    for(auto x : buffer)
        bytes_count += x.size();

    std::cout << buffer.size() << " chunks of data prepared for transmission (" << bytes_count << " bytes)" << std::endl;

    while (bytes_count)
    {
        size_t bytes_written = 0;
        bytes_written += _sock->write_some(buffer, error);
        if(error)
        {
            if(error.value() == 2)
            {
                std::cout << "End of outgoing buffer" << std::endl;
                break;
            }
            else if(error.value() == 54) // Connection reset by peer
            {
                bytes_written = resend_data(buffer);

            }
            else
            {
                std::cerr << "ERROR Socket send: " << error.value() << " - " << error.message() << std::endl;
                _state = STATE::ERROR;
                return 1;
            }
        }
        else
            std::cout << bytes_written << " written to socket" << std::endl;
        bytes_count -= bytes_written;
    }
    if(bytes_count <= 0)
        _state = STATE::COMPLETE;
    else
        _state = STATE::ERROR;
    return 0;
}

size_t NewCon::resend_data(std::vector<std::vector<char>> &buffer)
{
    size_t bytes_written = 0;
    bytes_written += _sock->write_some(boost::asio::buffer(buffer), error);
    if(error)
    {
        if(error.value() == 2)
        {
            std::cout << "End of outgoing buffer" << std::endl;
            break;
        }
        else if(error.value() == 54) // Connection reset by peer
        {
            resend_data();
        }
        else
        {
            std::cerr << "ERROR Socket send: " << error.value() << " - " << error.message() << std::endl;
            _state = STATE::ERROR;
            return 1;
        }
    }
    return bytes_written;
}

int NewCon::get_connection_state() const {
    return _state;
}

void NewCon::set_connection_state(int new_state) {
    _state = new_state;
}

