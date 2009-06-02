#ifndef EC_Object_H
#define EC_Object_H

#include "EC_Common.h"
#include "EC_Serialisation.h"

namespace ElvCore
{
	class Object
    {
	public:
		typedef std::string ObjectID;
		Object(ObjectID id);
        ~Object();
		
		ObjectID ID() const { return _id; }

        bool update(float timestep_);
       
        void disable(std::string type);
        void enable(std::string type);
        
        Component* getComponent(std::string type);
        void addComponent(Component* c);
        void removeComponent(Component * component_);
        
//		static void* operator new (size_t size);
//		static void* operator new(size_t size, int);
//		static void operator delete(void* p);
//	private:
//		static ObjectPool<Object> _pool;

	private:
        friend class boost::serialization::access;
		ObjectID _id;
        Component* _components;

		template<class Archive>
		void save(Archive & ar_, const unsigned int version_) const
		{
			int size = ListNode::length(_components);

			ar_  & BOOST_SERIALIZATION_NVP(_id);
			ar_ & BOOST_SERIALIZATION_NVP(size);

			Component* c = _components;
			while(c)
			{
				ar_ & BOOST_SERIALIZATION_NVP(c);
				c = (Component*)c->next;
			}
		}

		template<class Archive>
		void load(Archive & ar_, const unsigned int version_)
		{
			std::set<Component *> loadedComponents;
			std::set<Component *>::size_type loadedComponentsCount = 0;

			Component * c = 0;
			int size = 0;

			ar_  & BOOST_SERIALIZATION_NVP(_id);
			ar_ & BOOST_SERIALIZATION_NVP(size);

			for (int i = 0; i < size; ++i)
			{
				ar_ & BOOST_SERIALIZATION_NVP(c);
	            
				loadedComponentsCount = loadedComponents.size();
				loadedComponents.insert(c);				
	            
				if(loadedComponentsCount < loadedComponents.size())
				{
					addComponent(c);
				}
			}
		}    

        BOOST_SERIALIZATION_SPLIT_MEMBER()
    };

	BOOST_CLASS_EXPORT_GUID(Object, "ElvCoreObject")
}

namespace boost 
{ 
	namespace serialization 
	{
		template<class Archive>
		inline void save_construct_data(Archive & ar, const ElvCore::Object * t, const unsigned int file_version)
		{
			ar << t->ID();
		}

		template<class Archive>
		inline void load_construct_data(Archive & ar, ElvCore::Object * t, const unsigned int file_version)
		{
				// retrieve data from archive required to construct new instance
			std::string id;
			ar >> id;
				// invoke inplace constructor to initialize instance of my_class
			::new(t)ElvCore::Object(id);
		}
	}
}

#endif