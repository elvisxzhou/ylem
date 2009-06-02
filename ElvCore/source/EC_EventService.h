#ifndef EC_EventService_H
#define EC_EventService_H

#include "EC_Service.h"


namespace ElvCore
{
	class EventCallback
	{
	public:
		EventCallback(unsigned int const priority_)
			: _priority(priority_)
		{}

		void priority(unsigned int const priority_){ _priority = priority_;	}
		unsigned int const priority(void) const { return _priority; }

		virtual bool onEvent(int evt,Object* sender,ParameterSet* pSet){ return false; }
	private:
		unsigned int _priority;
	};

	class EventService : public Service
    {
    public:
		EventService(unsigned int,std::string);
        ~EventService();

        bool initialize(ParameterSet*);
        bool shutdown();
        bool update(float timestep);
		bool addEventCallBack(EventCallback * eventCallback_);

		void dispatchMsg(int msg,float delay,Object* sender,Object* receiver, ParameterSet* pset = NULL);

	private:
		typedef std::pair<unsigned int, EventCallback *> EventPair;
		typedef std::set< std::pair<unsigned int, EventCallback *> > EventCBSet;

		EventCBSet _eventCallbacks;
    };
}


#endif
