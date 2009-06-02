#ifndef EC_AudioService_H
#define EC_AudioService_H

#include "EC_Service.h"

namespace ElvCore
{
    class AudioService : public Service
    {
    public:
        AudioService(unsigned int ,std::string);
        ~AudioService();

        bool initialize(ParameterSet*);
        bool shutdown();
        
        bool update(float timestep);    
    };
}


#endif
