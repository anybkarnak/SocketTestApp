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

bool MessageContainer::Compare(const MessageContainerPtr& container)
{

    std::cout<<std::endl<<container->GetMap().size()<<" "<<this->m_container.size()<<std::endl;

    auto contbeg_ = container->GetMap().begin();
    auto contend_ = container->GetMap().end();

    uint64_t matches=0;

    for(auto& i : this->m_container)
    {
        auto j = std::find_if(contbeg_, contend_,
        [&i] (const std::pair<uint64_t, Message>& pair) { return pair.first==i.first&&i.second==pair.second; }
        );

        if(j==container->GetMap().end())
        {
            return false;
            matches++;
        }
    }
    std::cout<<std::endl<<matches<<" matches, percentage = "<<matches/this->m_container.size()<<std::endl;
    return true;
}