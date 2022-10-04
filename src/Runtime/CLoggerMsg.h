#pragma once
#include <GlobalTypes.h>
#define MAX_LOG_TEXT_LENGTH 512

namespace Runtime
{
class ILogger;

class CLoggerMsg
{
public:
  CLoggerMsg();
  CLoggerMsg( const UInt8 debugZone, const char* srcFileName, const UInt32 srcLineNo );
  virtual ~CLoggerMsg();

  void LogText( const char* logText, ... );

  static inline bool ZoneEnabled(UInt8 queryZone) { return ( 0 != (	sDebugZoneMask & queryZone ) );};

  static void SetLogger( ILogger* pLogger );

  static void SetDebugZone( const UInt8 dzMask);

  const char* GetDBGZone() const;
  const char* GetLogText() const;
  const char* GetSrcFileName() const;
  const UInt32 GetLineNo() const;
  const UInt32 GetTimeStamp() const;

private:
  UInt8 m_logDbgZone;
  char* m_logText;
  char* m_pSrcFileName;
  UInt32 m_srcLineNo;
  UInt32 m_timeStamp;

private:
  static ILogger* spLogger;
  static UInt8 sDebugZoneMask;
};
}