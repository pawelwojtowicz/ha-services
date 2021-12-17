#include "CModemManager.h"

namespace oFonoIntegration
{

CModemManager::CModemManager()
: m_oFonoProxy(*this)
{

}

CModemManager::~CModemManager()
{

}

bool CModemManager::Initialize()
{
  m_oFonoProxy.Initialize();
  return true;
}

void CModemManager::Shutdown()
{

}

void CModemManager::NotifyModemAdded( const std::string& modemName)
{

}

void CModemManager::NotifyModemRemoved( const std::string& modemName )
{

}



}
