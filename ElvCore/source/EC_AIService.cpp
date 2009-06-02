#include "EC_AIService.h"
#include "EC_ParameterSet.h"

namespace ElvCore
{
    AIService::AIService(unsigned int id ,std::string name)
	:	Service(id,name)
    {
    }
    
    AIService::~AIService()
    {

    }

    bool AIService::initialize(ParameterSet*)
    {
        return true;
    }
    
    bool AIService::shutdown()
    {
        return true;
    }
    
    bool AIService::update(float timestep)
    {
        return true;
    }
}

