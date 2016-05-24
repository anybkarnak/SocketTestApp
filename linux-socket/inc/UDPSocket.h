//
// Created by akomandyr on 23.05.16.
//

#ifndef UDPLINUXSOCKET_H
#define UDPLINUXSOCKET_H


#include <mutex>
#include "SocketCommon.h"


class UDPSocket
{
public:

    UDPSocket(const std::string &localAddress, int localPort);
    //for receiving socket
    UDPSocket(const int localPort);


    /**
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

    ~UDPSocket();


private:

    /**
     *   Internal Socket descriptor
     **/
    int m_socket;
    bool nonBlocking;


    struct sockaddr_in si_me;
    struct sockaddr_in si_other;

    int recv_len;
    int slen;
    std::mutex mutex;
};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;
#endif //UDPRESEIVER_LINUXSOCKET_H
