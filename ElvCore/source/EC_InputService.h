#ifndef EC_InputService_H
#define EC_InputService_H

#include "EC_Service.h"


namespace ElvCore
{
	class InputCallback
	{
	public:
		InputCallback()
		{}
		virtual ~InputCallback(){};

		virtual bool keyPressed(OIS::KeyEvent const & keyboardEvent_){ return false; }
		virtual bool keyReleased(OIS::KeyEvent const & keyboardEvent_){ return false; }
		virtual bool mouseMoved(const OIS::MouseEvent & mouseEvent_){ return false; }
		virtual bool mousePressed(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_){ return false; }
		virtual bool mouseReleased(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_){ return false; }
	};

	class InputService 
		: public OIS::MouseListener
		, public OIS::KeyListener
		, public Service
	{
	public:
		InputService(unsigned int id,std::string name); 
		~InputService(void);


		bool initialize(ParameterSet*);
		bool shutdown();
		bool update(float timestep);

		void setWindowExtents(int width_, int height_);
		
		void addInputCallBack(InputCallback * inputCallback_);
		void removeInputCallBack(InputCallback* InputCallback_);

		bool mouseMoved(const OIS::MouseEvent & mouseEvent_);
		bool mousePressed(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_);
		bool mouseReleased(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_);
		bool keyPressed(const OIS::KeyEvent & keyboardEvent_);
		bool keyReleased(const OIS::KeyEvent & keyboardEvent_);

		bool isKeyDown(OIS::KeyCode key) { return _keystate[key] == 1; }

	private:
		typedef std::vector< InputCallback * > ListenerList;

		ListenerList mListenerList;
		ListenerList mRemoves;

		OIS::InputManager * _ois;
		OIS::Mouse * _mouse;
		OIS::Keyboard * _keyboard;

		char _keystate[256];
	};
}

#endif