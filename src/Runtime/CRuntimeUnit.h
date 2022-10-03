#pragma once
#include "CExecutable.h"
#include "CMessenger.h"
#include "CTimerManager.h"
#include "IMessengerListener.h"

namespace Runtime
{
class CRuntimeUnit: public CExecutable, public IMessengerListener
{
public:
	CRuntimeUnit( const std::string& runtimeUnitName );
	virtual ~CRuntimeUnit();

	//initialization of the unit
	virtual void Initialize();

	//main thread of the unit - meesage processor runs in this thread
	virtual Int32 Run();

	//called right before shutdown - release all the resources here
	virtual void Shutdown();

  virtual void MQTTClientConnected();

  virtual void MQTTClientDisconnected();

private:
	void HandleMessage( const std::string& topic, const std::string& payload);

protected:
	ITimerManager& GetTimerManager() { return m_timerManager; };

	IMessenger& GetMessenger() { return m_messenger; };

private:
    bool m_run;

	CMessenger m_messenger;

	CTimerManager m_timerManager;

	Int32 m_unitReturnValue;
};

}