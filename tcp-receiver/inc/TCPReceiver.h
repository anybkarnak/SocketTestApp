//
// Created by karnak on 24.05.16.
//

#ifndef SOCKETTESTAPP_TCPRECEIVER_H
#define SOCKETTESTAPP_TCPRECEIVER_H

#include <MessageContainer.h>
#include "TCPSocket.h"

class TCPReceiver
{
public:
    TCPReceiver(TCPSocketPtr socket);
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
    TCPSocketPtr m_socketPtr;

    /*
     *  container of messages
     */
    MessageContainerPtr m_container;
};


#endif //SOCKETTESTAPP_TCPRECEIVER_H
