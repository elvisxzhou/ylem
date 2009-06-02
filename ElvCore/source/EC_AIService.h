#ifndef EC_AIService_H
#define EC_AIService_H

#include "EC_Service.h"

namespace ElvCore
{
    class AIService : public Service
    {
    public:
        AIService(unsigned int ,std::string);
        ~AIService();

        bool initialize(ParameterSet*);
        bool shutdown();
        
        bool update(float timestep);    
    };
}


#endif
