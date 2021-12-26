#pragma once
#include <string>
#include "CModemProxy.h"
#include "ITextMessageEvents.h"

namespace oFonoIntegration
{

class CModem : ITextMessageEvents
{
public:
  CModem( const std::string& objectPath, const std::string& systemPath);
  virtual ~CModem();

  bool Initialize();
  void Shutdown();

  void PowerOn();
  void PowerOff();

  

  bool IsModemEqual( const std::string& objectPath, const std::string& systemPath );

private:
  virtual void NotifySMSReceived( const std::string& senderNo, const std::string& message ) override;
  virtual void NotifyNetMsgReceived( const std::string& message ) override ;


private:
  CModem(const CModem&);
  CModem& operator=(const CModem&);

private:
  std::string m_objectPath;
  std::string m_systemPath;

  CModemProxy m_modemProxy;
};
}