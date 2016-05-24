//
// Created by akomandyr on 23.05.16.
//

#include "UDPSender.h"
#include <random>
#include <limits.h>

static const int BUFFLEN = 20; //19 digits and '0'

UDPSender::UDPSender(const std::string& localAddress, int localPort):
        m_UDPSocketContainer(std::make_shared<MessageContainer>()),
        m_TCPSocketContainer(std::make_shared<MessageContainer>()),
        m_running(true),
        m_UDPSocket(std::make_shared<UDPSocket>(localAddress, localPort)),
        m_TCPSocket(std::make_shared<TCPSocket>(localAddress, localPort)),
        m_bufferLenght(BUFFLEN)
{
}
UDPSender::UDPSender(const UDPSocketPtr& m_UDPSocket,const MessageContainerPtr& container):
        m_UDPSocketContainer(container),
        m_TCPSocketContainer(std::make_shared<MessageContainer>()),
        m_running(true),
        m_UDPSocket(m_UDPSocket),
        m_TCPSocket(nullptr),
        m_bufferLenght(BUFFLEN){ }

uint8_t* UDPSender::ComposeMessage(uint16_t MessageSize,
                                   uint8_t MessageType,
                                   uint64_t MessageId,
                                   uint64_t MessageData)
{
    uint8_t* byteArray = new uint8_t[BUFFLEN];
    byteArray[0] = ((MessageSize >> 8) & 0xFF);
    byteArray[1] = ((MessageSize & 0XFF));
    byteArray[2] = MessageType;
    byteArray[3] = ((MessageId >> 56) & 0xFF);
    byteArray[4] = ((MessageId >> 48) & 0xFF);
    byteArray[5] =  ((MessageId >> 40) & 0XFF);
    byteArray[6] = ((MessageId >> 32) & 0XFF);
    byteArray[7] = ((MessageId >> 24) & 0xFF);
    byteArray[8] = ((MessageId >> 16) & 0xFF);
    byteArray[9] = ((MessageId >> 8) & 0XFF);
    byteArray[10] =  ((MessageId & 0XFF));

    byteArray[11] = ((MessageData >> 56) & 0xFF);
    byteArray[12] = ((MessageData >> 48) & 0xFF);
    byteArray[13] = ((MessageData >> 40) & 0XFF);
    byteArray[14] = ((MessageData >> 32) & 0XFF);
    byteArray[15] = ((MessageData >> 24) & 0xFF);
    byteArray[16] = ((MessageData >> 16) & 0xFF);
    byteArray[17] = ((MessageData >> 8) & 0XFF);
    byteArray[18] = ((MessageData & 0XFF));
    byteArray[19] = '\0';

//    std::cout<<"init arr"<<std::endl;
//    for(int i = 0;i<20;i++)
//    {
//        std::cout<<(int)byteArray[i]<<std::endl;
//    }


    return byteArray;
}


void UDPSender::StartSendData()
{
    std::mt19937 mt_rand(time(0));

    while (m_running)
    {
        //simulate delay
        for(volatile int i=0; i<1000;i++)
        {
            pow(i,i);
        }

        uint16_t MessageSize = mt_rand() % USHRT_MAX;
        uint8_t MessageType = mt_rand() % UCHAR_MAX;
        uint64_t MessageId = mt_rand() % LLONG_MAX;
        uint64_t MessageData = mt_rand() % LLONG_MAX;


        uint8_t* buffer = ComposeMessage(MessageSize, MessageType, MessageId, MessageData);

        Message a(MessageSize, MessageType, MessageId, MessageData);
        m_UDPSocketContainer->Add(a);

        m_UDPSocket->Send(buffer, m_bufferLenght);
    }
}

void UDPSender::StopSendData()
{
    m_running = false;
}

void UDPSender::PrintContainer()
{
    m_UDPSocketContainer->Print();
}

UDPSender::~UDPSender()
{}