#pragma once
#include <string>
#include "CoFonoProxy.h"
#include "CModemContext.h"
#include "IModemManagerEvents.h"
#include "CModem.h"

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
  void AttachDefaultModem();
  void RefreshModemList();

private:
  bool m_modemAutoactivation;
  std::string m_defaultModem;
  CoFonoProxy m_oFonoProxy;

  tModemList m_attachedModems;

  std::unique_ptr<CModem> m_modemControl;
};
}
