#ifndef EC_GfxService_H
#define EC_GfxService_H

#include "EC_Service.h"


namespace ElvCore
{
	class GfxService : public Ogre::WindowEventListener,public Service
    {
    public:
		GfxService(unsigned int id,std::string name);
        ~GfxService();

        bool initialize(ParameterSet*);
        bool shutdown();
        
        bool update(float timestep);

		Ogre::RenderWindow* getRenderWindow() const { return mWindow; }
		Ogre::SceneManager* getSceneManager() const { return mSceneManager; }
		Ogre::Camera*       getCamera()       const { return mCamera; }
	private:
		void windowClosed(Ogre::RenderWindow* rw);
		void windowResized(Ogre::RenderWindow* rw);
		
		Ogre::Root* mRoot;
		Ogre::SceneManager* mSceneManager;
		Ogre::Camera* mCamera;
		Ogre::RenderSystem* mRenderSystem;
		Ogre::RenderWindow* mWindow;
	};
}


#endif
