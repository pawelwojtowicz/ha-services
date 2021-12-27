#include "CModemManager.h"
#include <iostream>

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
  std::cout << "bool CModemManager::Initialize()" << std::endl;
  m_oFonoProxy.Initialize();

  RefreshModemList();
  AttachDefaultModem();

  return true;
}

void CModemManager::Shutdown()
{
  m_oFonoProxy.Shutdown();
}

void CModemManager::NotifyModemAdded( const std::string& modemName)
{
  RefreshModemList();
  AttachDefaultModem();

}

void CModemManager::NotifyModemRemoved( const std::string& modemName )
{
  RefreshModemList();
  AttachDefaultModem();
}

void CModemManager::RefreshModemList()
{
  m_attachedModems = m_oFonoProxy.GetModemInfo();
  for (auto modemInfo : m_attachedModems )
  {
    modemInfo.ToString();
  }

  if ( m_modemControl )
  {
    bool modemStillConnected(false);
    for ( auto modem : m_attachedModems )
    {
      modem.ToString();
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

    m_modemControl = std::make_unique<CModem>(modemPath, systemPath);

    m_modemControl->Initialize();
    m_modemControl->PowerOn();
    m_modemControl->Connect();
  }


}

}
