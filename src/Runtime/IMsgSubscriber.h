#pragma once
#include <GlobalTypes.h>

namespace Runtime
{

class IMsgSubscriber
{
public:
    IMsgSubscriber() {};
    virtual ~IMsgSubscriber() {};

    virtual void HandleMessage( const std::string& topic, const std::string& payload) = 0;
};
}