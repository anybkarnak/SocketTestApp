//
// Created by karnak on 22.05.16.
//

#include <iostream>
#include "UDPReceiver.h"

static const int BUFLEN = 32;  //Max length of buffer
static const int PORT = 8888;   //The port on which to listen for incoming data

UDPReceiver::UDPReceiver(MessageContainerPtr &container):
        m_container(container),
        m_running(true),
        m_socketPtr(std::make_shared<UDPSocket>(PORT))
{
}


void UDPReceiver::StartReceiveData()
{
    char buf[BUFLEN];
    int recv_len;
    while (m_running)
    {
        recv_len=m_socketPtr->Recv(buf, BUFLEN);

        if (recv_len == 20)
        {
            Message a(buf);

            if (m_container != nullptr)
            {
                m_container->Add(a);
            }
        }

    }

    //m_container->Print();

}


void UDPReceiver::StopReceiveData()
{
    m_running = false;
}

void UDPReceiver::PrintContainer()
{
    m_container->Print();

}