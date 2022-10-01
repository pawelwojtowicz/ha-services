#include "CSpeakingAgent.h"
#include <stdio.h>

SpeakingAgent::CSpeakingAgent gs;

namespace SpeakingAgent
{
CSpeakingAgent::CSpeakingAgent()
: Runtime::CRuntimeUnit("speakingAgent")
{
    int timerId = GetTimerManager().CreateTimer(this);
    GetTimerManager().SetTimer(timerId,0,5);
    GetTimerManager().StartTimer(timerId);
}

CSpeakingAgent::~CSpeakingAgent()
{
}

void CSpeakingAgent::NotifyTimer( const Int32& timerId )
{
    printf("Timer\n");

    GetMessenger().Publish("hi", "hello world", 1, false);

    GetMessenger().Subscribe("temp", this);
}

void CSpeakingAgent::HandleMessage( const std::string& topic, const std::string& payload)
{
	printf("received %s, %s\n", topic.c_str(), payload.c_str());
}


}
