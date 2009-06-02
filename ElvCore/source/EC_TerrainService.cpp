#include "EC_TerrainService.h"

namespace ElvCore
{
    TerrainService::TerrainService(unsigned int id ,std::string name)
	:	Service(id,name)
    {
    }
    
    TerrainService::~TerrainService()
    {

    }

    bool TerrainService::initialize(ParameterSet*)
    {
        return true;
    }
    
    bool TerrainService::shutdown()
    {
        return true;
    }
    
    bool TerrainService::update(float timestep)
    {
        return true;
    }
}

