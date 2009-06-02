#ifndef EC_SERVICE_H
#define EC_SERVICE_H

#include "EC_Common.h"

namespace ElvCore
{
	enum ServiceID
	{
		eGfxService,
		eInputService,
		eGuiService,
		ePhysicService,
		eAudioService,
		eAIService,
		eScriptService,
		eEventService,
		eObjectService,
		eTerrainService,

		eUserService = 100,
	};

	class Service
	{
	public:
		Service(unsigned int id,std::string name) : mID(id),mName(name) {}
		virtual ~Service() {};

		virtual bool initialize(ParameterSet*) = 0;
		virtual bool update(float) = 0;
		virtual bool shutdown() = 0;
		
		std::string name() const { return mName; }
		unsigned int ID()  const { return mID; }

	private:
		unsigned int mID;
		std::string  mName;
	};
}

#endif