#include "CMessenger.h"
#include "Logger.h"

namespace Runtime
{

CMessenger::CMessenger( const std::string& clientId )
: mosqpp::mosquittopp( clientId.c_str() )
, m_brokerIP("127.0.0.1")
, m_mqttTcpPort(1883)
, m_rMessengerListener(nullptr)
{
	mosqpp::lib_init();
}

CMessenger::~CMessenger()
{
	mosqpp::lib_cleanup();
}

bool CMessenger::Initialize( IMessengerListener* rListener )
{
  m_rMessengerListener = rListener;
  Connect();
  return true;
}

bool CMessenger::SetLWM( const std::string& lwmTopic, const std::string& lwmPayload)
{
  return ( MOSQ_ERR_SUCCESS == will_set(lwmTopic.c_str(), lwmPayload.size(), lwmPayload.c_str(), 2, true) );
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


bool CMessenger::Subscribe( const std::string& topic, IMsgSubscriber* subscriber )
{
    auto subscriptionEntryIt = m_messageDispatchTable.find(topic);
    if (m_messageDispatchTable.end() != subscriptionEntryIt )
    {
        subscriptionEntryIt->second.first.insert( subscriber ) ;
        subscriptionEntryIt->second.second++;
        return true;
    }
    else
    {
        if ( MOSQ_ERR_SUCCESS == subscribe(nullptr, topic.c_str() ) )
        {
            tSubscriberList subscribers;
            subscribers.insert(subscriber);
            tSubscriptionEntry newSubscription = std::make_pair( subscribers, 0);
            m_messageDispatchTable.insert( tMessageDispatchTable::value_type( topic, newSubscription) );
            return true;
        }
    }
    
    return false;
}

bool CMessenger::Publish( const std::string& topic , const std::string& payload, const int qos, bool retain )
{
    publish( nullptr, topic.c_str(), static_cast<int>(payload.size()), payload.c_str(), static_cast<int>(qos),retain);

    return true;
}

void CMessenger::PeekMesseges()
{
    if ( mosq_err_t::MOSQ_ERR_NO_CONN == loop( 250 , 1) )
    {

    }

}

void CMessenger::on_connect(int rc)
{
  if (nullptr != m_rMessengerListener)
  {
    HA_LOG(INFO, ("Connected to the broker status=[%d]", rc));
    m_rMessengerListener->MQTTClientConnected();
  }
}

void CMessenger::on_disconnect(int rc )
{
  printf("Disconnect from broker\n");
  if (nullptr != m_rMessengerListener)
  {
    HA_LOG(INFO, ("Disconnected from the broker status=[%d]", rc));
    m_rMessengerListener->MQTTClientDisconnected();
  }
}

void CMessenger::on_message(const struct mosquitto_message *message )
{
    for ( auto& subscription : m_messageDispatchTable )
    {
        bool matches(false);
        mosqpp::topic_matches_sub(subscription.first.c_str(), message->topic, &matches);
        if ( matches )
        {
            std::string topic( message->topic);
            std::string payload( static_cast<const char*>(message->payload) , message->payloadlen );

            for ( auto& subscriber : subscription.second.first )
            {
                subscriber->HandleMessage( topic, payload);
            }
        } 
    }
}

}