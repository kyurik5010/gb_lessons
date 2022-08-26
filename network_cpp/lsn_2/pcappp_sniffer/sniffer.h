#pragma once
#include "Layer_Inspector.h"
#include "PcapLiveDevice.h"
#include "PcapLiveDeviceList.h"
#include <mutex>

class SniffingDevice
{
private:
    pcpp::PcapLiveDevice* dev;
    static SniffingDevice* _sniffer_instance;
    LayerHandler* inspector;
    pcpp::RawPacketVector packetVec;
    std::string _interface_IP_address;
    SniffingDevice(std::string& ip_address): _interface_IP_address(ip_address)
    {
        dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(_interface_IP_address);
        if (dev == NULL)
            std::cerr << "Cannot find interface with IPv4 address '" << _interface_IP_address << "'" << std::endl;
        else
        {
            PrintDeviceInfo();
            inspector = LayerHandler::GetInstance();
        }
    };
public:
    static SniffingDevice* getLiveDeviceByAddr(std::string& IPaddress)
    {
        std::mutex m1;
        m1.lock();
        if(!_sniffer_instance)
            _sniffer_instance = new SniffingDevice(IPaddress);
        m1.unlock();
        return _sniffer_instance;
    }
    void PrintDeviceInfo(){
        std::cout
                << "Interface info:" << std::endl
                << "   Interface name:        " << dev->getName() << std::endl           // interface name
                << "   Interface description: " << dev->getDesc() << std::endl           // interface description
                << "   MAC address:           " << dev->getMacAddress() << std::endl     // interface MAC address
                << "   Default gateway:       " << dev->getDefaultGateway() << std::endl // default gateway
                << "   Interface MTU:         " << dev->getMtu() << std::endl;           // interface MTU
        if (dev->getDnsServers().size() > 0)
            std::cout << "   DNS server:            " << dev->getDnsServers().at(0) << std::endl; // Interface DNS
    }
    void setFilter(int port = 80, pcpp::ProtocolType proto = pcpp::TCP)
    {
        //filter:1 (capture only traffic on port 80)
        pcpp::PortFilter portFilter(port, pcpp::SRC_OR_DST); // pcpp::SRC_OR_DST - instruction to search on both
                                                                    // source and destnation port of each packet
        //filter:2 (capture only TCP traffic) other available:TCP, UDP, ICMP, VLAN, IPv4, IPv6, ARP, Ethernet, GRE, IGMP
        pcpp::ProtoFilter protocolFilter(proto);

        // create an AND filter to combine both filters - capture only TCP traffic on port 80
        pcpp::AndFilter andFilter;
        andFilter.addFilter(&portFilter);
        andFilter.addFilter(&protocolFilter);

        // set the filter on the device
        dev->setFilter(andFilter);
    }
    void sniff(int timingInSeconds)
    {
        if (!dev->open())
            std::cerr << "Cannot open device" << std::endl;
        dev->startCapture(packetVec);
        pcpp::multiPlatformSleep(timingInSeconds);
        dev->stopCapture();
        std::cout << "Sniffing complete: " << packetVec.size() << " packets captured." << std::endl;
        for (pcpp::RawPacketVector::ConstVectorIterator iter = packetVec.begin(); iter != packetVec.end(); iter++)
        {
            pcpp::Packet parsedPacket(*iter);
            inspector->ConsumePacket(parsedPacket);
        }

    }



    SniffingDevice(SniffingDevice& other) = delete;
    void operator =(SniffingDevice&) = delete;
    ~SniffingDevice()
    {
        dev->close();
        for(auto x: packetVec)
            delete x;
        delete _sniffer_instance;
    };
};
SniffingDevice* SniffingDevice::_sniffer_instance = nullptr;