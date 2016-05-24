/*
    Simple udp server
    Silver Moon (m00n.silv3r@gmail.com)
*/
#include <stdio.h> //printf
#include "MessageContainer.h"
#include "UDPReceiver.h"
#include <iostream>
#include <atomic>
#include <thread>
#include <UDPSender.h>
#include <UDPSocket.h>

using namespace std;

static const int PORT = 8888;   //The port on which to listen for incoming data

int main(void)
{

   // char arr[] = {45, 8, 66, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
   // Message a(arr);
  //  std::cout << a.MessageSize << " " << (int) a.MessageType << " " << a.MessageId << " " << a.MessageData;

    MessageContainerPtr container = std::make_shared<MessageContainer>();
    UDPSocketPtr socket = std::make_shared<UDPSocket>("127.0.0.1", PORT);
    UDPReceiver *receiver1 = new UDPReceiver(socket);
    //UDPReceiver *receiver2 = new UDPReceiver(container);
    UDPSender *sender1 = new UDPSender(socket);
    bool run = true;

    while (run)
    {
        std::cout << " enter choise" << std::endl;
        std::cout << "1 - run" << std::endl;
        std::cout << "2 - print" << std::endl;
        std::cout << "3 - stop" << std::endl;

        int choise;
        cin >> choise;

        switch (choise)
        {
            case 1:
            {
                std::thread t(&UDPReceiver::StartReceiveData, receiver1);
                t.detach();
                std::thread t2(&UDPReceiver::StartReceiveData, receiver1);
                t2.detach();

                std::thread t3(&UDPSender::StartSendData, sender1);
                t3.detach();

                break;
            }
            case 2:
            {
                receiver1->PrintContainer();
                break;
            }
            case 3:
            {
                receiver1->PrintContainer();

                sender1->PrintContainer();
                run = false;
                break;
            }
        }



    }

    //close(s);
    return 0;
}