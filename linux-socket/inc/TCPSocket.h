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

    /*
     *   Read into the given buffer up to bufferLen bytes data from this
     *   socket.  Call connect() before calling recv() if use TCP socket
     *   @param buffer buffer to receive the data
     *   @param bufferLen maximum number of bytes to read into buffer
     *   @return number of bytes read, 0 for EOF, and -1 for error
     */
    int Recv(char *buffer, int bufferLen);

    /**
     *   Write the given buffer to this socket.
     *   @param buffer buffer to be written
     *   @param bufferLen number of bytes from buffer to be written
     */
    void Send(const uint8_t* buffer, int bufferLen);

private:
    /*
     * Socket descriptor
     */
    int m_socket;

    /*
     * friend socket descriptor
     */
    int m_friend;

    /*
     * my address information
     */
    struct 	sockaddr_in 	m_addr;

    /*
     *  connector's address information
     */
    struct 	sockaddr_in 	their_addr;

    int sin_size;

};
typedef std::shared_ptr<TCPSocket> TCPSocketPtr;
#endif //UDPRESEIVER_TCPLINUXSOCKET_H
