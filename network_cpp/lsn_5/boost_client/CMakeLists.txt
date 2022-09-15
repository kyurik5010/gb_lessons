cmake_minimum_required(VERSION 3.2)

project("boost_client")

find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17 REQUIRED)

set(BOOST_INC "/usr/local/cellar/boost/1.79.0_1/include/")
include_directories(${BOOST_INC})

set(Source src/Client.cpp
        src/Connection.cpp
        )

add_executable(boost_client main.cpp ${Source})
target_include_directories(boost_client PUBLIC src)
