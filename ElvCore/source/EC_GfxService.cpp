#include "EC_GfxService.h"
#include "EC_GuiService.h"
#include "EC_ParameterSet.h"
#include "EC_Core.h"

namespace ElvCore
{
	GfxService::GfxService(unsigned int id,std::string name)
	: Service(id,name)
	, mRoot(NULL)
	, mSceneManager(NULL)
	, mCamera(NULL)
	, mRenderSystem(NULL)
	, mWindow(NULL)
    {
    }
    
    GfxService::~GfxService()
    {
    }

    bool GfxService::initialize(ParameterSet* var)
    {
		Ogre::String plug;

		#ifdef _DEBUG
			plug = "plugins_d.cfg";
		#else
			plug = "plugins.cfg";
		#endif
		
		mRoot = new Ogre::Root(plug,"","ogre.log");

		Ogre::LogManager::getSingleton().getDefaultLog()->setLogDetail(Ogre::LL_LOW);

		// Load resource paths from config file
		Ogre::ConfigFile cf;
		cf.load("resources.cfg");

		// Go through all sections & settings in the file
		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

		Ogre::String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;
			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}

		Ogre::RenderSystemList* renderSystems = mRoot->getAvailableRenderers(); 
		mRenderSystem = *(renderSystems->begin());
		mRoot->setRenderSystem(mRenderSystem);

		mRenderSystem->setConfigOption("Full Screen", "No");
		mRenderSystem->setConfigOption("VSync", "No");

		std::stringstream strVideoMode;
		strVideoMode << 1024 << " x " << 768 << " @ " << 32 << "-bit colour";
		mRenderSystem->setConfigOption("Video Mode", strVideoMode.str());

		mWindow = mRoot->initialise(true, "TankStory");

		mSceneManager = mRoot->createSceneManager(  Ogre::ST_INTERIOR, "scMa" );
		mSceneManager->setAmbientLight( Ogre::ColourValue( 0.5, 0.5, 0.5) );

		mCamera = mSceneManager->createCamera("Camera");
		mCamera->setNearClipDistance(	1.0f );
		mCamera->setFOVy(Ogre::Radian(Ogre::Degree(45)));
		mCamera->setFarClipDistance( 10000.0f );
		mCamera->setPosition(0,100,100);
		mCamera->lookAt(0,0,0);

		Ogre::Viewport* viewport = mWindow->addViewport(mCamera);
		viewport->setBackgroundColour(Ogre::ColourValue(0.3f, 0.3f, 0.3f));
		mCamera->setAspectRatio( Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()) );

		Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(1);
		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8); 

		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

		unsigned long wnd;
		mWindow->getCustomAttribute("WINDOW",&wnd);
		var->AddInt("HWND",wnd);
		var->AddInt("RenderWindow",(unsigned long)mWindow);

		return true;
    }
    
    bool GfxService::shutdown()
    {
		if(mRoot)
		{
			delete mRoot;
			mRoot = NULL;
		}
        return true;
    }
    
    bool GfxService::update(float timestep)
    {
		return true;
    }

	void GfxService::windowClosed(Ogre::RenderWindow* rw)
	{
		if( rw == mWindow )
		{
			CORE->reqQuit();
		}
	}

	void GfxService::windowResized(Ogre::RenderWindow* rw)
	{
		GUI->resizeWindow();
		INPUT->setWindowExtents(rw->getWidth(),rw->getHeight());
	}

}

