#include "CSpeakingAgent.h"
#include <stdio.h>

SpeakingAgent::CSpeakingAgent gs;

namespace SpeakingAgent
{
CSpeakingAgent::CSpeakingAgent()
: Runtime::CRuntimeUnit("speakingAgent")
{
    m_ttsEngineWrapper.Initialize();
}

CSpeakingAgent::~CSpeakingAgent()
{
}

void CSpeakingAgent::MQTTClientConnected()
{
  CRuntimeUnit::MQTTClientConnected();

  GetMessenger().Subscribe("ttsOrders", this);
}

void CSpeakingAgent::HandleMessage( const std::string& topic, const std::string& payload)
{
	printf("received %s, %s\n", topic.c_str(), payload.c_str());

  if ( "ttsOrders" == topic )
  {
    m_ttsEngineWrapper.Say(payload);
  }
}

}
