#ifndef EC_Event_H
#define EC_Event_H

#include "EC_Common.h"

namespace ElvCore
{
	class Event
	{
	public:
		Event( void );
		Event( const Event& evt );
		Event& operator = ( const Event& evt );

		Event( DWORD id, float delay, ParameterSet* param, Object* sender = NULL, Object* receiver = NULL );
		~Event( void );

		ParameterSet* Param( void );
		const ParameterSet* Param( void ) const;

		Object* pSender;
		Object* pReceiver;

		DWORD dwID;
		float fDelay;

	private:
		ParameterSet* pParam;
	};

	inline bool operator < ( const Event& evtLeft, const Event& evtRight )
	{
		return evtLeft.fDelay < evtRight.fDelay;
	}
}

#endif