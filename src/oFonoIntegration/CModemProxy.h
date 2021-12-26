#pragma once
#include <sdbus-c++/sdbus-c++.h>

namespace oFonoIntegration
{
class ITextMessageEvents;

class CModemProxy
{
public:
  CModemProxy( const std::string& modemObjectPath, ITextMessageEvents& listener);
  virtual ~CModemProxy();

  bool Initialize();
  void Shutdown();

  void PowerOn();
  void PowerOff();

  void Connect();
  void Disconnect();

  void SendSMS(const std::string& dstNumber, const std::string& message);

private:
    std::string m_modemObjectPath;
    std::unique_ptr<sdbus::IProxy> m_modemConnection;

    ITextMessageEvents& m_rTextMessageEventsListener;
};

}