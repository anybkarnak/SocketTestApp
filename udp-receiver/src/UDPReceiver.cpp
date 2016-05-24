//
// Created by karnak on 22.05.16.
//

#include <iostream>
#include "UDPReceiver.h"

static const int BUFLEN = 32;  //Max length of buffer


UDPReceiver::UDPReceiver(const MessageContainerPtr& container, int localPort):
        m_container(container),
        m_running(true),
        m_socketPtr(std::make_shared<UDPSocket>(localPort))
{
}

UDPReceiver::UDPReceiver(UDPSocketPtr& socket, const MessageContainerPtr& container):
        m_socketPtr(socket),
        m_container(container),
        m_running(true)
{
}

void UDPReceiver::StartReceiveData()
{
    char buf[BUFLEN];
    int recv_len;

    while (m_running)
    {
        recv_len = m_socketPtr->Recv(buf, BUFLEN);
        //19 digits and '\0'
        if (recv_len == 20)
        {
            Message a((uint8_t*)buf);

            if (m_container != nullptr)
            {
                m_container->Add(a);
            }
        }
    }

}


void UDPReceiver::StopReceiveData()
{
    m_running = false;
}

void UDPReceiver::PrintContainer()
{
    m_container->Print();

}