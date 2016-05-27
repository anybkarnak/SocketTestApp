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
    m_container.push_back(msg);


}

Message MessageContainer::Find(uint64_t msg_ID)
{
    for(auto &it:m_container)
    {
        if(it.MessageId == msg_ID)
        {
            return it;
        }
    }
    return nullptr;
}

void MessageContainer::Print()
{
    for(auto &it:m_container)
    {
        std::cout << it.MessageSize << " " << (int) it.MessageType << " " << it.MessageId << " " << it.MessageData;
    }
}

bool MessageContainer::Compare(const MessageContainerPtr& container)
{
    int matches=0;


    Vector<Message> v2 = container->GetVector();
    int size1=m_container.size();
    int size2=v2.size();

    for(auto &it:m_container)
    {
        for(auto &jt:v2)
        {
                if(it==jt)
                {
                    matches++;
                    break;
                }
        }

    }

    std::cout<<std::endl<<"size1="<<size1<<"size2="<<size2<<"   "<<matches<<" matches, percentage = "<<(double)((double)matches/(double)size1)<<std::endl;
    return ((size1==size2)&&matches/size1)==1;

}


MessageContainer::~MessageContainer()
{

}