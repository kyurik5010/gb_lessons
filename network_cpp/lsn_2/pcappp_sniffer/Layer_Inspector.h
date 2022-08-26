#pragma once
#include <iostream>
#include "Packet.h"
#include "EthLayer.h"
#include "IPv4Layer.h"
#include "TcpLayer.h"
#include "HttpLayer.h"
#include "SystemUtils.h"


class LayerInspector
{
private:
    pcpp::Layer* _layer;
public:
    explicit LayerInspector(pcpp::Layer* l): _layer(l){};
    pcpp::Layer* GetLayer() const {return _layer;}
    virtual void PrintInfo() = 0;
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
    }
    void PrintLayerSpecs(pcpp::Layer* curLayer)
    {
        std::cout
                << "Layer type: " << getProtocolTypeAsString(curLayer->getProtocol()) << "; " // get layer type
                << "Total data: " << curLayer->getDataLen() << " [bytes]; " // get total length of the layer
                << "Layer data: " << curLayer->getHeaderLen() << " [bytes]; " // get the header length of the layer
                << "Layer payload: " << curLayer->getLayerPayloadSize() << " [bytes]" // get the payload length of the layer (equals total length minus header length)
                << std::endl;
    }
    ~LayerInspector()= default;
};

class EthernetInspector :public LayerInspector
{
private:
    pcpp::EthLayer* ethernetLayer = nullptr;
public:
    EthernetInspector(pcpp::Layer* el): LayerInspector(el)
    {
        if ((ethernetLayer = reinterpret_cast<pcpp::EthLayer *>(GetLayer())) == nullptr)
        {
            std::cerr << "Can't find Ethernet layer" << std::endl;
        }
        else
        {
            PrintLayerSpecs(el);
            PrintInfo();
        }
    };
    void PrintInfo()
    {
        std::cout << std::endl
                  << "Source MAC address: " << ethernetLayer->getSourceMac() << std::endl
                  << "Destination MAC address: " << ethernetLayer->getDestMac() << std::endl
                  << "Ether type = 0x" << std::hex << pcpp::netToHost16(ethernetLayer->getEthHeader()->etherType)
                  << std::endl;
    }
    ~EthernetInspector() = default;
};

class IpInspector :public LayerInspector
{
private:
    pcpp::IPv4Layer* ipLayer = nullptr;
public:
    IpInspector(pcpp::Layer* cl): LayerInspector(cl)
    {
            if ((ipLayer = reinterpret_cast<pcpp::IPv4Layer *>(GetLayer())) == nullptr)
            {
                std::cerr << "Can't find IPv4 layer" << std::endl;
            }
            else
            {
                PrintLayerSpecs(cl);
                PrintInfo();
            }
    };
    void PrintInfo()
    {
        std::cout << std::endl
                  << "Source IP address: " << ipLayer->getSrcIPAddress() << std::endl
                  << "Destination IP address: " << ipLayer->getDstIPAddress() << std::endl
                  << "IP ID: 0x" << std::hex << pcpp::netToHost16(ipLayer->getIPv4Header()->ipId) << std::endl
                  << "TTL: " << std::dec << (int)ipLayer->getIPv4Header()->timeToLive << std::endl;
    }
    ~IpInspector() = default;
};

class TcpInspector :public LayerInspector
{
private:
    pcpp::TcpLayer* tcpLayer = nullptr;
public:
    TcpInspector(pcpp::Layer* cl): LayerInspector(cl)
    {
        if ((tcpLayer = reinterpret_cast<pcpp::TcpLayer *>(GetLayer())) == nullptr)
        {
            std::cerr << "Can't find TCP layer" << std::endl;
        }
        else
        {
            PrintLayerSpecs(cl);
            PrintInfo();
        }
    };
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
    }
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
    }
    void PrintInfo()
    {
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
    }
    ~TcpInspector() = default;
};

class HttpInspector :public LayerInspector
{
private:
    pcpp::HttpRequestLayer* httpRequestLayer = nullptr;
public:
    HttpInspector(pcpp::Layer* cl): LayerInspector(cl){
        if((httpRequestLayer = reinterpret_cast<pcpp::HttpRequestLayer*>(cl)) == nullptr)
            std::cout << "Can't find HTTP layer";
        else
        {
            PrintLayerSpecs(cl);
            PrintInfo();
        }
    };
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
    }
    void PrintInfo()
    {
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
    };
};

class InspectorFactory{
public:
    InspectorFactory(){};
    LayerInspector* CreateEthernetInspector(pcpp::Layer* cl){ return new EthernetInspector(cl); };
    LayerInspector* CreateIPInspector(pcpp::Layer* cl){ return new IpInspector(cl); };
    LayerInspector* CreateTcpInspector(pcpp::Layer* cl){ return new TcpInspector(cl); };
    LayerInspector* CreateHttpInspector(pcpp::Layer* cl){ return new HttpInspector(cl); };
    ~InspectorFactory(){};
};

class LayerHandler
{
private:
    pcpp::Packet pocket;
    InspectorFactory* IFactory;
    std::vector<LayerInspector*> vec;
    static LayerHandler* _handler;
    LayerHandler()
    {
        IFactory = new InspectorFactory;
    };
public:
    static LayerHandler* GetInstance()
    {
        if(!_handler)
            _handler = new LayerHandler;
        return _handler;
    };

    int ConsumePacket(pcpp::Packet& parsedPacket)
    {
        pocket = parsedPacket;
        pcpp::Layer* current_layer;
        /***/
        for (current_layer = pocket.getFirstLayer() ; current_layer != nullptr ; current_layer = current_layer->getNextLayer())
        {
            if(current_layer->getProtocol() == pcpp::Ethernet)
                vec.push_back(IFactory->CreateEthernetInspector(current_layer));
            else if(current_layer->getProtocol() == pcpp::IPv4)
                vec.push_back(IFactory->CreateIPInspector(current_layer));
            else if(current_layer->getProtocol() == pcpp::TCP)
                vec.push_back(IFactory->CreateTcpInspector(current_layer));
            else if(current_layer->getProtocol() == pcpp::HTTPRequest || current_layer->getProtocol() == pcpp::HTTPResponse)
                vec.push_back(IFactory->CreateHttpInspector(current_layer));
            else
                std::cout << "Unknown layer\n";
        }
    }
    ~LayerHandler(){
        for(auto inspector: vec)
            delete inspector;
        delete _handler;
        delete IFactory;
    };
};

LayerHandler* LayerHandler::_handler = nullptr;



