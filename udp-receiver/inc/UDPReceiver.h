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

    UDPReceiver(MessageContainerPtr& container, int localPort);
    UDPReceiver(UDPSocketPtr& socket);

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

#endif //UDPRECEIVER_H
