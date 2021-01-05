#include "CState.h"
#include "IAction.h"
#include "CTransition.h"


namespace CSM
{
CState::CState( CState* pParentState, const std::string& stateName, IAction* enterAction, IAction* leafAction, IAction* exitAction)
: m_pParentState(pParentState)
, m_stateName(stateName)
, m_pEnterAction(enterAction)
, m_pLeafAction(leafAction)
, m_pExitAction(exitAction)	
{
}
	
CState::~CState()
{
	for (	tTranstionIterator pIter = m_nameHashToTransitionMap.begin() ; 
				m_nameHashToTransitionMap.end() != pIter ; 
				++pIter)
	{
		delete pIter->second;
	}
}

void CState::UpdateState(CState* pParentState, IAction* enterAction, IAction* leafAction, IAction* exitAction)
{
	m_pParentState = pParentState;
	m_pEnterAction = enterAction;
  m_pLeafAction = leafAction;
  m_pExitAction = exitAction;
}


const std::string& CState::GetName() const
{
	return m_stateName;
}

CState* CState::GetParent() const
{
	return m_pParentState;
}

void CState::AddTransition( const UInt32 eventNameHash, CTransition* pTransition )
{
	m_nameHashToTransitionMap.insert( tTransitionMap::value_type(eventNameHash, pTransition));
}
	
void CState::ExecuteEnterAction()
{
	if ( 0 != m_pEnterAction )
	{
		m_pEnterAction->Execute();
	}
}

void CState::ExecuteLeafAction()
{
	if ( 0 != m_pLeafAction )
	{
		m_pLeafAction->Execute();
	}
}

void CState::ExecuteExitAction()
{
	if ( 0 != m_pExitAction )
	{
		m_pExitAction->Execute();
	}
}

CTransition* CState::GetTransition( const UInt32 eventNameHash )
{
	tTranstionIterator beginIter( m_nameHashToTransitionMap.lower_bound( eventNameHash) );
	tTranstionIterator endIter( m_nameHashToTransitionMap.upper_bound( eventNameHash ) );
																							
	for ( ; beginIter != endIter ; ++beginIter)
	{
		if ( beginIter->second->CanExecute() )
		{
			return beginIter->second;
		}
	}
	
	return 0;
}


}
