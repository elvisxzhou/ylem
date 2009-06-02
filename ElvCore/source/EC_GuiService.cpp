#include "EC_GuiService.h"
#include "EC_Core.h"
#include "EC_ParameterSet.h"

namespace ElvCore
{
	GuiService::GuiService(unsigned int id,std::string name)
	:	Service(id,name)\
	,   m_bEnableKeyboard(true)
	,	m_bEnableMouse(true)
    {
    }
    
    GuiService::~GuiService()
    {
    }

    bool GuiService::initialize(ParameterSet* pParamSet)
    {
		m_pGUI = new MyGUI::Gui();
		m_pRenderWindow = reinterpret_cast<Ogre::RenderWindow*>(pParamSet->GetInt( "RenderWindow"));

		m_pGUI->initialise( m_pRenderWindow, "core.xml", "GUI" );

		MyGUI::IntSize size(120, 80);

		m_pFpsInfoShadow = m_pGUI->createWidget<MyGUI::StaticText>("StaticText", m_pRenderWindow->getWidth() - size.width, m_pRenderWindow->getHeight()-size.height, size.width, size.height, MyGUI::ALIGN_RIGHT | MyGUI::ALIGN_BOTTOM, "Statistic");
		m_pFpsInfoShadow->setTextAlign(MyGUI::ALIGN_CENTER);
		m_pFpsInfoShadow->setColour(Ogre::ColourValue::Black);
		//m_pFpsInfoShadow->hide();

		m_pFpsInfo = m_pGUI->createWidget<MyGUI::StaticText>("StaticText", m_pRenderWindow->getWidth() - size.width-1, m_pRenderWindow->getHeight()-size.height-1, size.width, size.height, MyGUI::ALIGN_RIGHT | MyGUI::ALIGN_BOTTOM, "Statistic");
		m_pFpsInfo->setTextAlign(MyGUI::ALIGN_CENTER);
		m_pFpsInfo->setColour(Ogre::ColourValue::White);
		//m_pFpsInfo->hide();

		::ShowCursor( FALSE );

		INPUT->addInputCallBack( this );

        return true;
    }
    
    bool GuiService::shutdown()
    {
		INPUT->removeInputCallBack(this);

		if ( m_pGUI ) 
		{
			if ( m_pFpsInfo ) 
			{
				m_pGUI->destroyChildWidget( m_pFpsInfo );
				m_pFpsInfo = NULL;
			}

			if ( m_pFpsInfoShadow )
			{
				m_pGUI->destroyChildWidget( m_pFpsInfoShadow );
				m_pFpsInfoShadow = NULL;
			}

			m_pGUI->shutdown();
			delete m_pGUI;
			m_pGUI = NULL;
		}
		return true;
    }
    
    bool GuiService::update(float timestep)
    {
		m_pGUI->injectFrameEntered(timestep);
        return true;
    }

	MyGUI::VectorWidgetPtr GuiService::loadLayout( const std::string& strFile,const std::string& strPrefix )
	{
		mWidgets = MyGUI::LayoutManager::getInstance().loadLayout(strFile, strPrefix, NULL,"GUI");

		//for (MyGUI::VectorWidgetPtr::iterator iter = mWidgets.begin(); iter!=mWidgets.end(); ++iter) 
		//{
		//	MyGUI::WidgetPtr pWidget = (*iter);
		//	_connect2Script(pWidget);
		//}

		return mWidgets;
	}

	void GuiService::unloadLayout(MyGUI::VectorWidgetPtr & _widgets)
	{
		MyGUI::WidgetManager::getInstance().destroyWidgetsVector(_widgets);
	}

	void GuiService::showPointer( bool bShow /* = true */ )
	{
		if( bShow )
		{
			m_pGUI->showPointer();
		}
		else
		{
			m_pGUI->hidePointer();
		}
	}

	bool GuiService::isShowPointer( void )
	{
		return m_pGUI->isShowPointer();
	}

	void GuiService::showFPS( bool bShow /* = true */ )
	{
		if( bShow )
		{
			m_pFpsInfo->show();
			m_pFpsInfoShadow->show();		
		}
		else
		{
			m_pFpsInfo->hide();
			m_pFpsInfoShadow->hide();
		}
	}

	bool GuiService::isShowFPS( void )
	{
		return m_pFpsInfo->isShow();
	}

	void GuiService::enableMouse( bool bEnable /* = true */ )
	{
		m_bEnableMouse = bEnable;
	}

	bool GuiService::isEnableMouse( void )
	{
		return m_bEnableMouse;
	}

	void GuiService::enableKeyboard( bool bEnable /* = true */ )
	{
		m_bEnableKeyboard = bEnable;
	}

	bool GuiService::isEnableKeyboard( void )
	{
		return m_bEnableKeyboard;
	}

	void GuiService::injectChar( MyGUI::Char _char )
	{
		m_pGUI->injectChar(_char);
	}

	void GuiService::setFocus( MyGUI::WidgetPtr widget)
	{
		MyGUI::InputManager::getInstancePtr()->setKeyFocusWidget( widget );
	}

	void GuiService::resizeWindow()
	{
		m_pGUI->windowResized( m_pRenderWindow );
	}

	bool GuiService::keyPressed( const OIS::KeyEvent &arg )
	{
		if( m_bEnableKeyboard )
		{
			m_pGUI->injectKeyPress( arg );
		}

		return true;
	}

	bool GuiService::keyReleased( const OIS::KeyEvent &arg )
	{
		if( m_bEnableKeyboard )
		{
			m_pGUI->injectKeyRelease( arg );
		}

		return true;
	}

	bool GuiService::mouseMoved( const OIS::MouseEvent &arg )
	{
		if( m_bEnableMouse )
		{
			m_pGUI->injectMouseMove( arg );
		}

		return true;
	}

	bool GuiService::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		if( m_bEnableMouse )
		{
			m_pGUI->injectMousePress( arg, id );
		}

		return true;
	}

	bool GuiService::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
	{
		if( m_bEnableMouse )
		{
			m_pGUI->injectMouseRelease( arg, id );
		}

		return true;
	}

}

