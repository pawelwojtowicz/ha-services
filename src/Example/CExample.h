#pragma once

#include <CExecutable.h>
#include <mosquittopp.h>

namespace Example
{

class CExample: Runtime::CExecutable
{
public:
  CExample();
  virtual ~CExample();

  Int32 Run() override;

private:
 CExample( const CExample&);
 CExample& operator=(const CExample&);
};

}
