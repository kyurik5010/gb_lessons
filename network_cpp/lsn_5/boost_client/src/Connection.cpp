


#include "Connection.h"


namespace fs = std::filesystem;
using namespace boost::asio;
using s = std::chrono::seconds;




Connection::~Connection() {
    std::cout << "Connection '" << std::this_thread::get_id() << "' pending termination" << std::endl;
    while(_task.keep_connection)
    {
        std::this_thread::sleep_for(s{1});                                /**плейсхолдер, может не потребоваться*/
    }
    std::cout << "Connection '" << std::this_thread::get_id() << "' closed" << std::endl;
    _sock.close();                                                                   /**возможно этого делать не стоит*/
}

Connection::Connection(client_request &&task, std::shared_ptr<boost::asio::io_context> context) :
_task(std::move(task)),
_io(context),
_sock(*context)
//_ep(ip::address::from_string(_task.cr_ip_address), _task.cr_port)  //_task здесь может быть не инициализирована
{
    Connection::set_signal(TASK::STATE.BUSY);
    std::cout << "New task ID: " << std::this_thread::get_id() << std::endl;
}


void Connection::connect_to_server() {

    bool okay = false;

    if(Connection::establish_connection())
    {
        if (Connection::send_request())
        {
            if (Connection::recieve_file())
                okay = true;
        }
    }

    _io->run();

    std::this_thread::sleep_for(s{2});

    if(okay)
        Connection::set_signal(TASK::STATE.READY);
}

bool Connection::establish_connection()
{
    bool result;
    ip::tcp::endpoint end(ip::address::from_string(_task.cr_ip_address), _task.cr_port);

    _sock.async_connect(end, [&](boost::system::error_code error){
        if(error)
        {
            Connection::set_signal(TASK::STATE.ERROR);
            std::cout << "ERROR Socket connection " << error.value() << std::endl;
            result = false;
        }
        else
            result = true;
    });
    return result;
}

bool Connection::send_request()
{
    bool result;
    _sock.async_send(boost::asio::buffer(_task.cr_path),[&](boost::system::error_code error, std::size_t bytes_transferred)
    {
        if(error)
        {
            Connection::set_signal(TASK::STATE.ERROR);
            std::cout << "ERROR Send connection " << error.value() << std::endl;
            result = false;
        }
        else
        {
            std::cout << bytes_transferred << " bytes sent to server" << std::endl;
            result = true;
        }
    });
    return result;
}

bool Connection::recieve_file() {
    std::vector<char> buffer;
    fs::path file_path = fs::weakly_canonical(_task.cr_download);

    if(!exists(file_path))
    {
        Connection::set_signal(TASK::STATE.ERROR);
        std::cout << "ERROR: '" << _task.cr_download << "' directory not found" << std::endl;
        return false;
    }

    bool result;

    std::ofstream file_stream(file_path);

    _sock.async_read_some(boost::asio::buffer(buffer), [&](boost::system::error_code error, std::size_t bytes_read)
    {
        if(error)
        {
            Connection::set_signal(TASK::STATE.ERROR);
            std::cout << "ERROR Read connection " << error.value() << std::endl;
            result = false;
        }
        else
        {
            std::cout << bytes_read << " bytes recieved from server" << std::endl;
            result = true;
        }
    });
    return result;
}

void Connection::set_signal(int state)
{
    std::mutex mut;
    std::lock_guard<std::mutex> name{ mut };
    _task.status = state;
}

bool Connection::task_complete() { return _task.status == TASK::STATE.READY; }

void Connection::kill()
{
    std::this_thread::sleep_for(s{1});
    std::mutex mut;
    std::lock_guard<std::mutex> name{ mut };
    _task.keep_connection = false;
    //Connection::~Connection();
}

const client_request* Connection::task_info() const { return &_task; }
