//
// Created by akomandyr on 23.05.16.
//

#ifndef TCPLINUXSOCKET_H
#define TCPLINUXSOCKET_H

#include "SocketCommon.h"
class TCPSocket
{
public:
    TCPSocket(const std::string &localAddress, int localPort);
};
typedef std::shared_ptr<TCPSocket> TCPSocketPtr;
#endif //UDPRESEIVER_TCPLINUXSOCKET_H
