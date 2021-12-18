#include "CModemManager.h"

namespace oFonoIntegration
{

CModemManager::CModemManager()
: m_modemAutoactivation(true)
, m_defaultModem("")
, m_oFonoProxy(*this)
{

}

CModemManager::~CModemManager()
{

}

bool CModemManager::Initialize()
{
  m_oFonoProxy.Initialize();

  if (m_modemAutoactivation)
  {

  }

  auto modems = m_oFonoProxy.GetModemInfo();

  for ( auto modem : modems )
  {
    modem.ToString();
  }
  return true;
}

void CModemManager::Shutdown()
{
  m_oFonoProxy.Shutdown();
}

void CModemManager::NotifyModemAdded( const std::string& modemName)
{

}

void CModemManager::NotifyModemRemoved( const std::string& modemName )
{

}

void CModemManager::RefreshModemList()
{
  m_attachedModems = m_oFonoProxy.GetModemInfo();


  if ( m_modemControl )
  {
    bool modemStillConnected(false);
    for ( auto modem : m_attachedModems )
    {
      if ( m_modemControl->IsModemEqual( modem.GetDBUSModemPath(), modem.GetSystemPath() ) )
      {
        modemStillConnected = true;
      }
    }

    if (! modemStillConnected )
    {
      m_modemControl.release();
    }
  }

}

void CModemManager::AttachDefaultModem()
{
  std::string modemPath;
  std::string systemPath;
  if (1 == m_attachedModems.size() )
  {
    modemPath = m_attachedModems[0].GetDBUSModemPath();
    systemPath = m_attachedModems[0].GetSystemPath();  
  }

  m_modemControl = std::make_unique<CModem>(modemPath, systemPath);
}

}
