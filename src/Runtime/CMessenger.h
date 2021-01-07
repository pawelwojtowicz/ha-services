#pragma once
#include "IMessenger.h"
#include <mosquittopp.h>


namespace Runtime
{
class CMessenger    : public IMessenger
                    , private mosqpp::mosquittopp
{
public:
    CMessenger( const std::string& clientName );
    virtual ~CMessenger();

    bool Initialize();
    void Shutdown();

    void PeekMesseges();

private:
    //implementation of the IMessenger
    virtual bool Subscribe( const std::string& topic, IMsgSubscriber& subscriber );
    virtual bool Subscribe( const std::string& topicPrefix, const std::string& topicWildcard, IMsgSubscriber& subcriber);

private:
    bool Connect();
    void Disconnect();


private:
	//implementation of the mosqpp::mosquittopp callbacks
	virtual void on_connect(int /*rc*/);
	virtual void on_connect_with_flags(int /*rc*/, int /*flags*/) {return;}
	virtual void on_disconnect(int /*rc*/) {return;}
	virtual void on_publish(int /*mid*/) {return;}
	virtual void on_message(const struct mosquitto_message * /*message*/);
	virtual void on_subscribe(int /*mid*/, int /*qos_count*/, const int * /*granted_qos*/) {return;}
	virtual void on_unsubscribe(int /*mid*/) {return;}
	virtual void on_log(int /*level*/, const char * /*str*/) {return;}
	virtual void on_error() {return;}

private:
    std::string m_brokerIP;
    Int32 m_mqttTcpPort;

};

}