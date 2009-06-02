#ifndef EC_PhysicService_H
#define EC_PhysicService_H

#include "EC_Service.h"


namespace ElvCore
{
	class PhysicService : public Service

    {
    public:
        PhysicService(unsigned int id,std::string name);
        ~PhysicService();

        bool initialize(ParameterSet*);
        bool shutdown();
        
        bool update(float timestep);

	private:
    };
}


#endif
