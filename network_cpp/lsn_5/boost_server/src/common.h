#ifndef BOOST_SERVER_COMMON_H
#define BOOST_SERVER_COMMON_H

#pragma once

#include <iostream>
#include <memory>
#include <array>
#include <future>
#include <algorithm>
#include <optional>
#include <filesystem>
#include <fstream>
#include <vector>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>


using ms = std::chrono::milliseconds;
using s = std::chrono::seconds;

namespace STATE
{
    const int COMPLETE = 0;
    const int ERROR = 1;
    const int RUNNING = 2;
}


#endif //BOOST_SERVER_COMMON_H
