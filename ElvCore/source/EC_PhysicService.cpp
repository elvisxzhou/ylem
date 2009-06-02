#include "EC_PhysicService.h"

namespace ElvCore
{


	PhysicService::PhysicService(unsigned int id,std::string name)
	:	Service(id,name)
    {
    }
    
    PhysicService::~PhysicService()
    {
    }

    bool PhysicService::initialize(ParameterSet* var)
    {
        return true;
    }
    
    bool PhysicService::shutdown()
    {
        return true;
    }
    
    bool PhysicService::update(float timestep)
    {
        return true;
    }
}

