#pragma once
#include "IMessenger.h"
#include "IMessengerListener.h"
#include <mosquittopp.h>
#include <set>

namespace Runtime
{
class CMessenger    : public IMessenger
                    , private mosqpp::mosquittopp
{
    using tSubscriberList = std::set<IMsgSubscriber*>;
    using tSubscriptionEntry = std::pair<tSubscriberList, Int32 >;
    using tMessageDispatchTable = std::map<std::string, tSubscriptionEntry>;
public:
    CMessenger( const std::string& clientName );
    virtual ~CMessenger();

    bool Initialize( IMessengerListener* rListener );
    void Shutdown();

    void PeekMesseges();

    bool SetLWM( const std::string& lwmTopic, const std::string& lwmPayload);

    //implementation of the IMessenger
    virtual bool Publish( const std::string& topic , const std::string& payload, const int qos, bool retain );
    virtual bool Subscribe( const std::string& topic, IMsgSubscriber* subscriber ) override;

private:
    bool Connect();
    void Disconnect();


private:
	//implementation of the mosqpp::mosquittopp callbacks
	virtual void on_connect(int /*rc*/);
	virtual void on_connect_with_flags(int /*rc*/, int /*flags*/) {};
	virtual void on_disconnect(int /*rc*/) ;
	virtual void on_publish(int /*mid*/) {return;}
	virtual void on_message(const struct mosquitto_message * /*message*/);
	virtual void on_subscribe(int /*mid*/, int /*qos_count*/, const int * /*granted_qos*/) {return;}
	virtual void on_unsubscribe(int /*mid*/) {return;}
	virtual void on_log(int /*level*/, const char * /*str*/) {return;}
	virtual void on_error() {return;}

private:
    std::string m_brokerIP;
    Int32 m_mqttTcpPort;

    tMessageDispatchTable m_messageDispatchTable;

    IMessengerListener* m_rMessengerListener;
};

}