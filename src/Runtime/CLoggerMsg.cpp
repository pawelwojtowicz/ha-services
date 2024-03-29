#include "CLoggerMsg.h"
#include "Logger.h"
#include "ILogger.h"
#include <sys/time.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

namespace Runtime
{
static const char* textERROR        = {"ERROR"};
static const char* textWARNING      = {"WARNING"};
static const char* textINFO         = {"INFO"};
static const char* textDATA         = {"DATA"};
static const char* textNotAvailable = {"n//a"}; 

static ILogger* CLoggerMsg::spLogger = nullptr;
static UInt8 CLoggerMsg::sDebugZoneMask = 0xFF;


CLoggerMsg::CLoggerMsg()
: m_logDbgZone(0)
, m_pSrcFileName(nullptr)
, m_srcLineNo(0)
, m_timeStamp(0)
{

}
CLoggerMsg::CLoggerMsg(const UInt8 debugZone, const char* srcFileName, const UInt32 srcLineNo )
: m_logDbgZone(debugZone)
, m_pSrcFileName(srcFileName)
, m_srcLineNo(0)
, m_timeStamp(0)
{
  struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	m_timeStamp = ( currentTime.tv_sec*1000 + currentTime.tv_usec/1000 );
}
CLoggerMsg::~CLoggerMsg()
{

}

void CLoggerMsg::LogText( const char* logText, ... )
{
	Int8 buffer[MAX_LOG_TEXT_LENGTH];
	
	va_list parameters ;
	va_start( parameters, logText);
	vsnprintf(buffer, MAX_LOG_TEXT_LENGTH ,logText, parameters);
	va_end(parameters);

	m_logText = buffer;

	if ( nullptr != spLogger )
	{
		spLogger->RecordDebugMessage(*this);
	}  
}

void CLoggerMsg::SetLogger( ILogger* pLogger )
{
  spLogger = pLogger;
}

void CLoggerMsg::SetDebugZone( const UInt8 dzMask)
{
  sDebugZoneMask = dzMask;
}

const char* CLoggerMsg::GetDBGZone() const
{
  switch(m_logDbgZone)
  {
  case ERROR:
    return textERROR;
  break;
  case WARNING:
    return textWARNING;
  break;
  case INFO:
    return textINFO;
  break;
  case DATA:
    return textDATA;
  break;
  default:;
  }
  return textNotAvailable;
}

const char* CLoggerMsg::GetLogText() const
{
  return m_logText;
}

const char* CLoggerMsg::GetSrcFileName() const
{
  return m_pSrcFileName ;
}

const UInt32 CLoggerMsg::GetLineNo() const
{
  return m_srcLineNo;
}

const UInt32 CLoggerMsg::GetTimeStamp() const
{
  return m_timeStamp;
}

}