#include "CModemContext.h"
#include <iostream>

namespace oFonoIntegration
{

CModemContext::CModemContext()
: m_dbusModemPath("")
, m_online(false)
, m_powered(false)
, m_systemPath("")
{
}

CModemContext::CModemContext( const CModemContext& ctx )
: m_dbusModemPath(ctx.m_dbusModemPath)
, m_online(ctx.m_online)
, m_powered(ctx.m_powered)
, m_systemPath(ctx.m_systemPath)
, m_interfaces(ctx.m_interfaces)
{
}

CModemContext::~CModemContext()
{
}

void CModemContext::AddInterface( const std::string& interfaceName)
{
  m_interfaces.insert(interfaceName);
}

bool CModemContext::IsSMSServiceActive() const
{
  return ( m_interfaces.end() != m_interfaces.find( "org.ofono.MessageManager") );
}

void CModemContext::ToString() const
{
  std::cout << m_dbusModemPath.c_str() << " powered=" << m_powered << " online=" << m_online << std::endl;
  std::cout << m_dbusModemPath.c_str() << "Interfaces [";
  for ( auto interfaceName : m_interfaces )
  {
    std::cout << interfaceName << ",";
  }
  std::cout << "]" << std::endl; 
}

}