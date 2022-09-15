//
//
// еще доделываю, надеюсь сегодня успеть

#include "Client.h"

#include <utility>

namespace fs = std::filesystem;

Client::~Client() { std::cout << "Client stopping" << std::endl; }

Client::Client(std::string&& ip, int port, std::string custom_path):
_io(std::make_shared<boost::asio::io_context>()),
_port(port),
_server_ip(std::move(ip))
{
    if(!custom_path.empty())
    {
        if (!Client::set_download_dir(std::move(custom_path)))
            Client::~Client();
    }
    else
        Client::set_download_dir("storage");

    std::cout << "Client ready" << std::endl;
}


bool Client::set_download_dir(std::string&& name)
{
    auto cur_path = static_cast<std::string>(fs::current_path());
    _download_path = cur_path + '/' + name;

    if(fs::exists(_download_path))
        std::cout << "'/" << name << "' folder already exists"<< std::endl;
    else
    {
        if (!fs::create_directory(_download_path))
        {
            std::cerr << "ERROR Creating directory: " << _download_path << std::endl;
            return false;
        }
    }
    std::cout << "Download path: " << _download_path << std::endl;
    return true;
}

bool Client::check_tasks() {
    if(_tasks.empty())
    {
        std::cout << "No active operations" << std::endl;
        return false;
    }

    for(int i=0; i<_tasks.size(); ++i)
        if(_tasks[i]->task_complete())
        {
            std::cout << "'" << _tasks[i]->task_info()->cr_file_name << "' download complete" << std::endl;
            Client::pop_task(i);
        }
    std::cout << _tasks.size() << " operations in progress" << std::endl;
    return true;
}

bool Client::get_file(std::string&& file)
{
    Client::get_file_path(std::move(file));
    if (check_path(_file_path))
    {
        Client::push_task();
        return true;
    }
    else
        return false;

}

void Client::get_file_path(std::string&& file)
{
    _file_name = std::move(file);
    std::cout << "Serching for '" << _file_name << "'" << std::endl;
    std::string cur_path = static_cast<std::string>(fs::current_path());
    auto iter = cur_path.find("boost_client/");
    cur_path.erase(cur_path.begin()+static_cast<int>(iter), cur_path.end());
    _file_path = cur_path + "boost_server/" + _file_name;
}

bool Client::check_path(std::string& file_path) {
    fs::path check = fs::weakly_canonical(file_path);
    if (! (fs::exists(check) && fs::is_regular_file(check)) )
    {
        std::cerr << "ERROR: invalid path '" << file_path << "'" << std::endl;  //проверка на ошибки в Client::get_file()
        return false;
    }
    return true;
}

int Client::push_task()
{
    client_request task;
    task.cr_port = _port;
    task.cr_ip_address = _server_ip;
    task.cr_file_name = _file_name;
    task.cr_path = _file_path;
    task.cr_download = _download_path;
    task.status = TASK::STATE.BUSY;
    task.keep_connection = true;


    _tasks.emplace_back(std::make_shared<Connection>(std::move(task), *_io));

    std::thread thr (&Connection::connect_to_server, &(*_tasks.back()) );

     return 0;
}

void Client::pop_task(int task) {
    _tasks[task]->kill();
    _tasks.erase(_tasks.begin()+task);
}


