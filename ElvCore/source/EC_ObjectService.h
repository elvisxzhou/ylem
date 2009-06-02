#ifndef EC_ObjectService_H
#define EC_ObjectService_H

#include "EC_Service.h"


namespace ElvCore
{
    class ObjectService : public Service
    {
    public:
        ObjectService(unsigned int ,std::string);
        ~ObjectService();

        bool initialize(ParameterSet*);
        bool shutdown();
        
        bool update(float timestep);

		Object* createObject(std::string name,bool bLoadPredefined = false);
		void    saveObject(const Object*,std::string file="") const;

	private:
		typedef std::map<std::string,Object*> ObjectMap;
		ObjectMap mObjects;
    };
}


#endif
