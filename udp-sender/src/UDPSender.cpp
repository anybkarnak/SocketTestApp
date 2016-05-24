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
    uint8_t byteArray[BUFFLEN];
    byteArray[0] = (int) ((MessageSize >> 8) & 0xFF);
    byteArray[1] = (int) ((MessageSize & 0XFF));
    byteArray[3] = MessageType;
    byteArray[4] = (int) ((MessageId >> 56) & 0xFF);
    byteArray[5] = (int) ((MessageId >> 48) & 0xFF);
    byteArray[6] = (int) ((MessageId >> 40) & 0XFF);
    byteArray[7] = (int) ((MessageId >> 32) & 0XFF);
    byteArray[8] = (int) ((MessageId >> 24) & 0xFF);
    byteArray[9] = (int) ((MessageId >> 16) & 0xFF);
    byteArray[10] = (int) ((MessageId >> 8) & 0XFF);
    byteArray[11] = (int) ((MessageId & 0XFF));

    byteArray[12] = (int) ((MessageData >> 56) & 0xFF);
    byteArray[13] = (int) ((MessageData >> 48) & 0xFF);
    byteArray[14] = (int) ((MessageData >> 40) & 0XFF);
    byteArray[15] = (int) ((MessageData >> 32) & 0XFF);
    byteArray[16] = (int) ((MessageData >> 24) & 0xFF);
    byteArray[17] = (int) ((MessageData >> 16) & 0xFF);
    byteArray[18] = (int) ((MessageData >> 8) & 0XFF);
    byteArray[19] = (int) ((MessageData & 0XFF));
    byteArray[20] = '\0';

    return byteArray;
}


void UDPSender::StartSendData()
{
    std::mt19937 mt_rand(time(0));

    while (m_running)
    {
        uint16_t MessageSize = mt_rand() % USHRT_MAX;
        uint8_t MessageType = mt_rand() % UCHAR_MAX;
        uint64_t MessageId = mt_rand() % LLONG_MAX;
        uint64_t MessageData = mt_rand() % LLONG_MAX;


        uint8_t* buffer = ComposeMessage(MessageSize, MessageType, MessageId, MessageData);

        if (MessageId % 100 == 0)
        {
            std::cout <<"sender " << std::endl << buffer << std::endl;
        }
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