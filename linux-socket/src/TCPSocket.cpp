//
// Created by akomandyr on 23.05.16.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket(const std::string& localAddress, int localPort)
{
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    m_addr.sin_family = AF_INET;         /* host byte order */
    m_addr.sin_port = htons(localPort);     /* short, network byte order */

    if (inet_aton(localAddress.c_str(), &m_addr.sin_addr) == 0)
    {

    }


    bzero(&(m_addr.sin_zero), 8);        /* zero the rest of the struct */

    if (bind(m_socket, (struct sockaddr*) &m_addr, sizeof(struct sockaddr)) \
 == -1)
    {
        perror("bind");
        exit(1);
    }

    //listen one connection
    if (listen(m_socket, 1) == -1)
    {
        perror("listen");
        exit(1);
    }

    if ((m_client = accept(m_socket, (struct sockaddr*) &their_addr, (socklen_t*)&sin_size)) == -1)
    {
        perror("accept");
    }
}


/*
 *   Read into the given buffer up to bufferLen bytes data from this
 *   socket.  Call connect() before calling recv() if use TCP socket
 *   @param buffer buffer to receive the data
 *   @param bufferLen maximum number of bytes to read into buffer
 *   @return number of bytes read, 0 for EOF, and -1 for error
 */
int TCPSocket::Recv(char* buffer, int bufferLen)
{
    sin_size = sizeof(struct sockaddr_in);
    if ((m_client = accept(m_socket, (struct sockaddr*) &their_addr, (socklen_t*) &sin_size)) == -1)
    {
        perror("accept");
    }
    printf("server: got connection from %s\n",
           inet_ntoa(their_addr.sin_addr));
    //set client to nonblock
    fcntl(m_client, F_SETFL, O_NONBLOCK);
    int len = 0;
    len = recv(m_client, buffer, sizeof(buffer), 0);
    if (len < 1)
    {
        perror("recv - non blocking \n");
        printf("and the data read size is: n=%d \n", len);


        return len;

    }
}
/**
 *   Write the given buffer to this socket.
 *   @param buffer buffer to be written
 *   @param bufferLen number of bytes from buffer to be written
 */
    void TCPSocket::Send(const uint8_t* buffer, int bufferLen)
    {

    }