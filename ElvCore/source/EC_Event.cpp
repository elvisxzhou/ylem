#include "EC_Event.h"
#include "EC_Object.h"
#include "EC_Component.h"
#include "EC_ParameterSet.h"

namespace ElvCore
{
	Event::Event( void )
	{
		pSender = NULL;
		pReceiver = NULL;
		dwID = 0;
		fDelay = 0.0f;
		pParam = ParameterSet::GetNewParameterSet();
		pParam->ConvertToTable();
	}

	Event::Event( const Event& evt )
	{
		pParam = NULL;
		*this = evt;
	}

	Event::Event( DWORD id, float delay, ParameterSet* param, Object* sender, Object* receiver /* = NULL */ )
	{
		dwID = id;
		fDelay = delay;
		pParam = param;
		pSender = sender;
		pReceiver = receiver; 
	}

	Event& Event::operator = ( const Event& evt )
	{
		if( NULL != pParam )
		{
			ParameterSet::FreeParameterSet( pParam );
			pParam = NULL;
		}
		pSender = evt.pSender;
		pReceiver = evt.pReceiver;
		dwID = evt.dwID;
		fDelay = evt.fDelay;
		pParam = ParameterSet::GetNewParameterSet();
		pParam->ConvertToTable();
		*pParam = *(evt.pParam);

		return *this;
	}

	Event::~Event(void)
	{
		ParameterSet::FreeParameterSet( pParam );
	}

	ParameterSet* Event::Param( void )
	{
		return pParam;
	}

	const ParameterSet* Event::Param( void ) const
	{
		return pParam;
	}
}