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
        Connection::set_signal(STATE::ERROR);
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
    Connection::set_signal(STATE::BUSY);
    std::cout << "New task ID: " << std::this_thread::get_id() << std::endl;
}


void Connection::connect_to_server() {


    if(!Connection::establish_connection())
    {
        std::cout<< "ERROR Connection not established" << std::endl;
    }

    _sock.async_wait(_sock.wait_write,[&](const boost::system::error_code& error)
    {
        if(!error)
        {
            Connection::send_request();
        }
        else
            std::cout << "ERROR wait write: " << error.value() << " - " << error.message() << std::endl;
    });

    _sock.async_wait(_sock.wait_read,[&](const boost::system::error_code& error)
    {
        if(!error)
        {
            Connection::Connection::recieve_file();
        }
        else
            std::cout << "ERROR wait read: " << error.value() << " - " << error.message() << std::endl;
    });

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
            Connection::set_signal(STATE::ERROR);
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
    std::cout << "Request size - " << _task.cr_path.length() << " bytes" << std::endl;

    boost::asio::mutable_buffers_1 buf = boost::asio::buffer(_task.cr_path, _task.cr_path.length());

    size_t total_bytes_sent = 0;

    boost::asio::async_write(_sock, buf, [&](const boost::system::error_code& error, size_t bytes_sent)
         {
             if (error && error.value() != 2)
             {
                 if(error.value() == 2)
                     std::cout << "End of file" << std::endl;
                 else
                 {
                     Connection::set_signal(STATE::ERROR);
                     std::cout << "ERROR Sending request: " << error.value() << " - " << error.message() << std::endl;
                 }
             }
             else
             {
                 total_bytes_sent += bytes_sent;
                 std::cout << "Request pushed to server (" << bytes_sent << " bytes)" << std::endl;
             }
         });

//    std::this_thread::sleep_for(s{10}); // не помогает
//    if(total_bytes_sent == 0)
//    {
//        std::cout << "Request not sent yet ..." << std::endl;
//        std::this_thread::sleep_for(s{10});
//
//        if(total_bytes_sent == 0)
//            return false;
//        else
//        {
//            std::cout << "Request sent successfully" << std::endl;
//            return true;
//        }
//    }
//    else
    return true;
}

bool Connection::wait_for_data()
{
    int wait = 10;

    _sock.async_wait(boost::asio::ip::tcp::socket::wait_read,[](const boost::system::error_code& error)
    {
        if(error)
            std::cout << "ERROR Socket wait: " << error.value() << " - " << error.message() << std::endl;
    });

    while(wait)
    {
        size_t temp = _sock.available();
        if(!temp)
        {
            --wait;
            std::this_thread::sleep_for(s{2});
            continue;
        }
        else
        {
            std::cout << temp << " bytes available to read on socket" << std::endl;
            return true;
        }
    }
    return false;
}



bool Connection::recieve_file() {
    std::cout << "Downloading file " << _task.cr_file_name << std::endl;

    //boost::system::error_code error;

    fs::path file_path = fs::weakly_canonical(_task.cr_download);

    if(exists(file_path))
    {
        std::cout << "WARNING: '" << _task.cr_download << "' file already exists, rewriting" << std::endl;
    }

    std::ofstream output_fs(file_path, std::ofstream::binary);

    if(!output_fs.is_open())
    {
        std::cout << "WARNING File stream not open" << std::endl;
    }

    if(!_sock.is_open())
    {
        std::cout << "WARNING Socket closed" << std::endl;
    }

    std::cout << _sock.available() << " bytes available on socket" << std::endl;

    boost::asio::streambuf buffer;

    boost::asio::streambuf::mutable_buffers_type bufs = buffer.prepare(MAX_BUF);

    size_t total_bytes_recieved;

    boost::system::error_code er;

    total_bytes_recieved = _sock.receive(boost::asio::buffer(bufs));

    std::cout << "Transmission in progress" << std::endl;
    if(er && er.value() != 2)
    {
        std::cout << "ERROR Reading from server: " << er.value() << " - " << er.message() << std::endl;
        Connection::set_signal(STATE::ERROR);
        return false;
    }

    std::cout << total_bytes_recieved << " total bytes recieved, " << _sock.available() << " more to go" << std::endl;

    buffer.commit(total_bytes_recieved);

    std::cout << buffer.in_avail() << " bytes available to read from streambuf" <<std::endl;

    std::istream is(&buffer);

    std::string result;

    std::getline(is, result);

    std::cout << result << std::endl;

    output_fs << result;

    output_fs.close();

    Connection::set_signal(STATE::READY);

    return true;
    /**

    Асинхронный вариант по какой-то причине как-будто ломает буфер (как streambuf так и вектор к примеру).
    При попытке вывести в консоль его размер (как в строке 241) выводится размер +- 140 терабайт и любая попытка
    содержимого в поток приводит к segmentation fault. В случае использования вектора _sock.async_receive()
    меняет его размерность, например я получил следующий вывод до и после (в хендлере) работы функции:

    0 -size|capacity- 20
    140704368628312 -size|capacity- 0

    При этом из сокета данные не считываются.

     */
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

bool Connection::task_complete() { return _task.status == STATE::READY; }

void Connection::check_file(std::filesystem::path& file_path) // прототип для переименовывания повторяющихся файлов, не используется
{
    std::string temp = static_cast<std::string>(file_path);
    if(exists(file_path))
    {
        std::cout << "WARNING: '" << _task.cr_download << "' file already exists" << std::endl;
    }
//    auto iter = std::find(temp.end(), temp.begin(), '.');
//    if(iter != temp.begin() && atoi(*iter-1)  )


}