#include "CLogger.h"
#include "CLoggerMsg.h"
#include <iostream>
#include <iomanip>

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
  std::cout << std::setw(15) << rLoggerMsg.GetTimeStamp() ;
  std::cout << "|" << std::setw(15) << m_runtimeUnitName.c_str();
  std::cout << "|" << std::setw(7) << rLoggerMsg.GetDBGZone();
  std::cout << "|" << std::setw(100) << rLoggerMsg.GetLogText();
  std::cout << "|" << std::setw(50) << rLoggerMsg.GetSrcFileName() << ":" << rLoggerMsg.GetLineNo() << std::endl ;
}

}