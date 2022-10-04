#include "CLogger.h"
#include "CLoggerMsg.h"
#include <iostream>

namespace Runtime
{
CLogger::CLogger( const std::string& runtimeUnitName)
: m_runtimeUnitName( runtimeUnitName)
{
  CLoggerMsg::SetLogger(this);
}

CLogger::~CLogger()
{

}

bool CLogger::Initialize()
{

}

void CLogger::Shutdown()
{

}

void CLogger::RecordDebugMessage( const CLoggerMsg& rLoggerMsg)
{
  std::cout << rLoggerMsg.GetTimeStamp() << "|" 
            << m_runtimeUnitName.c_str() << "|"
            << rLoggerMsg.GetDBGZone() << "|"
            << rLoggerMsg.GetLogText() << "|"
            << rLoggerMsg.GetSrcFileName() << ":" << rLoggerMsg.GetLineNo() << std::endl ;
}

}