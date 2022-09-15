//
//
// еще доделываю, надеюсь сегодня успеть

#include "Client.h"

namespace fs = std::filesystem;

Client::Client():
_io(boost::asio::io_context)
{}

Client::~Client() {

}

bool Client::set_download_dir(std::string name = "storage")
{
    auto cur_path = static_cast<std::string>(fs::current_path());
    _download_path = cur_path + '/' + name;
    std::cout << "Download path: " << _download_path << std::endl;
}

int Client::check_tasks() {
    int active_tasks = _tasks.size();

    for(int i=0; i<active_tasks; ++i)
        if(_tasks[i].task_complete())
        {

            Client::pop_task(i);
        }

    return 0;
}

std::string Client::get_file(std::string file_name)
{
    std::cout << "File name: ";
    std::cin >> file_name;
    std::cout << std::endl;
    std::string cur_path = static_cast<std::string>(fs::current_path());
    auto iter = std::find_if(cur_path.begin(), cur_path.end(), [=]( std::string part){
        return part == "boost_client/";
    });
    cur_path.erase(iter, cur_path.end());
    return cur_path + "boost_server/" + file_name;
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

void Client::push_task() {

}

void Client::pop_task(int task) {
    _tasks[task].kill();
    _tasks.erase(task);
}


