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
	int c(0);
	while(m_run)
	{

		m_messenger.PeekMesseges();

		m_timerManager.TickTimer();
		printf("polling %d \n", c++);
	}

	return m_unitReturnValue;
}

void CRuntimeUnit::Shutdown()
{
	m_messenger.Shutdown();
}

}
