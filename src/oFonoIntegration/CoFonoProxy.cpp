#include "CoFonoProxy.h"
#include "IModemManagerEvents.h"
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
 
    return true;
}

void CoFonoProxy::Shutdown()
{
    
}

tModemList CoFonoProxy::GetModemInfo()
{
  tModemList modemList;
  if ( m_ofonoConnection )
  {
    toFonoModemInformation dBusModemInfo;
    m_ofonoConnection->callMethod(s_getModemsMethodName).onInterface(s_modemManagerIfName).storeResultsTo( dBusModemInfo );    

    for ( auto modemIter = dBusModemInfo.begin(); modemIter != dBusModemInfo.end() ; ++modemIter)
    {
      CModemContext modemInfo;
      
      modemInfo.SetDBUSModemPath( modemIter->get<0>().c_str() );
      auto modemProperties = modemIter->get<1>();

      modemInfo.SetOnline( modemProperties["Online"].get<bool>() );
      modemInfo.SetPowered( modemProperties["Powered"].get<bool>() );
      modemInfo.SetSystemPath( modemProperties["SystemPath"].get<std::string>() );
      tStringArray availableInterfaces = modemProperties["Interfaces"];
      for ( auto interfaceName : availableInterfaces )
      {
        modemInfo.AddInterface(interfaceName);
      }
      modemList.push_back(modemInfo);
    }
  }
  return modemList;
}

}
