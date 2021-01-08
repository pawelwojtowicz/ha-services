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
    disconnect();
}


bool CMessenger::Subscribe( const std::string& topic, IMsgSubscriber& subscriber )
{
    return Subscribe( topic, topic, subscriber);
}

bool CMessenger::Subscribe( const std::string& topicPrefix, const std::string& topicWildcard, IMsgSubscriber& subcriber)
{
    return false;
}

bool CMessenger::Publish( const std::string& topic , const std::string& payload, const MQTT_QOS qos, bool retain )
{
    publish( nullptr, topic.c_str(), static_cast<int>(payload.size()), payload.c_str(), static_cast<int>(qos),retain);   
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

void CMessenger::on_disconnect(int rc )
{
    printf("Disconnect from broker\n");
}

void CMessenger::on_message(const struct mosquitto_message * message )
{

}

}