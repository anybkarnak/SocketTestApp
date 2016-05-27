//
// Created by karnak on 22.05.16.
//

#include <iostream>
#include "MessageContainer.h"
#include <algorithm>



void MessageContainer::Add(Message& msg)
{
    std::lock_guard<std::mutex> lock(m_mutex); //lock the mutex
    //std::cout<<"\n trying add element"<<std::endl;

    //std::cout << msg.MessageSize << " " << (int) msg.MessageType << " " << msg.MessageId << " " << msg.MessageData;



}

Message MessageContainer::Find(uint64_t msg_ID)
{
    return 0;
}

void MessageContainer::Print()
{

}

bool MessageContainer::Compare(const MessageContainerPtr& container)
{
    int matches=0;
    int size1=0;
    int size2=0;


    std::cout<<std::endl<<matches<<" matches, percentage = "<<(double)((double)matches/(double)size1)<<std::endl;
    return ((size1==size2)&&matches/size1)==1;

}


MessageContainer::~MessageContainer()
{

}