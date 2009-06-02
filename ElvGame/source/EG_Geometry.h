#ifndef EG_GEOMETRY_H
#define EG_GEOMETRY_H

#include "ElvCore.h"

namespace ElvGame
{
	typedef std::map<Ogre::String,Ogre::SceneNode*> SceneNodeMap;
	typedef Ogre::MapIterator< SceneNodeMap > SceneNodeMapIterator;

	class Geometry;

	class GeometryDesc
	{
	public:
		Ogre::String name;
		Ogre::String parent;
		Ogre::Vector3 position;
		Ogre::Vector3 scale;
		Ogre::Quaternion rotation;

		void from(Ogre::SceneNode* pNode)
		{
			name = pNode->getName();
			parent = pNode->getParentSceneNode()->getName();
			position = pNode->getPosition();
			scale = pNode->getScale();
			rotation = pNode->getOrientation();
		}

	private:
		friend class boost::serialization::access;

		template<class Archive>
		void serialize(Archive & ar_, const unsigned int version_)
		{
			ar_ & BOOST_SERIALIZATION_NVP(name);
			ar_ & BOOST_SERIALIZATION_NVP(parent);
			ar_ & BOOST_SERIALIZATION_NVP(position.x);
			ar_ & BOOST_SERIALIZATION_NVP(position.y);
			ar_ & BOOST_SERIALIZATION_NVP(position.z);
			ar_ & BOOST_SERIALIZATION_NVP(scale.x);
			ar_ & BOOST_SERIALIZATION_NVP(scale.y);
			ar_ & BOOST_SERIALIZATION_NVP(scale.z);
			ar_ & BOOST_SERIALIZATION_NVP(rotation.w);
			ar_ & BOOST_SERIALIZATION_NVP(rotation.x);
			ar_ & BOOST_SERIALIZATION_NVP(rotation.y);
			ar_ & BOOST_SERIALIZATION_NVP(rotation.z);
		}
	};

	BOOST_CLASS_EXPORT_GUID(GeometryDesc, "ElvGameGeometryDesc")

	class Geometry : public ElvCore::Component
	{
	public:
		Geometry();
		~Geometry();

		bool update(float timestep);

		Ogre::SceneNode* addSceneNode(Ogre::String name,Ogre::String parent,bool bAddPrefix = false);
		void removeSceneNode(Ogre::SceneNode* pNode);
		void removeSceneNode(Ogre::String node);

		SceneNodeMapIterator getSceneNodes();
		Ogre::SceneNode* getSceneNode(Ogre::String node);

	private:
		std::string getType() { return "Geometry"; }
		void _init(GeometryDesc* pDesc);

	private:
		SceneNodeMap mSceneNodes;

		friend class boost::serialization::access;

		template<class Archive>
		void save(Archive & ar_, const unsigned int version_) const
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);

			size_t sz = mSceneNodes.size();
			ar_ & BOOST_SERIALIZATION_NVP(sz);

			GeometryDesc desc;

			for(SceneNodeMap::const_iterator it = mSceneNodes.begin(); it != mSceneNodes.end(); ++it)
			{
				Ogre::SceneNode* pNode = it->second;
				desc.from(pNode);
				ar_ & BOOST_SERIALIZATION_NVP(desc);
			}
		}

		template<class Archive>
		void load(Archive & ar_, const unsigned int version_)
		{
			ar_ & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ElvCore::Component);

			size_t sz = 0;
			ar_ & BOOST_SERIALIZATION_NVP(sz);

			GeometryDesc desc;

			for(size_t i = 0; i<sz; ++i)
			{				
				ar_ & BOOST_SERIALIZATION_NVP(desc);
				_init(&desc);
			}
		}    

		BOOST_SERIALIZATION_SPLIT_MEMBER()
	};

	BOOST_CLASS_EXPORT_GUID(Geometry, "ElvGameGeometry")

}
#endif