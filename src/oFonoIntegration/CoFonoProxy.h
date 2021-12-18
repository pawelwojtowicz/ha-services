#pragma once
#include "CModemContext.h"
#include "IModemManagerEvents.h"
#include <sdbus-c++/sdbus-c++.h>

namespace oFonoIntegration
{

class IModemManagerEvents;

class CoFonoProxy
{
public:
    CoFonoProxy(IModemManagerEvents& rModemEventsListener);
    virtual ~CoFonoProxy();

    bool Initialize();
    void Shutdown();

    tModemList GetModemInfo();
private:
    std::unique_ptr<sdbus::IProxy> m_ofonoConnection;

private:
    IModemManagerEvents& m_modemManagerListener;
};
}
