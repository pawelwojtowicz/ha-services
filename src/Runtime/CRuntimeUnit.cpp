#include "CRuntimeUnit.h"
#include <stdio.h>
#include <cstdlib>

namespace Runtime
{
CRuntimeUnit::CRuntimeUnit( const std::string& runtimeUnitName  )
: CExecutable(runtimeUnitName)
, m_messenger(runtimeUnitName)
, m_run(true)
, m_unitReturnValue(0)
{
}

CRuntimeUnit::~CRuntimeUnit()
{
}


void CRuntimeUnit::Initialize()
{
	m_messenger.Initialize();
}


Int32 CRuntimeUnit::Run()
{
	while(m_run)
	{
		printf("polling 1 \n");

		m_messenger.PeekMesseges();

		printf("polling 2 \n");

		m_timerManager.TickTimer();

		printf("polling 3 \n");
	}

	return m_unitReturnValue;
}

void CRuntimeUnit::Shutdown()
{
	m_messenger.Shutdown();
}

}
