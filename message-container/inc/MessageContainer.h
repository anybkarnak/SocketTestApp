//
// Created by karnak on 22.05.16.
//

#ifndef MESSAGECONTAINER_H
#define MESSAGECONTAINER_H

#include <memory>
#include <stdint.h>

// delete after
#include <map>
#include <mutex>
//delete
#include <iostream>

struct Message
{
    Message(char *buf) :
            MessageSize(*(reinterpret_cast<uint16_t *>(buf))),
            MessageType(static_cast<uint8_t>(buf[2])),
            MessageId(*(reinterpret_cast<uint64_t *>(buf + 3))),
            MessageData(*(reinterpret_cast<uint64_t *>(buf + 11)))
    {
        std::cout<<"message container, buf = "<<buf<<std::endl;
        std::cout << MessageSize << " " << (int) MessageType << " " << MessageId << " " << MessageData;
    }

    Message():
            MessageSize(0),
            MessageType(0),
            MessageId(0),
            MessageData(0)
            {

            }
    uint16_t MessageSize;
    uint8_t MessageType;
    uint64_t MessageId;
    uint64_t MessageData;
};


class MessageContainer
{
public:

    void Add(Message& msg);

    Message Find(uint64_t msg_ID);

    void Print();
private:

    std::map<uint64_t, Message> m_container;
    std::mutex m_mutex;
    Message m_data;
};

typedef std::shared_ptr<MessageContainer> MessageContainerPtr;

#endif //MESSAGECONTAINER_H
