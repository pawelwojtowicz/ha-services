#pragma once
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


    void GetModemInfo();

    void SendSMS(const std::string& dstNumber, const std::string& message);

private:
    std::unique_ptr<sdbus::IProxy> m_ofonoConnection;

private:
    IModemManagerEvents& m_modemManagerListener;
};
}
