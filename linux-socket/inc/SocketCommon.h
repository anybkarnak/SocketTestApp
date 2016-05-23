//
// Created by akomandyr on 23.05.16.
//

#ifndef SOCKETCOMMON_H
#define SOCKETCOMMON_H

#include <cstring>            // For string
#include <exception>         // For exception class
#include <string>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
#include <errno.h>
#include <climits>
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <fcntl.h>          //for file operations

void die(char *s)
{
    perror(s);
    exit(1);
}

/**
 * Enum to represent type of socket(UDP or TCP)
 */
enum SocketType
{
    TcpSocket = SOCK_STREAM,
    UdpSocket = SOCK_DGRAM,
    UnknownSocketType = -1
};

/**
 * Enum to represent type network layer protocol used for socket
 */
enum NetworkLayerProtocol
{
    IPv4Protocol = AF_INET,
    IPv6Protocol = AF_INET6,
    UnknownNetworkLayerProtocol = -1
};

/**
 * Enum to represent Wait Result when reading data from a socket
 */
enum ReadResult
{
    DATA_ARRIVED = 0,
    DATA_TIMED_OUT = ETIMEDOUT,
    DATA_EXCEPTION = 255
};

#endif //SOCKETCOMMON_H
