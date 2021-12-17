#include "CoFonoProxy.h"
#include "IModemManagerEvents.h"
#include "ITextMessageEvents.h"
#include "oFonoTypes.h"
#include <stdio.h>

namespace oFonoIntegration
{
CoFonoProxy::CoFonoProxy(IModemManagerEvents& rModemEventsListener)
: m_ofonoConnection(nullptr)
, m_modemManagerListener(rModemEventsListener)
{

}

CoFonoProxy::~CoFonoProxy()
{
}

bool CoFonoProxy::Initialize()
{
    m_ofonoConnection = sdbus::createProxy( s_ofonoEndpoint, "/" );

    m_ofonoConnection->uponSignal(s_modemAddedSignalName).onInterface(s_modemManagerIfName).call( [this](sdbus::ObjectPath name) { 
        printf("modem INserted");
        this->m_modemManagerListener.NotifyModemAdded( name ) ;
    });
    m_ofonoConnection->uponSignal(s_modemRemovedSignalName).onInterface(s_modemManagerIfName).call( [this](sdbus::ObjectPath name) {
        printf("modem removed");
        this->m_modemManagerListener.NotifyModemRemoved( name ); 
    } );
    m_ofonoConnection->finishRegistration();

    GetModemInfo();

    while(1) {int i = 0;}
 
    return true;
}

void CoFonoProxy::Shutdown()
{
    
}

void CoFonoProxy::GetModemInfo()
{
    if ( m_ofonoConnection )
    {
        toFonoModemInformation dBusModemInfo;
        m_ofonoConnection->callMethod(s_getModemsMethodName).onInterface(s_modemManagerIfName).storeResultsTo( dBusModemInfo );    

        for ( auto iterek = dBusModemInfo.begin(); iterek != dBusModemInfo.end() ; ++iterek)
        {
            printf("--> %s\n", iterek->get<0>().c_str());
        }
    }
}

}
