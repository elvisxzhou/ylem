#ifndef EC_COMPONENT_H
#define EC_COMPONENT_H

#include "EC_Common.h"
#include "EC_ListNode.h"
#include "EC_Serialisation.h"

namespace ElvCore
{
    class Component : public ListNode
    {
    public:
        Component(void);
		virtual ~Component(void){};
        virtual std::string getType() = 0;

        virtual bool update(float timestep_) { return true; }
        virtual void owner(Object * owner_){ _owner = owner_; }
        Object * owner(void) const { return _owner; }
        bool isEnabled(void) const { return _enabled; }
        void enable(void){ _enabled = true; onEnable(); }
        void disable(void){ _enabled = false; onDisable(); }
    
	//	void* operator new (size_t size);
	//	void operator delete(void* p);
	//private:
	//	static ObjectPool<Component> _pool;

    protected:
        friend class Object;
        virtual void onAttach(void){}
        virtual void onRemove(void){}
        virtual void onEnable(void){}
        virtual void onDisable(void){}

    private:
        friend class boost::serialization::access;

        Object * _owner;
        bool _enabled;

        template<class Archive>
        void serialize(Archive & ar_, const unsigned int version_)
		{
			ar_ & BOOST_SERIALIZATION_NVP(_enabled);
		}
    };
    
    BOOST_CLASS_EXPORT_GUID(Component, "ElvCoreComponent")
}

#endif