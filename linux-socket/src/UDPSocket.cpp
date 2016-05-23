//
// Created by akomandyr on 23.05.16.
//

#include "UDPSocket.h"

UDPSocket::UDPSocket(const int localPort)
{

    slen = sizeof(si_other);
    //create a UDP socket
    if ((m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    fcntl(m_socket, F_SETFL, O_NONBLOCK);

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(localPort);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if (bind(m_socket, (struct sockaddr *) &si_me, sizeof(si_me)) == -1)
    {
        die("bind");
    }
}

int UDPSocket::Recv(void* buffer, int bufferLen) {

    int result;
    fd_set readset;
    struct timeval tv;

    fflush(stdout);
    do
    {
        FD_ZERO(&readset);
        FD_SET(m_socket, &readset);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        result = select(m_socket + 1, &readset, NULL, NULL, &tv);
    } while (result == -1 && errno == EINTR);

    if (result == 1)
    {
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(m_socket, buffer, bufferLen, 0, (struct sockaddr *) &si_other, (socklen_t *) &slen)) ==
            -1)
        {
            die("recvfrom()");
        }

    }
}

UDPSocket::~UDPSocket()
{

}
