#include "EG_FSM.h"

namespace ElvGame
{
	FSM::FSM()
	{
	}

	FSM::~FSM()
	{
	}

	bool FSM::update(float timestep)
	{
		for(FsmMap::iterator it = mFSMs.begin(); it != mFSMs.end(); ++it)
		{
			if(!it->second.empty())
				SCRIPT->runCommand("%s.update(%s,%f);",it->second.c_str(),it->second.c_str(),timestep);
		}

		return true;
	}

	void FSM::changeState(std::string fsm,std::string state)
	{
		FsmMap::iterator it = mFSMs.find(fsm);
		if(it == mFSMs.end())
		{
			if(!state.empty())
			{
				SCRIPT->runCommand("%s.enter(%s);",state.c_str(),state.c_str());
				mFSMs.insert(std::make_pair(fsm,state));
			}
		}
		else
		{
			if(it->second != state)
			{
				if(!it->second.empty())
					SCRIPT->runCommand("%s.exit(%s);",it->second.c_str(),it->second.c_str());

				if(!state.empty())
					SCRIPT->runCommand("%s.enter(%s);",state.c_str(),state.c_str());

				it->second = state;
			}
		}
	}

}