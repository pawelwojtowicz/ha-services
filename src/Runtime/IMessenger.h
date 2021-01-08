#pragma once
#include <GlobalTypes.h>
#include "IMsgSubscriber.h"

namespace Runtime
{

using MQTT_QOS = enum { MQTT_QOS_0 = 0, MQTT_QOS_1 = 1,MQTT_QOS_2 = 2, MQTT_QOS_3 = 3};

class IMessenger
{
public:
    IMessenger() {};
    virtual ~IMessenger() {};

    virtual bool Subscribe( const std::string& topic, IMsgSubscriber* subscriber ) = 0;

    virtual bool Publish( const std::string& topic , const std::string& payload, const int qos, bool retain ) = 0;

private:


};
}