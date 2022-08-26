#include <iostream>
#include "sniffer.h"

int main(int argc, char* argv[])
{
    std::string IPaddress = "127.0.0.1";
    int timer = 10; //после старта программы нужно загрузить какую-нибудь страничку
    SniffingDevice* dev = SniffingDevice::getLiveDeviceByAddr(IPaddress);
    dev->sniff(timer);
    dev = nullptr;
    return 0;
};