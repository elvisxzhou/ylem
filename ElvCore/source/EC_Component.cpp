#include "EC_Component.h"
#include "EC_Object.h"

namespace ElvCore
{
	Component::Component(void) 
	: _owner(0), _enabled(true)
	{
	}		

 //   ObjectPool<Component> Component::_pool;

//	  void* Component::operator new (size_t size)
 //   {
 //       return _pool.AllocObject();
 //   }

 //   void Component::operator delete(void* p)
 //   {
 //       _pool.RecycleObject(p);
 //   }

	//template<class Archive>
 //   void Component::serialize(Archive & ar_, const unsigned int version_)
 //   {
 //       ar_ & BOOST_SERIALIZATION_NVP(_enabled);
 //   }
}