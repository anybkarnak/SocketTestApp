//
// Created by karnak on 22.05.16.
//

#include <iostream>
#include "MessageContainer.h"

void MessageContainer::Add(Message& msg)
{
    std::lock_guard<std::mutex> lock(m_mutex); //lock the mutex
    //std::cout<<"\n trying add element"<<std::endl;

    //std::cout << msg.MessageSize << " " << (int) msg.MessageType << " " << msg.MessageId << " " << msg.MessageData;
    m_container.insert( std::pair<uint64_t, Message>(msg.MessageId, msg) );
}

Message MessageContainer::Find(uint64_t msg_ID)
{
    return m_container[msg_ID];
}

void MessageContainer::Print()
{
    for(auto& msg:m_container)
    {
        std::cout<<msg.first<<" "<<msg.second.MessageData<<std::endl;
    }
}