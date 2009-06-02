#include "EC_Core.h"
#include "EC_PhysicService.h"
#include "EC_GuiService.h"
#include "EC_AudioService.h"
#include "EC_AIService.h"
#include "EC_GfxService.h"
#include "EC_InputService.h"
#include "EC_ScriptService.h"
#include "EC_EventService.h"
#include "EC_ObjectService.h"
#include "EC_TerrainService.h"
#include "EC_ParameterSet.h"

namespace ElvCore
{
    Core::Core()
	:	mQuit(false)
    {
    }
    
    Core::~Core()
    {
    }
 
    bool Core::initialize(ParameterSet* var)
    {
		addService<GfxService>(eGfxService,"GfxService");
		addService<InputService>(eInputService,"InputService");
		addService<GuiService>(eGuiService,"GuiService");
		addService<PhysicService>(ePhysicService,"PhysicService");
		addService<AudioService>(eAudioService,"AudioService");
		addService<AIService>(eAIService,"AIService");
		addService<ScriptService>(eScriptService,"ScriptService");
		addService<EventService>(eEventService,"EventService");
		addService<ObjectService>(eObjectService,"ObjectService");
		addService<TerrainService>(eTerrainService,"TerrainService");

		//mServices.push_back(new GfxService);
		//mServices.push_back(new InputService);
		//mServices.push_back(new GuiService);
		//mServices.push_back(new PhysicService);
		//mServices.push_back(new AudioService);
		//mServices.push_back(new AIService);
		//mServices.push_back(new ScriptService);

		for(ServiceVec::iterator it = mServices.begin(); it != mServices.end(); ++it)
		{
			Service* pServ = (*it);

			//DWORD var = 0;
			//if(pServ->name() == "InputService")
			//{
			//	GFX->getRenderWindow()->getCustomAttribute("WINDOW",&var);
			//}

			if(!pServ->initialize(var))
				return false;
		}
      
        return true;
    }
    
    bool Core::shutdown()
    {
		ServiceVec::iterator it = mServices.end();

		while(1)
		{
			--it;

			Service* pServ = (*it);
			pServ->shutdown();		

			if(it == mServices.begin())
				break;
		}
        
        return true;
    }
    
    bool Core::update(float timestep)
    {
		if(mQuit)
			return false;
		
		for(ServiceVec::iterator it = mServices.begin(); it != mServices.end(); ++it)
		{
			Service* pServ = (*it);
			if(!pServ->update(timestep))
				return false;
		}

        return true;
    }

	template<class T>
	Service* Core::addService(unsigned int id,std::string name)
	{
		if(id < mServices.size())
		{
			if(mServices[id] != NULL)
				return NULL;
			else
				mServices[id] = new T(id,name);
		}
		else
		{
			mServices.resize(id+1);
			mServices[id] = new T(id,name);
		}

		return mServices[id];
	}
}