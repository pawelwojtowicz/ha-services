#include "CModem.h"
#include <iostream>

namespace oFonoIntegration
{
CModem::CModem( const std::string& objectPath, const std::string& systemPath )
: m_objectPath( objectPath )
, m_systemPath( systemPath )
, m_modemProxy( m_objectPath , *this )
{

}

CModem::~CModem()
{
  Shutdown();
}

bool CModem::Initialize()
{
  std::cout << "CModem::Initialize() " << std::endl;
  bool retVal = m_modemProxy.Initialize();
  return retVal;  
}

void CModem::Shutdown()
{
  std::cout << " CModem::Shutdown\n";
}

void CModem::PowerOn()
{
  std::cout << "Power On" << std::endl;
  m_modemProxy.PowerOn();
}

void CModem::PowerOff()
{
  m_modemProxy.PowerOff();
}

void CModem::Connect()
{
  std::cout << "Connect to the network" << std::endl;
  m_modemProxy.Connect() ;
}

void CModem::Disconnect()
{
  m_modemProxy.Disconnect();
}



bool CModem::IsModemEqual( const std::string& objectPath, const std::string& systemPath )
{
    return ( ( m_objectPath == objectPath) && (systemPath == m_systemPath) );
}

void CModem::NotifySMSReceived( const std::string& senderNo, const std::string& message )
{
  std::cout << "New SMS: " << message.c_str() << std::endl;
}

void CModem::NotifyNetMsgReceived( const std::string& message )
{

}


}