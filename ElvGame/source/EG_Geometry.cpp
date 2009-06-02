#include "EG_Geometry.h"

namespace ElvGame
{
	Geometry::Geometry()
	{
	}

	Geometry::~Geometry()
	{
	}

	bool Geometry::update(float timestep)
	{
		return true;
	}

	Ogre::SceneNode* Geometry::addSceneNode(Ogre::String name,Ogre::String parent,bool bAddPrefix)
	{
		Ogre::SceneManager* pSceneMgr = GFX->getSceneManager();

		Ogre::SceneNode *pNode = 0;
		Ogre::SceneNode *pParent = 0;

		Ogre::String strName = name;
		Ogre::String strParent = parent;
		
		if(bAddPrefix)
		{
			strName = owner()->ID() + strName;
			strParent = owner()->ID() + strParent;
		}

		if(parent == "WorldRootNode")
			pParent = pSceneMgr->getRootSceneNode();
		else
		{
			try {
				pParent = pSceneMgr->getSceneNode(strParent);			
			} 
			catch(...){	
				pParent = pSceneMgr->getRootSceneNode()->createChildSceneNode(strParent);
			}
		}

		try { 
			pNode = pSceneMgr->getSceneNode(strName);

			Ogre::SceneNode *pOldParent=pNode->getParentSceneNode();
			pOldParent->removeChild(pNode);
			pParent->addChild(pNode);
		} 
		catch(...){
			pNode = pParent->createChildSceneNode(strName);
		}

		mSceneNodes.insert(std::make_pair(strName,pNode));

		return pNode;
	}

	void Geometry::removeSceneNode(Ogre::SceneNode* pNode)
	{
	}

	void Geometry::removeSceneNode(Ogre::String node)
	{
	}

	SceneNodeMapIterator Geometry::getSceneNodes()
	{
		return SceneNodeMapIterator(mSceneNodes.begin(),mSceneNodes.end());
	}

	Ogre::SceneNode* Geometry::getSceneNode(Ogre::String node)
	{
		SceneNodeMap::iterator it = mSceneNodes.find(node);
		if(it == mSceneNodes.end())
			return NULL;
		else
			return it->second;
	}

	void Geometry::_init(GeometryDesc* pDesc)
	{
		Ogre::SceneNode* pNode = addSceneNode(pDesc->name,pDesc->parent);
		if(!pNode) return;
	
		pNode->setPosition(pDesc->position);
		pNode->setScale(pDesc->scale);
		pNode->setOrientation(pDesc->rotation);
	}
}