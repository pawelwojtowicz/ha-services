#ifndef RUNTIME_CRUNTIMEUNIT_H
#define RUNTIME_CRUNTIMEUNIT_H
#include "CExecutable.h"
#include "Logger/CLoggingAgent.h"
#include "CTimerManager.h"
#include "CMessage.h"
#include "ControllerInterface/IControllerListener.h"
#include "ControllerInterface/CControllerProxy.h"
#include "CHealthReporter.h"
#include <stdio.h>

namespace Runtime
{
class CRuntimeUnit: public CExecutable,
										public Controller::IControllerListener
{
public:
	CRuntimeUnit( const std::string& runtimeUnitName, const std::string& runtimeUnitQueueName );
	virtual ~CRuntimeUnit();

	//initialization of the unit
	virtual void Initialize();

	//main thread of the unit - meesage processor runs in this thread
	virtual Int32 Run();

	//called right before shutdown - release all the resources here
	virtual void Shutdown();

	//used implicitly by the timer - the method enqueues the timer messasges	
	virtual void NotifyTimer();

protected:
	IMessenger& GetMessenger() { return m_messenger;};

	void InitializeTimerManager();

	ITimerManager& GetTimerManager() { return m_timerManager; };

	Controller::CControllerProxy& GetControllerProxy() { return m_controllerProxy; };

	const std::string GetUnitQueueName() { return m_unitQueueName; };

	void SetIddle();
	void SetBusy();
	void SetError();

	void InitDone(const bool& status);

private:
	virtual void NotifyShutdownPending();

	virtual void ShutdownProcess();

private:
	Logger::CLoggingAgent m_loggingAgent;

	CMessenger m_messenger;

	CTimerManager m_timerManager;

	Controller::CControllerProxy m_controllerProxy;

	CHealthReporter m_healthReporter;

	CMessage m_timerMessage;

	std::string m_unitQueueName;

	Int32 m_unitReturnValue;
};

}
#endif
