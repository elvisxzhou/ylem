#include "EG_Application.h"

namespace ElvGame
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	bool Application::initialize()
	{
		new ElvCore::Core;

		ElvCore::ParameterSet* var = ElvCore::ParameterSet::GetNewParameterSet();
		var->ConvertToTable();

		CORE->initialize(var);

		Ogre::Root::getSingleton().addFrameListener(this);
		
		ElvCore::ParameterSet::FreeParameterSet(var);

		onInitialize();

		return true;
	}

	bool Application::run()
	{
		MSG  msg;
		
		while(1)
		{
			if(PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ))
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
				
				if(msg.message == WM_CHAR)
				{
	//				GetGuiManager().injectChar(msg.wParam);
				}
			}

			Ogre::Root::getSingleton().renderOneFrame();

			Sleep(0);
		}
		
		return true;
	}

	bool Application::shutdown()
	{
		onShutdown();

		CORE->shutdown();

		delete CORE;

		return true;
	}

	bool Application::frameEnded(const Ogre::FrameEvent& evt)
	{
		CORE->update( evt.timeSinceLastFrame );

		onUpdate( evt.timeSinceLastFrame );

		return true;
	}
}