#pragma once

#include <CRuntimeUnit.h>

namespace Example
{

class CExample: Runtime::CRuntimeUnit
{
public:
  CExample();
  virtual ~CExample();

private:
 CExample( const CExample&);
 CExample& operator=(const CExample&);
};

}
