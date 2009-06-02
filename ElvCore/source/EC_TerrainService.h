#ifndef EC_TERRAINSERVICE_H
#define EC_TERRAINSERVICE_H

#include "EC_Service.h"


namespace ElvCore
{
    class TerrainService : public Service
    {
    public:
        TerrainService(unsigned int ,std::string);
        ~TerrainService();

        bool initialize(ParameterSet*);
        bool shutdown();
        
        bool update(float timestep);    
    };
}


#endif
