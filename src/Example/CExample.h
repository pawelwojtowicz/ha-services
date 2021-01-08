#pragma once

#include <CRuntimeUnit.h>
#include <ITimerListener.h>

namespace Example
{

class CExample: Runtime::CRuntimeUnit
              , Runtime::ITimerListener
{
public:
  CExample();
  virtual ~CExample();

private:
  virtual void NotifyTimer( const Int32& timerId ) override;

private:
 CExample( const CExample&);
 CExample& operator=(const CExample&);
};

}
