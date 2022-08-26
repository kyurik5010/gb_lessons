cmake_minimum_required(VERSION 3.10)

project(PCPP_sniffer CXX)

#специфичные для мака библиотеки требуемые Pcap++.a
find_library(FoundationLib CoreFoundation)
message("\n\nLIB: ${FoundationLib}\n")
find_library(SystemConfigurationLib SystemConfiguration)
message("\n\nLIB: ${SystemConfigurationLib}\n")

include_directories(/usr/local/include/pcapplusplus/)
include_directories(/usr/local/lib/)
set(PCPP_INCLUDES_DIR /usr/local/include/pcapplusplus/)
set(LIBS_DIR /usr/local/lib)

set(PCPP_LIBS
              ${LIBS_DIR}/libPcap++.a
        ${LIBS_DIR}/libPacket++.a
        ${LIBS_DIR}/libCommon++.a
              )

set(OTHER /usr/local/Cellar/libpcap/1.10.1/lib/libpcap.a #требуется подключение библиотеки tcpdump
          ${LIBS_DIR}/libevent_pthreads.a
          ${LIBS_DIR}/libevent.a
          )

add_executable(PCPP_sniffer main.cpp sniffer.h Layer_Inspector.h)
target_link_libraries(PCPP_sniffer PUBLIC ${PCPP_LIBS} ${OTHER} ${FoundationLib} ${SystemConfigurationLib})
target_include_directories(PCPP_sniffer PUBLIC ${PCPP_INCLUDES_DIR})

message("\nPcapPlusPlus build complete \n")