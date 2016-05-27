/*

*/
#include "MessageContainer.h"
#include "UDPReceiver.h"
#include "UDPSender.h"
#include <cmath>
#include "TCPReceiver.h"


#include <iostream>
#include <atomic>
#include <thread>
#include <stdio.h> //printf
#include <cassert>

//#include "message-container/src/Vector.h"

using namespace std;

static const int PORT = 8888;   //The port on which to listen for incoming data

int main(void)
{

    MessageContainerPtr receiveContainer = std::make_shared<MessageContainer>();
    UDPSocketPtr socket1 = std::make_shared<UDPSocket>("127.0.0.1", PORT);
    UDPSocketPtr socket2 = std::make_shared<UDPSocket>("127.0.0.1", PORT+1);
    TCPSocketPtr tcpSockRes = std::make_shared<TCPSocket>("127.0.0.1", PORT+2);


    UDPReceiverPtr receiver1 = std::make_shared<UDPReceiver>(socket1, receiveContainer);
    UDPReceiverPtr receiver2 = std::make_shared<UDPReceiver>(socket2, receiveContainer);
    TCPReceiverPtr receiver3 = std::make_shared<TCPReceiver>(tcpSockRes);


    MessageContainerPtr sendContainer = std::make_shared<MessageContainer>();
    UDPSenderPtr sender1 = std::make_shared<UDPSender>(socket1,tcpSockRes, sendContainer);
    UDPSenderPtr sender2 = std::make_shared<UDPSender>(socket2,tcpSockRes, sendContainer);
    bool run = true;


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

                std::thread t21(&TCPReceiver::StartReceiveData, receiver3);
                t21.detach();


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

                for(volatile int i=0; i<10000000;i++)
                {
                    pow(i,i);
                }
                receiver1->StopReceiveData();
                receiver2->StopReceiveData();
                receiver3->StopReceiveData();
                bool equal = receiveContainer->Compare(sendContainer);
                if(equal)
                {
                    std::cout<<"\nequal"<<std::endl;
                }
                else
                {
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