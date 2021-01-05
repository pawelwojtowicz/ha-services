#include "CStateMachine.h"
#include "IActionFactory.h"
#include "ICSMConfigurator.h"
#include "IAction.h"
#include "CState.h"
#include "CTransition.h"
#include <UCL/CFastHash.h>
#include <algorithm>
#include <stdio.h>
namespace CSM
{
static const UInt32 cUInt32_CSM_HashSeed = 0x11FF;


CStateMachine::CStateMachine()
: m_pActionFactory(0)
, m_pCurrentState(0)
{
}

CStateMachine::~CStateMachine()
{
}
	
bool CStateMachine::Initialize( ICSMConfigurator* pConfigurator, IActionFactory* pActionFactory)
{
	m_pActionFactory = pActionFactory;
		
	if ( 0!= pConfigurator && 0 != m_pActionFactory  )
	{
		return pConfigurator->InitializeStateMachine(this);
	}
	return false;
}


void CStateMachine::AddState(	const std::string& parentName, 
															const std::string& stateName, 
															const std::string& enterActionName, 
															const std::string& leafActionName, 
															const std::string& exitActionName)
{
	CState* pParentState(0);
	
	IAction* pEnterAction(0);
	IAction* pLeafAction(0);
	IAction* pExitAction(0);
	
	UInt32 parentNameHash(UCL::CFastHash::CalculateHash32(parentName, cUInt32_CSM_HashSeed));
	UInt32 stateNameHash(UCL::CFastHash::CalculateHash32(stateName, cUInt32_CSM_HashSeed));
	
	if ( 0 != m_pActionFactory )
	{
		if ( !enterActionName.empty() )
		{
			pEnterAction = m_pActionFactory->GetAction(enterActionName);
		}
		
		if ( !leafActionName.empty() )
		{
			pLeafAction = m_pActionFactory->GetAction(leafActionName);
		}
		
		if ( !exitActionName.empty() )
		{
			pExitAction = m_pActionFactory->GetAction(exitActionName);
		}
	}
	
	if ( !parentName.empty() )
	{
		tStateMapIterator parentStateIterator( m_stateMap.find(parentNameHash) );
		if ( m_stateMap.end() != parentStateIterator )
		{
			pParentState = parentStateIterator->second;
		}
		else
		{
			pParentState = new CState( 0 , parentName, 0 , 0, 0 );
		
			m_stateMap.insert( tStateMap::value_type(parentNameHash,pParentState));
		}	
	}
	
	tStateMapIterator stateIterator(m_stateMap.find(stateNameHash));
	if ( m_stateMap.end() == stateIterator )
	{
		CState* pState = new CState( pParentState, stateName, pEnterAction, pLeafAction, pExitAction );
		m_stateMap.insert( tStateMap::value_type(stateNameHash,pState));

	}
	else
	{
		stateIterator->second->UpdateState(pParentState, pEnterAction, pLeafAction, pExitAction);
	}	
}
	
void CStateMachine::AddTransition(	const std::string& eventName,
																		const std::string& sourceStateName, 
																		const std::string& targetStateName, 
																		const std::string& conditionName, 
																		const std::string& actionName)
{
	UInt32 eventNameHash(UCL::CFastHash::CalculateHash32(eventName, cUInt32_CSM_HashSeed));
	UInt32 sourceNameHash(UCL::CFastHash::CalculateHash32(sourceStateName, cUInt32_CSM_HashSeed));
	UInt32 targetNameHash(UCL::CFastHash::CalculateHash32(targetStateName, cUInt32_CSM_HashSeed));
	
	CState* pSourceState(0);
	CState* pTargetState(0);
	IAction* pTransitionAction(0);
	ICondition* pTransitionCondition(0);
	
	tStateMapConstIterator pSourceStateIter(m_stateMap.find(sourceNameHash));
	if ( m_stateMap.end() != pSourceStateIter )
	{
		pSourceState = pSourceStateIter->second;
	}
	
	tStateMapConstIterator pTargetStateIter(m_stateMap.find(targetNameHash));
	if ( m_stateMap.end() != pTargetStateIter )
	{
		pTargetState = pTargetStateIter->second;
	}
	
	if ( 0 != pSourceState && 0 != pTargetState )
	{
		if ( 0 !=m_pActionFactory )
		{
			if ( !conditionName.empty() )
			{
				pTransitionCondition = m_pActionFactory->GetCondition(conditionName);
			}
		
			if ( !actionName.empty() )
			{
				pTransitionAction = m_pActionFactory->GetAction(actionName);
			}
		}
		
		CTransition* pTransition = new CTransition( eventName , 
																								pTransitionCondition, 
																								pTransitionAction, 
																								pTargetState);
																								
		pSourceState->AddTransition( eventNameHash , pTransition );
	}
}

void CStateMachine::SetInitialState( const std::string& initialState)
{
	UInt32 initialStateNameHash(UCL::CFastHash::CalculateHash32(initialState, cUInt32_CSM_HashSeed));
	
	tStateMapConstIterator pInitialStateIter(m_stateMap.find(initialStateNameHash));
	if ( m_stateMap.end() != pInitialStateIter )
	{
		m_pCurrentState = pInitialStateIter->second;
	}

}


bool CStateMachine::DispatchEvent( const std::string& eventName )
{
	UInt32 eventNameHash(UCL::CFastHash::CalculateHash32( eventName, cUInt32_CSM_HashSeed));

	return DispatchEvent(eventNameHash);
}

bool CStateMachine::DispatchEvent( const UInt32 eventNameHash )
{
	if ( 0 != m_pCurrentState )
	{
		CTransition* pTransition( m_pCurrentState->GetTransition( eventNameHash ) );
		
		// there is a transition, which fits the nameHash and the condition
		if ( 0 != pTransition )
		{
			CState* pTargetState( pTransition->GetTargetState() );
			
			tStateList sourceStates;
			tStateList targetStates;
			
			//prepare the list of the parents of target and source states
			//it will be used to evaluate the set of enter/exit actions to be exeuted
			CState* pState(m_pCurrentState);
			while ( 0 != pState )
			{
				sourceStates.push_back( pState );
				pState = pState->GetParent();
			}
			
			pState = pTargetState;
			while ( 0 != pState )
			{
				targetStates.push_back( pState );
				pState = pState->GetParent();
			}
			
			// iterate through all of the source states, starting from current state
			// and execute the exit action for all of the states , that are not present
			// in the target state list.
			for ( tStateListIterator iter = sourceStates.begin() ; sourceStates.end() != iter ; ++iter)
			{
				tStateListIterator targetIter = std::find(targetStates.begin(), targetStates.end() , *iter );
				if ( targetStates.end() == targetIter )
				{
					(*iter)->ExecuteExitAction();
				}
			}
			
			// execute the transition action in the middle of the transition
			pTransition->ExecuteAction();
			
			// execute the enter action on the state and all it's parens, which were not
			// present in the origin state.
			for ( tStateListReverseIterator iter = targetStates.rbegin() ; targetStates.rend() != iter ; ++iter)
			{
				tStateListIterator sourceIter = std::find(sourceStates.begin(), sourceStates.end() , *iter );
				if ( sourceStates.end() == sourceIter )
				{
					(*iter)->ExecuteEnterAction();
				}
			}			
			
			if ( m_pCurrentState != pTargetState )
			{
				//change the current state to the target of the transition
				m_pCurrentState = pTargetState;
			
				// Execute Leaf Action for the currentState in case it's different from previous one.
				m_pCurrentState->ExecuteLeafAction();
			}
		}
	
		return true;
	}

	return false;
}
}
