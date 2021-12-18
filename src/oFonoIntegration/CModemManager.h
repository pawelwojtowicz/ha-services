#pragma once
#include <string>
#include "CoFonoProxy.h"
#include "CModemContext.h"
#include "IModemManagerEvents.h"
namespace oFonoIntegration
{
class CModemManager : public IModemManagerEvents
{
public:
    CModemManager();
    virtual ~CModemManager();

    bool Initialize();
    void Shutdown();

private:
  void NotifyModemAdded( const std::string& modemName) override;
  void NotifyModemRemoved( const std::string& modemName ) override;

private:
  CoFonoProxy m_oFonoProxy;
};
}
