#include "EC_AudioService.h"
#include "EC_ParameterSet.h"

namespace ElvCore
{
    AudioService::AudioService(unsigned int id ,std::string name)
	:	Service(id,name)
    {
    }
    
    AudioService::~AudioService()
    {
    }

    bool AudioService::initialize(ParameterSet*)
    {
        return true;
    }
    
    bool AudioService::shutdown()
    {
        return true;
    }
    
    bool AudioService::update(float timestep)
    {
        return true;
    }
}

