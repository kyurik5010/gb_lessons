


#include "Connection.h"


namespace fs = std::filesystem;
using namespace boost::asio;
using s = std::chrono::seconds;




Connection::~Connection() {
    std::cout << "Connection '" << std::this_thread::get_id() << "' pending termination" << std::endl;
    while(_task.keep_connection)
    {
        std::this_thread::sleep_for(s{5});                                /**плейсхолдер, может не потребоваться*/
    }
    _sock.close();
    std::cout << "Connection '" << std::this_thread::get_id() << "' closed" << std::endl;
}

Connection::Connection(client_request &&task, std::shared_ptr<boost::asio::io_context> context) :
_task(std::move(task)),
_io(context),
_sock(*context)

{
    boost::system::error_code ec;

    _sock.open(ip::tcp::v4(), ec);

    if(ec)
    {
        Connection::set_signal(TASK::STATE.ERROR);
        std::cout << "ERROR Opening socket " << ec.value() << ':' << ec.message() << std::endl;
    }

//    ip::tcp::socket::keep_alive option;
//    ip::tcp::socket::reuse_address option2;
//
//    _sock.get_option(option, ec);
//    _sock.get_option(option2, ec);
//    if (ec)
//    {
//        Connection::set_signal(TASK::STATE.ERROR);
//        std::cout << "ERROR Setting socket options " << ec.value() << ':' << ec.message() << std::endl;
//    }
//    else
//    {
//        std::cout << "Socket options set" << std::endl;
//    }
    Connection::set_signal(TASK::STATE.BUSY);
    std::cout << "New task ID: " << std::this_thread::get_id() << std::endl;
}


void Connection::connect_to_server() {


    if(!Connection::establish_connection())
    {
        std::cout<< "ERROR Connection not established" << std::endl;
    }

    else if (!Connection::send_request())
    {
        std::cout<< "ERROR Request not sent" << std::endl;
    }

    if (!Connection::recieve_file())
    {
        std::cout << "ERROR File not recieved" << std::endl;
    }

    _io->run();
}

bool Connection::establish_connection()
{
    bool result;

    boost::system::error_code error;

    ip::tcp::endpoint end(ip::address::from_string(_task.cr_ip_address), _task.cr_port);

    _sock.connect(end, error);
        std::cout << "Attempting connection to server at addr: " << _task.cr_ip_address << ", port: " << _task.cr_port << std::endl;
        if(error)
        {
            Connection::set_signal(TASK::STATE.ERROR);
            std::cout << "ERROR Socket connection: "<< error.value() << " - " << error.message() << std::endl;
            result = false;
        }
        else
        {
            result = true;
            std::cout << "Connection established" << std::endl;
        }

    return result;
}

bool Connection::send_request()
{
    boost::system::error_code error;
    //_session.run = true;
    std::cout << "Request size - " << _task.cr_path.length() << " bytes" << std::endl;
    boost::asio::mutable_buffers_1 buf = boost::asio::buffer(_task.cr_path, _task.cr_path.length());

    boost::asio::async_write(_sock, buf, [&](const boost::system::error_code& error, size_t bytes_sent)
         {
             if (error)
             {
                 if (error.value() == 2)
                     std::cout << "End of file" << std::endl;
                 Connection::set_signal(TASK::STATE.ERROR);
                 std::cout << "ERROR Sending request: " << error.value() << " - " << error.message() << std::endl;
                 //_session.run = false;
             }
             else
             {
                 _session.total_bytes += bytes_sent;
                 std::cout << bytes_sent << " bytes sent to server" << std::endl;
             }
         });

    std::cout << _session.total_bytes << " bytes sent to server" << std::endl;
//    while(_session.run)
//         _sock.async_write_some(buf, [&](const boost::system::error_code& error, size_t bytes_sent)
//         {
//             if (error)
//             {
//                 if (error.value() == 2)
//                     std::cout << "End of file" << std::endl;
//                 Connection::set_signal(TASK::STATE.ERROR);
//                 std::cout << "ERROR Sending request: " << error.value() << " - " << error.message() << std::endl;
//                 _session.run = false;
//             }
//             else
//             {
//                 _session.total_bytes += bytes_sent;
//                 if(_session.total_bytes == _task.cr_path.length())
//                     _session.run = false;
//                 std::cout << bytes_sent << " bytes sent to server" << std::endl;
//             }
//         });
    if(error && error.value() != 2)
        return false;
    else
        return true;

}

bool Connection::wait_for_data()
{
    int wait = 10;
    while(_sock.available() == 0)
    {
        _sock.async_wait(boost::asio::ip::tcp::socket::wait_read ,[](const boost::system::error_code& error){
            if(error)
                std::cout << "ERROR Socket wait: " << error.value() << " - " << error.message() << std::endl;
        });
        if(--wait == 0)
            return false;
    }
    return true;
}

bool Connection::recieve_file() {
    std::vector<char> buffer;

    boost::system::error_code error;

    fs::path file_path = fs::weakly_canonical(_task.cr_download);

    if(!exists(file_path))
    {
        Connection::set_signal(TASK::STATE.ERROR);
        std::cout << "ERROR: '" << _task.cr_download << "' directory not found" << std::endl;
        return false;
    }

    std::ofstream output_fs(file_path);

    if(!_sock.is_open())
    {
        std::cout << "WARNING Socket closed" << std::endl;
    }

    if(_sock.available() == 0)
    {
        if(error)
        {
            std::cout << "ERROR: " << error.value() << " - " << error.message() << std::endl;
            Connection::set_signal(TASK::STATE.ERROR);
            return false;
        }
        std::cout << "Waiting for server transmission" << std::endl;
        if(!wait_for_data())
        {
            std::cout << "ERROR No data on socket" << std::endl;
            Connection::set_signal(TASK::STATE.ERROR);
            return false;
        }
        else
        {
            std::cout << "Waiting for server transmission" << std::endl;
        }
    }

    size_t bytes_read = 0;

    while(true)
    {
        bytes_read += _sock.read_some(boost::asio::buffer(buffer), error);
        if(error)
        {
            if(error.value() == 2)
            {
                std::cout << "End of incoming transmission" << std::endl;
                break;
            }
            else
            {
                std::cout << "ERROR Reading from server: " << error.value() << " - " << error.message() << std::endl;
                Connection::set_signal(TASK::STATE.ERROR);
                return false;
            }
        }
    }

    if(bytes_read > 0)
    {
        std::cout << bytes_read << " bytes received from server" << std::endl;
        output_fs.write(buffer.data(), bytes_read);
        output_fs.close();
        Connection::set_signal(TASK::STATE.READY);
        return true;
    }
    else
    {
        std::cout << "Closing with error" << std::endl;
        Connection::set_signal(TASK::STATE.ERROR);
        return false;
    }
}

void Connection::set_signal(int state)
{
    std::mutex mut;
    std::lock_guard<std::mutex> name{ mut };
    _task.status = state;
}

void Connection::kill()
{
    std::this_thread::sleep_for(s{1});
    std::mutex mut;
    std::lock_guard<std::mutex> name{ mut };
    _task.keep_connection = false;
}

const client_request* Connection::task_info() const { return &_task; }

bool Connection::task_complete() { return _task.status == TASK::STATE.READY; }
