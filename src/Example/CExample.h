#pragma once

#include <CRuntimeUnit.h>
#include <ITimerListener.h>

namespace Example
{

class CExample: Runtime::CRuntimeUnit
              , Runtime::ITimerListener
              , Runtime::IMsgSubscriber
{
public:
  CExample();
  virtual ~CExample();

private:
  void NotifyTimer( const Int32& timerId ) override;

private:
  void HandleMessage( const std::string& topic, const std::string& payload);

private:
 CExample( const CExample&);
 CExample& operator=(const CExample&);
};

}
