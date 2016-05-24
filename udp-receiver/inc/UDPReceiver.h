//
// Created by karnak on 22.05.16.
//

#ifndef UDPRECEIVER_H
#define UDPRECEIVER_H

#include "MessageContainer.h"

#include "UDPSocket.h"

class UDPReceiver
{
public:

    UDPReceiver(const MessageContainerPtr& container, int localPort);

    UDPReceiver(UDPSocketPtr& socket, const MessageContainerPtr& container);

    void StartReceiveData();
    void StopReceiveData();
    void PrintContainer();

private:

    /*
     *  State of Receiver
     */
    bool m_running;

    /*
     *  Socket descriptor
     */
    UDPSocketPtr m_socketPtr;

    /*
     *  container of messages
     */
    MessageContainerPtr m_container;

};

typedef std::shared_ptr<UDPReceiver> UDPReceiverPtr;
#endif //UDPRECEIVER_H
