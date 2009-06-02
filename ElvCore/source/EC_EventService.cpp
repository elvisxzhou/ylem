#include "EC_EventService.h"

namespace ElvCore
{
	EventService::EventService(unsigned int id,std::string name)
	:	Service(id,name)
    {
    }
    
    EventService::~EventService()
    {

    }

    bool EventService::initialize(ParameterSet*)
    {
        return true;
    }
    
    bool EventService::shutdown()
    {
        return true;
    }
    
    bool EventService::update(float timestep)
    {
        return true;
    }

	bool EventService::addEventCallBack(EventCallback * eventCallback_)
	{
		if(!eventCallback_){ return false; }
		EventCBSet::size_type size = _eventCallbacks.size();
		_eventCallbacks.insert(EventPair(eventCallback_->priority(), eventCallback_) ); 
		return size < _eventCallbacks.size(); 
	}

	void EventService::dispatchMsg(int msg,float delay,Object* sender,Object* receiver, ParameterSet* pset)
	{
		for (EventCBSet::iterator i = _eventCallbacks.begin(); 
			i != _eventCallbacks.end(); ++i)
		{
			(*i).second->onEvent(msg,sender,pset);
		}


	}

}

