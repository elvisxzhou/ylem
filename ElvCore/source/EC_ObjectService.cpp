#include "EC_ObjectService.h"
#include "EC_Object.h"
#include "EC_Component.h"

namespace ElvCore
{
    ObjectService::ObjectService(unsigned int id ,std::string name)
	:	Service(id,name)
    {
    }
    
    ObjectService::~ObjectService()
    {

    }

    bool ObjectService::initialize(ParameterSet*)
    {
        return true;
    }
    
    bool ObjectService::shutdown()
    {
		for(ObjectMap::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
		{
			Object* pObj = it->second;

			delete pObj;
		}

		mObjects.clear();

		return true;
    }
    
    bool ObjectService::update(float timestep)
    {
		for(ObjectMap::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
		{
			Object* pObj = it->second;

			if(!pObj->update(timestep))
				return false;
		}

        return true;
    }

	Object* ObjectService::createObject(std::string name,bool bLoadPredefined/* = false*/)
	{
		ObjectMap::iterator it = mObjects.find(name);
		if(it == mObjects.end())
		{
			Object* pObj;
			if(bLoadPredefined)
			{
				Deserialise serialise(name);
				serialise.in(pObj);
			}
			else
			{
				pObj = new Object(name);
			}

			mObjects.insert(std::make_pair(name,pObj));
			
			return pObj;
		}
		else
		{
			return it->second;
		}
	}

	void ObjectService::saveObject(const Object* pObj,std::string file) const
	{
		std::string name = pObj->ID();
		if(file.empty())
		{
			Serialise serialise(name);
			serialise.out(pObj);
		}
		else
		{
			Serialise serialise(file);
			serialise.out(pObj);
		}
	}
}

