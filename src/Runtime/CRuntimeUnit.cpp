#include "CRuntimeUnit.h"
#include "Logger.h"
#include <stdio.h>
#include <cstdlib>

namespace Runtime
{
CRuntimeUnit::CRuntimeUnit( const std::string& runtimeUnitName  )
: CExecutable(runtimeUnitName)
, m_logger( runtimeUnitName )
, m_messenger(runtimeUnitName)
, m_run(true)
, m_unitReturnValue(0)
, m_statusMsgTopic( "wojtech/" + runtimeUnitName + "/status")
{
}

CRuntimeUnit::~CRuntimeUnit()
{
}


void CRuntimeUnit::Initialize()
{
  HA_LOG(INFO, ("Initializing the runtime unit"));
  m_logger.Initialize();
	m_messenger.Initialize(this);
}


Int32 CRuntimeUnit::Run()
{
	while(m_run)
	{
		m_messenger.PeekMesseges();
		m_timerManager.TickTimer();
	}

	return m_unitReturnValue;
}

void CRuntimeUnit::Shutdown()
{
	m_messenger.Shutdown();
  m_logger.Shutdown();
}

void CRuntimeUnit::MQTTClientConnected()
{
  m_messenger.SetLWM(m_statusMsgTopic, "Offline");
  m_messenger.Publish( m_statusMsgTopic, "Online", 2, true);
}

void CRuntimeUnit::MQTTClientDisconnected()
{
}

}
