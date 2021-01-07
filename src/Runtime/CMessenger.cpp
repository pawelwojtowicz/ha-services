#include "CMessenger.h"

namespace Runtime
{

CMessenger::CMessenger( const std::string& clientId )
: mosqpp::mosquittopp( clientId.c_str() )
, m_brokerIP("127.0.0.1")
, m_mqttTcpPort(1883)
{
	mosqpp::lib_init();

}

CMessenger::~CMessenger()
{
	mosqpp::lib_cleanup();

}

bool CMessenger::Initialize()
{
    Connect();

    return true;
}

void CMessenger::Shutdown()
{

}

bool CMessenger::Connect()
{
    return ( MOSQ_ERR_SUCCESS != connect(m_brokerIP.c_str(), m_mqttTcpPort ) );
}

void CMessenger::Disconnect()
{

}


bool CMessenger::Subscribe( const std::string& topic, IMsgSubscriber& subscriber )
{
    return Subscribe( topic, topic, subscriber);
}

bool CMessenger::Subscribe( const std::string& topicPrefix, const std::string& topicWildcard, IMsgSubscriber& subcriber)
{
    return false;
}

void CMessenger::PeekMesseges()
{
    if ( mosq_err_t::MOSQ_ERR_NO_CONN == loop( 250 , 1) )
    {

    }

}

void CMessenger::on_connect(int rc)
{
    printf("Connected to the broker dog %d\n", rc);
}

void CMessenger::on_message(const struct mosquitto_message * message )
{

}

}