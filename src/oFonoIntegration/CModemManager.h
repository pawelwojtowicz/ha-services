#pragma once

namespace oFonoIntegration
{
class CModemManager
{
public:
    CModemManager();
    virtual ~CModemManager();

    bool Initialize();
    void Shutdown();

private:

};
}