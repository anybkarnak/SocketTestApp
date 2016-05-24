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
#include <cmath>

using namespace std;

static const int PORT = 8888;   //The port on which to listen for incoming data

int main(void)
{

   // char arr[] = {45, 8, 66, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
   // Message a(arr);
  //  std::cout << a.MessageSize << " " << (int) a.MessageType << " " << a.MessageId << " " << a.MessageData;

    MessageContainerPtr receiveContainer = std::make_shared<MessageContainer>();
    UDPSocketPtr socket1 = std::make_shared<UDPSocket>("127.0.0.1", PORT);
    UDPSocketPtr socket2 = std::make_shared<UDPSocket>("127.0.0.1", PORT+1);

    UDPReceiverPtr receiver1 = std::make_shared<UDPReceiver>(socket1, receiveContainer);
    UDPReceiverPtr receiver2 = std::make_shared<UDPReceiver>(socket2, receiveContainer);

    MessageContainerPtr sendContainer = std::make_shared<MessageContainer>();
    UDPSenderPtr sender1 = std::make_shared<UDPSender>(socket1, sendContainer);
    UDPSenderPtr sender2 = std::make_shared<UDPSender>(socket2, sendContainer);
    bool run = true;


//    Message a(1028, 241, 30, 40);
//    uint8_t* arr = (sender1->ComposeMessage(1028, 241, 30, 40));
//    std::cout<<"main";
//    for(int i = 0;i<20;i++)
//    {
//        std::cout<<(int)*(arr+i)<<std::endl;
//    }
//    Message b(arr);
//    if(a==b)
//    {
//        std::cout<<"compare true";
//    }
//    else
//    {
//        //std::cout<<"long size"<<sizeof(uint64_t);
//        std::cout << b.MessageSize << " " << (int) b.MessageType << " " << b.MessageId << " " <<b.MessageData<<std::endl;
//        std::cout << a.MessageSize << " " << (int) a.MessageType << " " << a.MessageId << " " <<a.MessageData<<std::endl;
//    }

    while (run)
    {
        std::cout << " enter choise" << std::endl;
        std::cout << "1 - run demo" << std::endl;
        std::cout << "2 - print" << std::endl;
        std::cout << "3 - stop demo, get results" << std::endl;

        int choise;
        cin >> choise;

        switch (choise)
        {
            case 1:
            {
                std::thread t(&UDPReceiver::StartReceiveData, receiver1);
                t.detach();
                std::thread t2(&UDPReceiver::StartReceiveData, receiver2);
                t2.detach();

                std::thread t3(&UDPSender::StartSendData, sender1);
                t3.detach();

                std::thread t4(&UDPSender::StartSendData, sender2);
                t4.detach();

                break;
            }
            case 2:
            {
                //receiver1->PrintContainer();
                break;
            }
            case 3:
            {
                sender1->StopSendData();
                sender2->StopSendData();

                //receiver1->PrintContainer();
                //sendContainer->GetMap()
                //sender1->PrintContainer();
                for(volatile int i=0; i<10000000;i++)
                {
                    pow(i,i);
                }
                receiver1->StopReceiveData();
                receiver2->StopReceiveData();
                bool equal = receiveContainer->Compare(sendContainer);
                if(equal)
                {
                    std::cout<<"\nequal"<<std::endl;
                }
                else
                {
                    //receiver1->PrintContainer();

                    //sender1->PrintContainer();

                    std::cout<<"\nnon equal"<<std::endl;
                }
                run = false;
                break;
            }
        }



    }

    //close(s);
    return 0;
}