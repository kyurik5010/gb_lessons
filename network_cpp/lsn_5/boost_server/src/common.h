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


namespace STATE
{
    int COMPLETE = 0;
    int ERROR = 1;
    int RUNNING = 2;
}


#endif //BOOST_SERVER_COMMON_H
