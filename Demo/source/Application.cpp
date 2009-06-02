#include "GAME_PCH.h"

#include "Application.h"
#include "FreeCamera.h"

App::App()
{
}

App::~App()
{
}

bool App::onInitialize()
{
	{	
		Ogre::SceneNode* pNode = GFX->getSceneManager()->getRootSceneNode()->createChildSceneNode("GridPlaneNode");


		Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create("GridMatOrtho", 
			Ogre::ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME);
		Ogre::Pass* pass = mat->getTechnique(0)->getPass(0);
		Ogre::TextureUnitState* t = pass->createTextureUnitState("grid.png");
		pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
		pass->setDepthWriteEnabled(false);
		pass->setCullingMode(Ogre::CULL_NONE);
		pass->setPolygonModeOverrideable(false);
		mat->load();
		mat = mat->clone("GridMatPersp");
		t = mat->getTechnique(0)->getPass(0)->getTextureUnitState(0);
		t->setTextureFiltering(Ogre::TFO_ANISOTROPIC);
		t->setTextureAnisotropy(8);


		Ogre::ManualObject* mPlane = GFX->getSceneManager()->createManualObject("GridPlane");

		float uvDim = 100;

		mPlane->begin("GridMatPersp");

		mPlane->position(-1000,0, -1000);
		mPlane->textureCoord(0, uvDim);
		mPlane->position(1000, 0, -1000);
		mPlane->textureCoord(uvDim, uvDim);
		mPlane->position(1000, 0, 1000);
		mPlane->textureCoord(uvDim, 0);
		mPlane->position(-1000,0 , 1000);
		mPlane->textureCoord(0, 0);
		mPlane->quad(0, 1, 2, 3);
		mPlane->end();

		pNode->attachObject(mPlane);
	}

	//		SCRIPT->runFile("root.lua");

	ElvCore::Object* pObj=NULL;
	/*/
	OBJ->createObject("tank",true);
	/*/
	pObj = OBJ->createObject("tank");//new ElvCore::Object(ElvCore::Object::ObjectID("tank"));

	ElvGame::Geometry* pGeo = new ElvGame::Geometry;
	ElvGame::Graphics* pGfx = new ElvGame::Graphics;
	FreeCamera* pCam = new FreeCamera;
	ElvGame::FSM* pFSM = new ElvGame::FSM;

	ElvGame::VisualEffect* pVE = new ElvGame::VisualEffect("autorotate");
	pVE->setPosition(Ogre::Vector3(100,0,0));

	ElvGame::VisualEffectElement* pVEE = pVE->addMeshElement("VE_Plane.mesh");
	pVEE->setTexture("ray039.dds");

	pVEE = pVE->addMeshElement("VE_Plane.mesh");
	pVEE->setTexture("ray039.dds");

	pVEE->setPosition(Ogre::Vector3(100,0,0));
	pVEE->addAffector(ElvGame::AT_SCALING);
	ElvGame::RibbonTrailElement* pRte = (ElvGame::RibbonTrailElement*)pVE->addRibbonTrailElement(100,1000,"LightRibbonTrail");
	Ogre::RibbonTrail* rt = pRte->getRibbonTrail();
	rt->setInitialColour(0,1,0,0);
	rt->setColourChange(0,2,0,0,2);
	rt->setInitialWidth(0,20);
	rt->setWidthChange(0,10);

	//		std::vector<Ogre::String> names;
	//		ParticleUniverse::ParticleSystemManager::getSingletonPtr()->particleSystemTemplateNames(names);

	//		ParticleUniverse::ParticleSystem* pSys = pVEE->addParticleSystem(names[4]);

	//		pSys->start();

	{
		ElvGame::TranslateAffector* af =(ElvGame::TranslateAffector*) pVEE->addAffector(ElvGame::AT_TRANSLATE);
		af->setVelocity(3);
		af->setAccelaration(1);
		af->setTime(15.0f);
	}
	{

		ElvGame::SelfRotateAffector* af =(ElvGame::SelfRotateAffector*) pVEE->addAffector(ElvGame::AT_SELFROTATE);
		af->setAxis(Ogre::Vector3(0,1,0));
		af->setSpeed(Ogre::Degree(120.0f));
	}
	{

		ElvGame::PublicRotateAffector* af1 =(ElvGame::PublicRotateAffector*) pVEE->addAffector(ElvGame::AT_PUBLICROTATE);
		af1->setAxis(Ogre::Vector3(0,1,0));
		af1->setSpeed(Ogre::Degree(60.0f));
		af1->setTransformSpace(Ogre::Node::TS_PARENT);
	}
	{

		pVEE->addAffector(ElvGame::AT_COLORFADE);
		pVEE->addAffector(ElvGame::AT_RANDOMCOLOR);
	}

	pObj->addComponent(pGeo);
	pObj->addComponent(pGfx);
	pObj->addComponent(pCam);
	//		pObj->addComponent(pFSM);
	pObj->addComponent(pVE);

	//Ogre::SceneNode* pNode = pGeo->addSceneNode("root","WorldRootNode");
	//pNode->setPosition(Ogre::Vector3(0,0,0));
	//pGfx->addEntity("ninja","ninja.mesh","root");

	//*/

//	OBJ->saveObject(pObj,"tank");

	return true;
}

bool App::onShutdown()
{
	return true;
}
