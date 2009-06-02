#include "GAME_PCH.h"
#include "FreeCamera.h"

FreeCamera::FreeCamera() 
: mCamera(NULL)
, mRotateSpeed(0.01)
, mMoveSpeed(1)
{
	mCamera = GFX->getCamera();
	mSceneNode = GFX->getSceneManager()->getRootSceneNode()->createChildSceneNode("FreeCameraNode");
	mSceneNode->attachObject(mCamera);

	INPUT->addInputCallBack(this);
}

FreeCamera::~FreeCamera() 
{
	GFX->getSceneManager()->destroySceneNode(mSceneNode);
}

bool FreeCamera::update(float timestep)
{
	if(INPUT->isKeyDown(OIS::KC_W))
		mCamera->setPosition(mCamera->getPosition() - mCamera->getOrientation() * Ogre::Vector3::UNIT_Z);
	if(INPUT->isKeyDown(OIS::KC_A))
		mCamera->setPosition(mCamera->getPosition() - mCamera->getOrientation() * Ogre::Vector3::UNIT_X);
	if(INPUT->isKeyDown(OIS::KC_S))
		mCamera->setPosition(mCamera->getPosition() + mCamera->getOrientation() * Ogre::Vector3::UNIT_Z);
	if(INPUT->isKeyDown(OIS::KC_D))
		mCamera->setPosition(mCamera->getPosition() + mCamera->getOrientation() * Ogre::Vector3::UNIT_X);
	return true;
}

void FreeCamera::onAttach(void)
{
}

bool FreeCamera::mouseMoved(const OIS::MouseEvent & arg)
{
	if(arg.state.buttonDown(OIS::MB_Right))
	{
		Ogre::Vector3 up = mCamera->getOrientation()*mCamera->getDerivedOrientation().Inverse()*Ogre::Vector3::UNIT_Y;
		Ogre::Vector3 right = mCamera->getDerivedRight();
		mCamera->rotate(up,Ogre::Radian(arg.state.X.rel*-mRotateSpeed));
		mCamera->pitch(Ogre::Radian(arg.state.Y.rel*-mRotateSpeed));
	}
	else if(arg.state.buttonDown(OIS::MB_Left))
	{
		Ogre::Vector3 up = mCamera->getDerivedUp();
		Ogre::Vector3 right = mCamera->getDerivedRight();
		mSceneNode->yaw(Ogre::Radian(arg.state.X.rel*-mRotateSpeed),Ogre::Node::TS_WORLD);
		mSceneNode->rotate(right,Ogre::Radian(arg.state.Y.rel*-mRotateSpeed),Ogre::Node::TS_WORLD);
	}

	return false;
}