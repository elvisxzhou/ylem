#ifndef EG_GRAPHICS_H
#define EG_GRAPHICS_H

#include "ElvCore.h"

namespace ElvGame
{
	typedef std::map<Ogre::String,Ogre::Entity*> EntityMap;
	typedef Ogre::MapIterator< EntityMap > EntityMapIterator;

	class Graphics;

	class GraphicsDesc
	{
	public:
		Ogre::String name;
		Ogre::String mesh;
		Ogre::String parent;
		Ogre::String material;

		void fromEntity(Ogre::Entity* pEntity)
		{
			name = pEntity->getName();
			mesh = pEntity->getMesh()->getName();
			parent=pEntity->getParentSceneNode()->getName();
			material=pEntity->getSubEntity(0)->getMaterialName();
		}

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar_, const unsigned int version_)
		{
			ar_ & BOOST_SERIALIZATION_NVP(name);
			ar_ & BOOST_SERIALIZATION_NVP(mesh);
			ar_ & BOOST_SERIALIZATION_NVP(parent);
			ar_ & BOOST_SERIALIZATION_NVP(material);
		}
	};

	BOOST_CLASS_EXPORT_GUID(GraphicsDesc, "ElvGameGraphicsDesc")

	class Graphics : public ElvCore::Component
	{
	public:
		Graphics();
		~Graphics();

		bool update(float timestep);

		Ogre::Entity* addEntity(Ogre::String name,Ogre::String mesh,Ogre::String parent,bool bAddPrefix = false);
		void removeEntity(Ogre::Entity* entity);
		void removeEntity(Ogre::String entity);
		EntityMapIterator getEntities();
		Ogre::Entity* getEntity(Ogre::String entity);

	private:
		std::string getType() { return "Graphics"; }
		void _init(GraphicsDesc*);

	private:
		EntityMap mEntities;
		
		friend class boost::serialization::access;

		template<class Archive>
		void save(Archive & ar_, const unsigned int version_) const
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);
			
			size_t sz = mEntities.size();
			ar_ & BOOST_SERIALIZATION_NVP(sz);

			GraphicsDesc desc;

			for(EntityMap::const_iterator it = mEntities.begin(); it != mEntities.end(); ++it)
			{
				Ogre::Entity* pEntity = it->second;
				
				desc.fromEntity(pEntity);
				ar_ & BOOST_SERIALIZATION_NVP(desc);
			}
		}

		template<class Archive>
		void load(Archive & ar_, const unsigned int version_)
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);

			size_t sz = 0;
			ar_ & BOOST_SERIALIZATION_NVP(sz);

			GraphicsDesc desc;
			for(size_t i = 0; i<sz; ++i)
			{
				ar_ & BOOST_SERIALIZATION_NVP(desc);
				_init(&desc);
			}
		}    

        BOOST_SERIALIZATION_SPLIT_MEMBER()
	};

	BOOST_CLASS_EXPORT_GUID(Graphics, "ElvGameGraphics")

}
#endif