//
// Created by akomandyr on 23.05.16.
//

#include <iostream>
#include "TCPSocket.h"

TCPSocket::TCPSocket(const std::string &localAddress, int localPort) : m_localadress(localAddress),
                                                                       m_localPort(localPort)
{
    //init recv socket
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    m_addr.sin_family = AF_INET;         /* host byte order */
    m_addr.sin_port = htons(localPort);     /* short, network byte order */
    m_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
    bzero(&(m_addr.sin_zero), 8);        /* zero the rest of the struct */

    if (bind(m_socket, (struct sockaddr *) &m_addr, sizeof(struct sockaddr)) == -1)
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

    /* Change the socket into non-blocking state	*/
    fcntl(m_socket, F_SETFL, O_NONBLOCK);

    //init send socket
    if ((m_server = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return;
    }
    server_addr.sin_family = AF_INET;         /* host byte order */
    server_addr.sin_port = htons(m_localPort);     /* short, network byte order */
    bzero(&(server_addr.sin_zero), 8);        /* zero the rest of the struct */

    if (inet_aton(m_localadress.c_str(), &server_addr.sin_addr) == 0)
    {
        perror("socket");
    }


    //set client to nonblock
    fcntl(m_server, F_SETFL, O_NONBLOCK);

    is_connected = false;
    is_accepted = false;
//    if ((m_friend = accept(m_socket, (struct sockaddr*) &their_addr, (socklen_t*)&sin_size)) == -1)
//    {
//        perror("accept");
//    }


}


/*
 *   Read into the given buffer up to bufferLen bytes data from this
 *   socket.  Call connect() before calling recv() if use TCP socket
 *   @param buffer buffer to receive the data
 *   @param bufferLen maximum number of bytes to read into buffer
 *   @return number of bytes read, 0 for EOF, and -1 for error
 */
int TCPSocket::Recv(char *buffer, int bufferLen)
{
    std::lock_guard<std::mutex> lock(m_mutex);


    sin_size = sizeof(struct sockaddr_in);
    if (!is_accepted)
    {
        if ((m_client = accept(m_socket, (struct sockaddr *) &client_addr, (socklen_t *) &sin_size)) == -1)
        {
            perror("accept");

            return 0;
        }
        else
        {
            printf("server: got connection from %s\n", inet_ntoa(client_addr.sin_addr));
            is_accepted = true;
        }
    }


//set client to nonblock
    fcntl(m_client, F_SETFL, O_NONBLOCK);
    int len = 0;
    len = recv(m_client, buffer, bufferLen, 0);

    if (len < 1)
    {
        perror("recv - non blocking \n");
        printf("and the data read size is: l=%d \n", len);
    }

    return
            len;
}

/**
 *   Write the given buffer to this socket.
 *   @param buffer buffer to be written
 *   @param bufferLen number of bytes from buffer to be written
 */
void TCPSocket::Send(const uint8_t *buffer, int bufferLen)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (connect(m_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0 && !is_connected)
    {
        perror("connect error");
        return;
    }
    else
    {
        std::cout << "connected" << std::endl;
        is_connected = true;
    }



    //Send some data

    if (send(m_server, buffer, bufferLen, 0) < 0)
    {
        perror("Send failed");
        return;
    }
}