#pragma once

#include <CRuntimeUnit.h>
#include <ITimerListener.h>

namespace SpeakingAgent
{

class CSpeakingAgent: Runtime::CRuntimeUnit
              , Runtime::ITimerListener
              , Runtime::IMsgSubscriber
{
public:
  CSpeakingAgent();
  virtual ~CSpeakingAgent();

private:
  void NotifyTimer( const Int32& timerId ) override;

private:
  void HandleMessage( const std::string& topic, const std::string& payload);

private:
 CSpeakingAgent( const CSpeakingAgent&);
 CSpeakingAgent& operator=(const CSpeakingAgent&);
};

}
