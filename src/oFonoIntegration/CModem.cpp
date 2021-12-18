#include "CModem.h"

namespace oFonoIntegration
{
CModem::CModem( const std::string& objectPath, const std::string& systemPath )
: m_objectPath( objectPath )
, m_systemPath( systemPath )
, m_modemProxy( m_objectPath , *this )
{

}

CModem::~CModem()
{

}

bool CModem::IsModemEqual( const std::string& objectPath, const std::string& systemPath )
{
    return ( ( m_objectPath == objectPath) && (systemPath == m_systemPath) );
}

void CModem::NotifySMSReceived( const std::string& senderNo, const std::string& message )
{

}

void CModem::NotifyNetMsgReceived( const std::string& message )
{

}


}