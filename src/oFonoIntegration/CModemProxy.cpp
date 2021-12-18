#include "CModemProxy.h"
#include "ITextMessageEvents.h"
#include "oFonoTypes.h"

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

  m_modemConnection = sdbus::createProxy( s_ofonoEndpoint, m_modemObjectPath.c_str() );
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

void CModemProxy::SendSMS(const std::string& dstNumber, const std::string& message)
{
  if ( m_modemConnection )
  {
    m_modemConnection->callMethod(s_sendSMSMethodName).onInterface(s_messageManagerIfName).withArguments(dstNumber,message);
  }
}

}