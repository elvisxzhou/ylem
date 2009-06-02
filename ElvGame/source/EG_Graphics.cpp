#include "EG_Graphics.h"

namespace ElvGame
{
	Graphics::Graphics()
	{
	}
	
	Graphics::~Graphics()
	{
	}
	
	bool Graphics::update(float timestep)
	{
		return true;
	}

	Ogre::Entity* Graphics::addEntity(Ogre::String name,Ogre::String mesh,Ogre::String parent,bool bAddPrefix)
	{
		Ogre::SceneManager* pSceneMgr = GFX->getSceneManager();
		try 
		{
			Ogre::String strName = name;
			Ogre::String strParent = parent;

			if(bAddPrefix)
			{
				strName = owner()->ID() + strName;
				strParent = owner()->ID() + strParent;
			}

			Ogre::Entity* pEntity = pSceneMgr->createEntity(strName,mesh);
			Ogre::SceneNode* pNode = pSceneMgr->getSceneNode(strParent);
			pNode->attachObject(pEntity);

			EntityMap::_Pairib ret = mEntities.insert(std::make_pair(strName,pEntity));
			if(ret.second)
				return pEntity;
			else
				return NULL;
		}
		catch(...)
		{
		}
		
		return NULL;
	}

	void Graphics::removeEntity(Ogre::Entity* entity)
	{
	}

	void Graphics::removeEntity(Ogre::String entity)
	{
	}

	EntityMapIterator Graphics::getEntities()
	{
		return EntityMapIterator(mEntities.begin(),mEntities.end());
	}

	Ogre::Entity* Graphics::getEntity(Ogre::String entity)
	{
		EntityMap::iterator it = mEntities.find(entity);
		if(it == mEntities.end())
			return NULL;
		else
			return it->second;
	}


	void Graphics::_init(GraphicsDesc* pDesc)
	{
		Ogre::Entity* pEntity = addEntity(pDesc->name,pDesc->mesh,pDesc->parent);
		if(!pEntity) return;

		pEntity->getSubEntity(0)->setMaterialName(pDesc->material);
	}

}