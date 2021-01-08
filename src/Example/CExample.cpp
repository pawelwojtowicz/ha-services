#include "CExample.h"
#include <stdio.h>

Example::CExample gs;

namespace Example
{
CExample::CExample()
: Runtime::CRuntimeUnit("Example")
{
    int timerId = GetTimerManager().CreateTimer(this);
    GetTimerManager().SetTimer(timerId,0,5);
    GetTimerManager().StartTimer(timerId);
}

CExample::~CExample()
{
}

void CExample::NotifyTimer( const Int32& timerId )
{
    printf("Timer\n");

    GetMessenger().Publish("hi", "hello world", 1, false);

    GetMessenger().Subscribe("temp", this);
}

void CExample::HandleMessage( const std::string& topic, const std::string& payload)
{
	printf("received %s, %s\n", topic.c_str(), payload.c_str());
}


}
