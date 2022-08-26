#include <iostream>
#include "PcapLiveDeviceList.h"
#include "SystemUtils.h"
#include "Packet.h"
#include "EthLayer.h"
#include "IPv4Layer.h"
#include "TcpLayer.h"
#include "HttpLayer.h"
#include "PcapFileDevice.h" // contains all the API for reading and writing packets from/to files

struct PacketStats {
    /**
     * назарел, авамис, насобэк - что-то одно, по одному пшику в каждую ноздрю 2 раза в день;
     * кабинет 608
     * */
    // затычка для структуры из туториала
    std::string results;
    std::string printTcpOptionType(pcpp::TcpOptionType optionType)
    {
        switch (optionType)
        {
            case pcpp::PCPP_TCPOPT_NOP:
                return "NOP";
            case pcpp::PCPP_TCPOPT_TIMESTAMP:
                return "Timestamp";
            default:
                return "Other";
        }
    }              // добавлено
    std::string printTcpFlags(pcpp::TcpLayer* tcpLayer)
    {
        std::string result = "";
        if (tcpLayer->getTcpHeader()->synFlag == 1)
            result += "SYN ";
        if (tcpLayer->getTcpHeader()->ackFlag == 1)
            result += "ACK ";
        if (tcpLayer->getTcpHeader()->pshFlag == 1)
            result += "PSH ";
        if (tcpLayer->getTcpHeader()->cwrFlag == 1)
            result += "CWR ";
        if (tcpLayer->getTcpHeader()->urgFlag == 1)
            result += "URG ";
        if (tcpLayer->getTcpHeader()->eceFlag == 1)
            result += "ECE ";
        if (tcpLayer->getTcpHeader()->rstFlag == 1)
            result += "RST ";
        if (tcpLayer->getTcpHeader()->finFlag == 1)
            result += "FIN ";

        return result;
    }                         // добавлено
    std::string getProtocolTypeAsString(pcpp::ProtocolType protocolType)
    {
        switch (protocolType)
        {
            case pcpp::Ethernet:
                return "Ethernet";
            case pcpp::IPv4:
                return "IPv4";
            case pcpp::TCP:
                return "TCP";
            case pcpp::HTTPRequest:
            case pcpp::HTTPResponse:
                return "HTTP";
            default:
                return "Unknown";
        }
    }        // добавлено
    std::string printHttpMethod(pcpp::HttpRequestLayer::HttpMethod httpMethod)
    {
        switch (httpMethod)
        {
            case pcpp::HttpRequestLayer::HttpGET:
                return "GET";
            case pcpp::HttpRequestLayer::HttpPOST:
                return "POST";
            default:
                return "Other";
        }
    }  // добавлено
    int consumePacket(pcpp::Packet& parsedPacket)
    {
        for (pcpp::Layer* curLayer = parsedPacket.getFirstLayer(); curLayer != NULL; curLayer = curLayer->getNextLayer())
        {
            std::cout
                    << "Layer type: " << getProtocolTypeAsString(curLayer->getProtocol()) << "; " // get layer type
                    << "Total data: " << curLayer->getDataLen() << " [bytes]; " // get total length of the layer
                    << "Layer data: " << curLayer->getHeaderLen() << " [bytes]; " // get the header length of the layer
                    << "Layer payload: " << curLayer->getLayerPayloadSize() << " [bytes]" // get the payload length of the layer (equals total length minus header length)
                    << std::endl;
        }
        // now let's get the Ethernet layer
        pcpp::EthLayer* ethernetLayer = parsedPacket.getLayerOfType<pcpp::EthLayer>();
        if (ethernetLayer == NULL)
        {
            std::cerr << "Something went wrong, couldn't find Ethernet layer" << std::endl;
            return 1;
        }
        // print the source and dest MAC addresses and the Ether type
        std::cout << std::endl
                  << "Source MAC address: " << ethernetLayer->getSourceMac() << std::endl
                  << "Destination MAC address: " << ethernetLayer->getDestMac() << std::endl
                  << "Ether type = 0x" << std::hex << pcpp::netToHost16(ethernetLayer->getEthHeader()->etherType)
                  << std::endl;


        // let's get the IPv4 layer
        auto* ipLayer = parsedPacket.getLayerOfType<pcpp::IPv4Layer>();
        if (ipLayer == NULL)
        {
            std::cerr << "Something went wrong, couldn't find IPv4 layer" << std::endl;
            return 1;
        }
        // print source and dest IP addresses, IP ID and TTL
        std::cout << std::endl
                  << "Source IP address: " << ipLayer->getSrcIPAddress() << std::endl
                  << "Destination IP address: " << ipLayer->getDstIPAddress() << std::endl
                  << "IP ID: 0x" << std::hex << pcpp::netToHost16(ipLayer->getIPv4Header()->ipId) << std::endl
                  << "TTL: " << std::dec << (int)ipLayer->getIPv4Header()->timeToLive << std::endl;


        // let's get the TCP layer
        auto* tcpLayer = parsedPacket.getLayerOfType<pcpp::TcpLayer>();
        if (tcpLayer == NULL)
        {
            std::cerr << "Something went wrong, couldn't find TCP layer" << std::endl;
            return 1;
        }
        // print TCP source and dest ports, window size, and the TCP flags that are set in this layer
        std::cout << std::endl
                  << "Source TCP port: " << tcpLayer->getSrcPort() << std::endl
                  << "Destination TCP port: " << tcpLayer->getDstPort() << std::endl
                  << "Window size: " << pcpp::netToHost16(tcpLayer->getTcpHeader()->windowSize) << std::endl
                  << "TCP flags: " << printTcpFlags(tcpLayer) << std::endl;
        // go over all TCP options in this layer and print its type
        std::cout << "TCP options: ";
        for (pcpp::TcpOption tcpOption = tcpLayer->getFirstTcpOption(); tcpOption.isNotNull(); tcpOption = tcpLayer->getNextTcpOption(tcpOption))
        {
            std::cout << printTcpOptionType(tcpOption.getTcpOptionType()) << " ";
        }
        std::cout << std::endl;


        // let's get the HTTP request layer
        auto* httpRequestLayer = parsedPacket.getLayerOfType<pcpp::HttpRequestLayer>();
        if (httpRequestLayer == NULL)
        {
            std::cerr << "Something went wrong, couldn't find HTTP request layer" << std::endl;
            return 1;
        }
        // print HTTP method and URI. Both appear in the first line of the HTTP request
        std::cout << std::endl
                  << "HTTP method: " << printHttpMethod(httpRequestLayer->getFirstLine()->getMethod()) << std::endl
                  << "HTTP URI: " << httpRequestLayer->getFirstLine()->getUri() << std::endl;
        // print values of the following HTTP field: Host, User-Agent and Cookie
        std::cout
                << "HTTP host: " << httpRequestLayer->getFieldByName(PCPP_HTTP_HOST_FIELD)->getFieldValue() << std::endl
                << "HTTP user-agent: " << httpRequestLayer->getFieldByName(PCPP_HTTP_USER_AGENT_FIELD)->getFieldValue() << std::endl
                << "HTTP cookie: " << httpRequestLayer->getFieldByName(PCPP_HTTP_COOKIE_FIELD)->getFieldValue() << std::endl;
        // print the full URL of this request
        std::cout << "HTTP full URL: " << httpRequestLayer->getUrl() << std::endl;
        return 0;
    };                              // добавлено

    void printToConsole()
    {
        if(results == "")
        {
            std::cout << "Printing virtual results" << std::endl;
            results = "old";
        }
        else if(results == "new results")
        {
            std::cout << "Printing new virtual results" << std::endl;
            results = "old";
        }
        else
        {
            std::cout << "Printing old virtual results" << std::endl;
        }
    }
    void clear()
    {
        std::cout << "Clearing virtual results" << std::endl;
        results = "new results";
    }
};

static void onPacketArrives(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
    /**
    A callback function for the async capture which is called each time a packet is captured

    void* cookie - is a pointer to an object supplied by the user at the beginning of the packet capture (a cookie)
    A cookie is needed in order to pass objects (or data) between our main code and the callback running in
    a static context-less environment. The cookie is a way of providing a context to our callback function.
    **/
    // extract the stats object form the cookie
    PacketStats* packetStats = (PacketStats*)cookie; // PacketStats структура из туториала для подсчета статистики перехваченных пакетов
    // (PacketStats*)cookie - это си-стайл кастование, если что ...
    // parsed the raw packet
    pcpp::Packet parsedPacket(packet);

    // collect stats from packet
    packetStats->consumePacket(parsedPacket);
}

/**
* a callback function for the blocking mode capture which is called each time a packet is captured
*/
static bool onPacketArrivesBlockingMode(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
    // extract the stats object form the cookie
    PacketStats* packetStats = (PacketStats*)cookie;

    // parsed the raw packet
    pcpp::Packet parsedPacket(packet);

    // collect stats from packet
    packetStats->consumePacket(parsedPacket);

    // return false means we don't want to stop capturing after this callback
    return false;
}

int main(int argc, char* argv[]){
    pcpp::IFileReaderDevice *reader = pcpp::IFileReaderDevice::getReader("input.pcap"); // создание интерфейса
    // create the stats object

    if(reader == NULL)
    {
        std::cout << "Cannot determine reader for file type" << std::endl;
        return 2;
    }
    if(!reader->open()) // открытие файла для чтения
    {
        std::cerr << "Cannot open input.pcap for reading" << std::endl;
        return 1;
    }

//    // create a pcap file writer. Specify file name and link type of all packets that will be written to it,
//    // since pcap file format can contain single link type per file
//    pcpp::PcapFileWriterDevice pcapWriter("output.pcap", pcpp::LINKTYPE_ETHERNET);
//
//    if (!pcapWriter.open()) // open the file for writing
//    {
//        std::cerr << "Cannot open output.pcap for writing" << std::endl;
//        return 1;
//    }

    // create a pcap-ng file writer. Specify file name. Link type is not necessary because
    // because pcap-ng files can store multiple link types in the same file
    pcpp::PcapNgFileWriterDevice pcapNgWriter("output.pcapng");

    if (!pcapNgWriter.open()) // open the file for writing
    {
        std::cerr << "Cannot open output.pcapng for writing" << std::endl;
        return 1;
    }

    // set a BPF filter for the reader - only packets that match the filter will be read
    if (!reader->setFilter("net 98.138.19.88"))
    {
        std::cerr << "Cannot set filter for file reader" << std::endl;
        return 1;
    }

    //==================================================================================================================

    // the packet container
    pcpp::RawPacket rawPacket;

    // a while loop that will continue as long as there are packets in the input file
    // matching the BPF filter
    while (reader->getNextPacket(rawPacket))
    {
        // write each packet to both writers
//        pcapWriter.writePacket(rawPacket);
        pcapNgWriter.writePacket(rawPacket);
    }
    //==================================================================================================================
    pcpp::IPcapDevice::PcapStats stats;

    // read stats from reader and print them
    reader->getStatistics(stats);
    std::cout << "Read " << stats.packetsRecv << " packets successfully and "
                         << stats.packetsDrop << " packets could not be read" << std::endl;

//    // read stats from pcap writer and print them
//    pcapWriter.getStatistics(stats);
//    std::cout << "Written " << stats.packetsRecv << " packets successfully to pcap writer and "
//                            << stats.packetsDrop << " packets could not be written" << std::endl;

    // read stats from pcap-ng writer and print them
    pcapNgWriter.getStatistics(stats);
    std::cout << "Written " << stats.packetsRecv << " packets successfully to pcap-ng writer and "
                            << stats.packetsDrop << " packets could not be written" << std::endl;

//==================================/ Initializing a device for packet capturing \======================================

// IPv4 address of the interface we want to sniff
    std::string interfaceIPAddr = "10.0.0.1";

    // find the interface by IP address
    pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(interfaceIPAddr);
    if (dev == NULL)
    {
        std::cerr << "Cannot find interface with IPv4 address of '" << interfaceIPAddr << "'" << std::endl;
        return 1;
    }

    // before capturing packets let's print some info about this interface
    std::cout
            << "Interface info:" << std::endl
            << "   Interface name:        " << dev->getName() << std::endl // get interface name
            << "   Interface description: " << dev->getDesc() << std::endl // get interface description
            << "   MAC address:           " << dev->getMacAddress() << std::endl // get interface MAC address
            << "   Default gateway:       " << dev->getDefaultGateway() << std::endl // get default gateway
            << "   Interface MTU:         " << dev->getMtu() << std::endl; // get interface MTU

    if (dev->getDnsServers().size() > 0)
        std::cout << "   DNS server:            " << dev->getDnsServers().at(0) << std::endl;

    // open the device before start capturing/sending packets
    if (!dev->open())
    {
        std::cerr << "Cannot open device" << std::endl;
        return 1;
    }

//========================================/ Setting up packet filters \=================================================

    // create a filter instance to capture only traffic on port 80
    pcpp::PortFilter portFilter(80, pcpp::SRC_OR_DST); // pcpp::SRC_OR_DST - instruction to search on both
    // source and destnation port of each packet

    // create a filter instance to capture only TCP traffic
    pcpp::ProtoFilter protocolFilter(pcpp::TCP);

    // create an AND filter to combine both filters - capture only TCP traffic on port 80
    pcpp::AndFilter andFilter;
    andFilter.addFilter(&portFilter);
    andFilter.addFilter(&protocolFilter);

    // set the filter on the device
    dev->setFilter(andFilter);

//===========================/ Asynchronous packet capture using a callback function \==================================

    std::cout << std::endl << "Starting async capture..." << std::endl;

    PacketStats packetStats;
    // start capture in async mode. Give a callback function to call to whenever a packet is captured and the stats object as the cookie
    dev->startCapture(onPacketArrives, &packetStats); //можно без проверок - лог будет выведен
    /**
    the packet capture is happening in a different thread
    so code written from now on in our main thread will work in parallel.
    */
    // sleep for 10 seconds in main thread, in the meantime packets are captured in the async thread
    pcpp::multiPlatformSleep(10); // метод вызывающий метод sleep корректный для действующей ОС
                                          // здесь нужен просто для отсчета времени необходимого для перехвата
                                          // какого-то объема пакетов
    // stop capturing packets
    dev->stopCapture();

    std::cout << "Results:" << std::endl;
    packetStats.printToConsole();

//=========================/ Asynchronous packet capture using a packet list (vector) \=================================

    std::cout << std::endl << "Starting capture with packet vector..." << std::endl;

    // create an empty packet vector object
    pcpp::RawPacketVector packetVec;

    // start capturing packets. All packets will be added to the packet vector
    dev->startCapture(packetVec); //функция перегружена и может принимать векторы, коллбэки,
    // sleep for 10 seconds in main thread, in the meantime packets are captured in the async thread
    pcpp::multiPlatformSleep(10);
    dev->stopCapture();

    // go over the packet vector and feed all packets to the stats object
    for (pcpp::RawPacketVector::ConstVectorIterator iter = packetVec.begin(); iter != packetVec.end(); iter++)
    {
        // parse raw packet
        pcpp::Packet parsedPacket(*iter);

        // feed packet to the stats object
        packetStats.consumePacket(parsedPacket);
    }
    // print results
    std::cout << "Results:" << std::endl;
    packetStats.printToConsole();

//=========================/ Synchronous (blocking) packet capture using a callback function \==========================

    std::cout << std::endl << "Starting capture in blocking mode..." << std::endl;

// clear stats
    packetStats.clear();

// start capturing in blocking mode. Give a callback function to call to whenever a packet is captured, the stats object
// as the cookie and a 10 seconds timeout
    dev->startCaptureBlockingMode(onPacketArrivesBlockingMode, &stats, 10);

// thread is blocked until capture is finished

// capture is finished, print results
    std::cout << "Results:" << std::endl;
    packetStats.printToConsole();

//==============================================/ ЗАКРЫТИЕ СЕССИИ \=====================================================

    reader->close();// close reader

    // close writers
//    pcapWriter.close();
    pcapNgWriter.close();


    delete reader; // free reader memory because it was created by pcpp::IFileReaderDevice::getReader()
}

