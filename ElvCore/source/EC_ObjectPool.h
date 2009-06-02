#ifndef EC_OBJECTPOOL_H
#define EC_OBJECTPOOL_H

#include <list>

namespace ElvCore
{
    template<class T>
    class ObjectPool
    {
    public:
		ObjectPool(int size = 10)
		{
			for(int i=0; i<size; ++i)
			{
				void* p = malloc(sizeof(T));
				RecycleObject(p);			
			}
		}
	 
		~ObjectPool()
		{
			PurgeList();
		}

        void* AllocObject()
		{
			if(!_objectList.empty())
			{
				iter it = _objectList.begin();
				void *p = *it;
				_objectList.pop_front();
				return p;
			}
			else
			{
				void* p = malloc(sizeof(T));
				return p;
			}
		}

        void  RecycleObject(void* p)
		{
			_objectList.push_back(p);
		}

        void  PurgeList()
		{
			for(iter it = _objectList.begin(); it != _objectList.end(); ++it)
			{
				void *p = *it;
				free(p);
			}
			_objectList.clear();
		}

    private:
        typedef std::list<void*> container;
        typedef container::iterator iter;
        container _objectList;
    };
}

#endif