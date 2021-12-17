#pragma once

namespace oFonoIntegration
{

class ITextMessageEvents
{
public:
  ITextMessageEvents() {};
  virtual ~ITextMessageEvents() {};

  virtual void NotifySMSReceived( const std::string& senderNo, const std::string& message ) = 0;
  virtual void NotifyNetMsgReceived( const std::string& message ) = 0;

};
}