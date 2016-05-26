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
    Message(uint8_t* buf)
    {
//        std::cout<<"arr"<<std::endl;
//        for(int i = 0;i<20;i++)
//        {
//            std::cout<<(int)buf[i]<<std::endl;
//        }
        //use bigEndian shiftness
            MessageSize =((buf[0]<<8)|buf[1]);
            MessageType = buf[2];
            MessageId = ((buf[3] << 56)|(buf[4] << 48) | (buf[5] << 40) | (buf[6] << 32) | (buf[7] << 24) | (buf[8] << 16) | (buf[9] << 8) | (buf[10]));
            MessageData = ((buf[11] << 56)|(buf[12] << 48) | (buf[13] << 40) | (buf[14] << 32) | (buf[15] << 24) | (buf[16] << 16) | (buf[17] << 8) | (buf[18]));
    }

    Message():
            MessageSize(0),
            MessageType(0),
            MessageId(0),
            MessageData(0)
            {

            }
    Message(uint16_t messageSize,
    uint8_t messageType,
    uint64_t messageId,
    uint64_t messageData):
            MessageSize(messageSize),
            MessageType(messageType),
            MessageId(messageId),
            MessageData(messageData)
    {
    }
    bool operator==(const Message msg) const
    {
        return (MessageSize==msg.MessageSize&&MessageType==msg.MessageType&&MessageId==msg.MessageId&&MessageData==msg.MessageData);
    }

    uint16_t MessageSize;
    uint8_t MessageType;
    uint64_t MessageId;
    uint64_t MessageData;
};

class MessageContainer;
typedef std::shared_ptr<MessageContainer> MessageContainerPtr;

class MessageContainer
{
public:

    void Add(Message& msg);

    Message Find(uint64_t msg_ID);

    bool Compare(const MessageContainerPtr& container);

    std::map<uint64_t, Message> GetMap(){return m_container;};

    void Print();
private:

    std::map<uint64_t, Message> m_container;
    std::mutex m_mutex;
    Message m_data;
};

typedef std::shared_ptr<MessageContainer> MessageContainerPtr;

#endif //MESSAGECONTAINER_H
