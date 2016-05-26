//
// Created by akomandyr on 25.05.16.
//

#include "TCPReceiver.h"

static const int BUFLEN = 32;  //Max length of buffer

TCPReceiver::TCPReceiver(TCPSocketPtr socket) : m_socketPtr(socket), m_running(true), m_container(std::make_shared<MessageContainer>())
{
}
void
TCPReceiver::StartReceiveData()
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


void TCPReceiver::StopReceiveData()
{
    m_running = false;
    PrintContainer();
}

void TCPReceiver::PrintContainer()
{
    m_container->Print();
}