#pragma once

namespace oFonoIntegration
{
class CofonoProxy
{
public:
CofonoProxy();
virtual ~CofonoProxy();

bool Initialize();
void Shutdown();

};
}