#pragma once

namespace oFonoIntegration
{

class IModemManagerEvents
{
public:
  IModemManagerEvents() {};
  virtual ~IModemManagerEvents() {};

  virtual void NotifyModemAdded( const std::string& modemName) = 0;
  virtual void NotifyModemRemoved( const std::string& modemName ) = 0;

private:
  IModemManagerEvents( const IModemManagerEvents&);
  IModemManagerEvents& operator=(const IModemManagerEvents&);
};

}