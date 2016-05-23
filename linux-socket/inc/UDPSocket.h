//
// Created by akomandyr on 23.05.16.
//

#ifndef UDPLINUXSOCKET_H
#define UDPLINUXSOCKET_H


#include "SocketCommon.h"
#include <memory>

class UDPSocket
{
public:

    UDPSocket(const std::string &localAddress, int localPort);
    //for receiving socket
    UDPSocket(const int localPort);
    /**
        *   Set the local port to the specified port and the local address
        *   will be selected.
        *   @param localAddress local address
        *   @param localPort local port
        */

     void BindLocalAddressAndPort(const std::string &localAddress, unsigned short localPort);

    /**
     *   Read into the given buffer up to bufferLen bytes data from this
     *   socket.  Call connect() before calling recv() if use TCP socket
     *   @param buffer buffer to receive the data
     *   @param bufferLen maximum number of bytes to read into buffer
     *   @return number of bytes read, 0 for EOF, and -1 for error
     */
     int Recv(void *buffer, int bufferLen);

    /**
     *   Sets the socket to Non blocking state.
     */
     int SetNonBlock();

    /**
     *   Establish a socket connection for TCP SOCKET with the given foreign
     *   address and port
     *   @param foreignAddress foreign address (IP address or name)
     *   @param foreignPort foreign port
     */
    void ConnectToHost(const std::string &foreignAddress, unsigned short foreignPort);

    /**
     *   Write the given buffer to this socket.  Call connect() before
     *   calling send()
     *   @param buffer buffer to be written
     *   @param bufferLen number of bytes from buffer to be written
     */
     void Send(const void *buffer, int bufferLen);

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

};

typedef std::shared_ptr<UDPSocket> UDPSocketPtr;
#endif //UDPRESEIVER_LINUXSOCKET_H
