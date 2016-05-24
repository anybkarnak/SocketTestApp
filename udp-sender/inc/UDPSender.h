//
// Created by akomandyr on 23.05.16.
//

#ifndef UDPSENDER_H
#define UDPSENDER_H

#include "TCPSocket.h"
#include "MessageContainer.h"
#include "UDPSocket.h"

class UDPSender
{
public:
    UDPSender(const std::string& localAddress, int localPort);

    UDPSender(const UDPSocketPtr& m_UDPSocket);

    void StartSendData();

    void StopSendData();

    void PrintContainer();

    uint8_t* ComposeMessage(uint16_t MessageSize,
                        uint8_t MessageType,
                        uint64_t MessageId,
                        uint64_t MessageData);

    ~UDPSender();

private:
    /*
     *  State of Sender
     */
    bool m_running;

    /*
     *  Socket descriptor
     */
    UDPSocketPtr m_UDPSocket;

    /*
     *  Socket descriptor
     */
    TCPSocketPtr m_TCPSocket;

    /*
     *  container of messages for UDP socket(for checking)
     */
    MessageContainerPtr m_UDPSocketContainer;

    /*
     *  container of messages for TCP socket(for checking)
     */
    MessageContainerPtr m_TCPSocketContainer;

    int m_bufferLenght;
};

typedef std::shared_ptr<UDPSender> UDPSenderPtr;

#endif //UDPSENDER_H
