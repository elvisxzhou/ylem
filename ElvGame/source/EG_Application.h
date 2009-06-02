#ifndef EG_APPLICATION_H
#define EG_APPLICATION_H

#include "ElvCore.h"

namespace ElvGame
{
	class Application : private Ogre::FrameListener
	{
	public:
		Application();
		virtual ~Application();

		bool initialize();
		bool shutdown();
		bool run();

	protected:
		virtual bool onInitialize() { return true; }
		virtual bool onShutdown() { return true; }
		virtual bool onUpdate( float timeStep ) { return true; }

		virtual bool frameStarted(const Ogre::FrameEvent& evt) { return true; };
		virtual bool frameEnded(const Ogre::FrameEvent& evt);

	};
}

#endif