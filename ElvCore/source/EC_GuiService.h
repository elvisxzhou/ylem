#ifndef EC_GuiService_H
#define EC_GuiService_H


#include "EC_Service.h"

#include "EC_InputService.h"

namespace ElvCore
{
	class GuiService : public Service , public InputCallback
    {
    public:
		GuiService(unsigned int ,std::string);
        ~GuiService();

        bool initialize(ParameterSet*);
        bool shutdown();
        
        bool update(float timestep);    

		MyGUI::VectorWidgetPtr loadLayout( const std::string& strFile,const std::string& strPrefix );
		void unloadLayout(MyGUI::VectorWidgetPtr & _widgets);
		void showPointer( bool bShow  = true );
		bool isShowPointer( void );
		void showFPS( bool bShow = true );
		bool isShowFPS( void );
		void enableMouse( bool bEnable = true );
		bool isEnableMouse( void );
		void enableKeyboard( bool bEnable = true);
		bool isEnableKeyboard( void );
		void injectChar( MyGUI::Char _char );
		void setFocus( MyGUI::WidgetPtr widget);
		void resizeWindow();

		bool keyPressed(const OIS::KeyEvent & keyboardEvent_);
		bool keyReleased(const OIS::KeyEvent & keyboardEvent_);
		bool mouseMoved(const OIS::MouseEvent & mouseEvent_);
		bool mousePressed(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_);
		bool mouseReleased(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_);

	private:
		MyGUI::WidgetPtr m_pFpsInfo, m_pFpsInfoShadow;
		MyGUI::VectorWidgetPtr mWidgets;

		MyGUI::Gui* m_pGUI;
		Ogre::RenderWindow* m_pRenderWindow;
		bool m_bEnableMouse;
		bool m_bEnableKeyboard;
		float m_fLastFPSUpdateTime;
    };
}


#endif
