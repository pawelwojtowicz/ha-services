#pragma once

namespace Runtime
{
class IMessengerListener
{
public:
  IMessengerListener() = default;
  virtual ~IMessengerListener() = default;

  virtual void MQTTClientConnected() = 0;
  virtual void MQTTClientDisconnected() = 0;

};
}