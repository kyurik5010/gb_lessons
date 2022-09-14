cmake_minimum_required(VERSION 3.2)

project("boost_server")

find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17 REQUIRED)

set(BOOST_INC "/usr/local/cellar/boost/1.79.0_1/include/")
include_directories(${BOOST_INC})

set(Source src/interface.cpp
        src/server.cpp
        src/connection.cpp
        )

add_executable(serv main.cpp ${Source})
target_include_directories(serv PUBLIC src)
