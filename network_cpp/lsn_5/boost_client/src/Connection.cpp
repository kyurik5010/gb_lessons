


#include "Connection.h"

namespace fs = std::filesystem;
using namespace boost::asio;

Connection::Connection(const client_request &&task, io_context& context) :
_task(std::move(task)),
_io(context),
_sock(_io),
_ep(ip::address::from_string(_task.cr_ip_address), _task.cr_port)
{
    Connection::set_signal(TASK::STATE.BUSY);
    std::cout << "New task ID: " << std::this_thread::get_id() << std::endl;
    //начать работу с полученной структурой
}

Connection::~Connection() {
    while(_task.keep_connection)
    {
        continue;                                                               /**плейсхолдер, может не потребоваться*/
    }
    _sock.close();                                                                   /**возможно этого делать не стоит*/
}


//void Connection::setup_connection() {
//    // возможно этого не требуется
//}

void Connection::connect_to_server() {
    _sock.async_connect(_ep, [&](boost::system::error_code& error){
        if(0 != error.value())
        {
            Connection::set_signal(TASK::STATE.ERROR);
            std::cerr << "ERROR Socket connection " << error.value() << std::endl;
        }
    });
}

void Connection::send_request()
{
    _sock.async_send(boost::asio::buffer(_task.cr_path),[&](boost::system::error_code& error, std::size_t bytes_transferred)
    {
        if(0 != error.value())
        {
            Connection::set_signal(TASK::STATE.ERROR);
            std::cerr << "ERROR Send connection " << error.value() << std::endl;
        }
        else
            std::cout << bytes_transferred << " bytes sent to server" << std::endl;
    });
}

void Connection::recieve_file() {
    std::vector<char> buffer;
    fs::path file_path = fs::weakly_canonical(_task.cr_download);

    if(!exists(file_path))
    {
        Connection::set_signal(TASK::STATE.ERROR);
        std::cerr << "ERROR: '" << _task.cr_download << "' directory not found" << std::endl;
        return;
    }


    std::ofstream file_stream(file_path);

    _sock.async_read_some(boost::asio::buffer(buffer), [&](boost::system::error_code& error, std::size_t bytes_read)
    {
        if(0 != error.value())
        {
            Connection::set_signal(TASK::STATE.ERROR);
            std::cerr << "ERROR Read connection " << error.value() << std::endl;
        }
        else
            std::cout << bytes_read << " bytes recieved from server" << std::endl;
    });
}

void Connection::set_signal(int state) {
    _task.status = state;
}

bool Connection::task_complete() { return _task.status == TASK::STATE.READY; }

void Connection::kill(){ _task.keep_connection = false; }

const client_request* Connection::task_info() const { return &_task; }
