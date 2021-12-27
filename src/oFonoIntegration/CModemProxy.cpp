#include "CModemProxy.h"
#include "ITextMessageEvents.h"
#include "oFonoTypes.h"
#include <iostream>

namespace oFonoIntegration
{


CModemProxy::CModemProxy(const std::string& modemObjectPath, ITextMessageEvents& listener)
: m_modemObjectPath(modemObjectPath)
, m_rTextMessageEventsListener(listener)
, m_modemConnection(nullptr)
{
}
CModemProxy::~CModemProxy()
{
}

bool CModemProxy::Initialize()
{
  bool result(false);

  std::cout << "creating new interface on: " << m_modemObjectPath.c_str() << std::endl;

  sleep(1);

  m_modemConnection = sdbus::createProxy( s_ofonoEndpoint, m_modemObjectPath );
  std::cout << "udalo sie: " << m_modemObjectPath.c_str() << std::endl;

  if ( m_modemConnection )
  {
    m_modemConnection->uponSignal(s_incommingMessageSignalName).onInterface(s_messageManagerIfName).call( [this](std::string message, tMessageInfoDict msgInfo) {
        printf("Dostałem %s", message.c_str());
        std::string sender(msgInfo["Sender"].get<std::string>());

        this->m_rTextMessageEventsListener.NotifySMSReceived( sender, message) ;
    } );
    m_modemConnection->finishRegistration();
    result = true;
  }

  return result;
}

void CModemProxy::Shutdown()
{
}

void CModemProxy::SetPower( const bool power )
{
  if (m_modemConnection)
  {
    m_modemConnection->callMethod(s_modemMethodSetProperty).onInterface(s_modemIfName).withArguments(s_modemProperty_Powered, sdbus::Variant(power) );
  }
}

void CModemProxy::SetOnline( const bool online )
{
  if (m_modemConnection)
  {
    m_modemConnection->callMethod(s_modemMethodSetProperty).onInterface(s_modemIfName).withArguments(s_modemProperty_Online, sdbus::Variant(online) );
  }
}

void CModemProxy::SendSMS(const std::string& dstNumber, const std::string& message)
{
  if ( m_modemConnection )
  {
    m_modemConnection->callMethod(s_sendSMSMethodName).onInterface(s_messageManagerIfName).withArguments(dstNumber,message);
  }
}

}