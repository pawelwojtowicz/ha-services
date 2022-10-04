#pragma once

namespace Runtime
{
class CLoggerMsg;

class ILogger
{
public:
  ILogger() = default;
  virtual ~ILogger() = default;

  virtual void RecordDebugMessage( const CLoggerMsg& rLoggerMsg) = 0;
};
}