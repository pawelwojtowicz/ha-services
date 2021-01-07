#pragma once
#include <GlobalTypes.h>
#include "IMsgSubscriber.h"

namespace Runtime
{
class IMessenger
{
public:
    IMessenger() {};
    virtual ~IMessenger() {};

    virtual bool Subscribe( const std::string& topic, IMsgSubscriber& subscriber ) = 0;

    virtual bool Subscribe( const std::string& topicPrefix, const std::string& topicWildcard, IMsgSubscriber& subcriber) = 0;
private:


};
}