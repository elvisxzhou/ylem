#include "EC_Object.h"
#include "EC_Component.h"
#include "EC_ListNode.h"
#include "EC_ObjectPool.h"

namespace ElvCore
{
//	ObjectPool<Object> Object::_pool;
	
	Object::Object(Object::ObjectID id)
    : _components(NULL) 
	, _id(id)
    { 
    }
    
    Object::~Object()
    {
        Component* c = _components;
        while(c)
        {
            Component* d = c;
            c = (Component*)c->next;
            removeComponent(d);
        }
    }

    bool Object::update(float timestep_)
    {
        Component * c = _components;
        while(c)
        {
            if(c->isEnabled())
            {
                if(!c->update(timestep_))
                    return false;
            }
            c=(Component*)c->next;
        }

        return true;
    }
    void Object::disable(std::string type)
    {
        Component * c = getComponent(type);
        if(c){ c->disable(); }
    }

    void Object::enable(std::string type)
    {
        Component * c = getComponent(type);
        if(c){ c->enable(); }
    }

    Component* Object::getComponent(std::string type)
    {
        Component* c = _components;
        while(c)
        {
            if(c->getType() == type)
                return c;

            c = (Component*)c->next;
        }

        return NULL;
    }

    void Object::addComponent(Component* c)
    {
        if(0 != c)
        {
            if(_components == NULL)
                _components = c;
            else
                c->insert((ListNode*)_components);
            c->owner(this);	
            c->onAttach();
        }
    }

    void Object::removeComponent(Component * c)
    {
        if(c)
        {
            if(c == _components)
                _components = (Component*)c->next;

            c->detach();
            c->onRemove();
            c->owner(0);
            delete c;
            c = NULL;
        }
    }

    //void* Object::operator new (size_t size)
    //{
    //    return _pool.AllocObject();
    //}

    //void* Object::operator new (size_t size,int)
    //{
    //    return _pool.AllocObject();
    //}

    //void Object::operator delete(void* p)
    //{
    //    _pool.RecycleObject(p);
    //}
}