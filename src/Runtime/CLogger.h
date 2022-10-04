#pragma once
#include "ILogger.h"
#include "CLoggerMsg.h"

namespace Runtime
{
class CLogger: public ILogger
{
public:
  CLogger( const std::string& runtimeUnitName);
  virtual ~CLogger();

  bool Initialize();
  void Shutdown();

  virtual void RecordDebugMessage( const CLoggerMsg& rLoggerMsg) override;

private:
  std::string m_runtimeUnitName;
};
}