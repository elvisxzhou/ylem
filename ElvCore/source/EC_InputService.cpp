#include "EC_InputService.h"
#include "EC_ParameterSet.h"

namespace ElvCore
{
	InputService::InputService(unsigned int id,std::string name)
	:	Service(id,name)
	, _ois(0), _mouse(0), _keyboard(0)
	{
	}

	InputService::~InputService(void) 
	{
	}

	bool InputService::initialize(ParameterSet* var)
	{
		unsigned long hwnd = var->GetInt("HWND");
		OIS::ParamList pl;
		pl.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hwnd)));
		pl.insert( std::make_pair( std::string("w32_mouse"), std::string("DISCL_FOREGROUND" ) ) );
		pl.insert( std::make_pair( std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE") ) );

		_ois = OIS::InputManager::createInputSystem( pl );
		_mouse = static_cast<OIS::Mouse*>(_ois->createInputObject( OIS::OISMouse, true ));
		_keyboard = static_cast<OIS::Keyboard*>(_ois->createInputObject( OIS::OISKeyboard, true));
		
		_mouse->setEventCallback(this);
		_keyboard->setEventCallback(this);

		Ogre::RenderWindow* rw = reinterpret_cast<Ogre::RenderWindow*>(var->GetInt( "RenderWindow"));

		setWindowExtents(rw->getWidth(),rw->getHeight());

		memset(_keystate,0,sizeof(_keystate));
		return true;
	}

	bool InputService::shutdown()
	{
		_ois->destroyInputObject(_mouse);
		_ois->destroyInputObject( _keyboard );

		OIS::InputManager::destroyInputSystem(_ois);

		return true;
	}

	bool InputService::update(float timestep) 
	{
		_mouse->capture();
		_keyboard->capture();


		for(ListenerList::iterator it = mRemoves.begin(); it != mRemoves.end(); ++it)
		{
			ListenerList::iterator it1 = std::find(mListenerList.begin(),mListenerList.end(),(*it));
			if( it1 != mListenerList.end() )
				mListenerList.erase(it1);

		}
		return true;
	}

	void  InputService::setWindowExtents(int width_, int height_)
	{
		const OIS::MouseState & mouseState = _mouse->getMouseState();
		mouseState.width = width_;
		mouseState.height = height_;
	}

	void InputService::addInputCallBack(InputCallback * inputCallback_)
	{ 
		if(!inputCallback_){ return; }
		ListenerList::size_type size = mListenerList.size();
		mListenerList.push_back(inputCallback_); 
	}

	void InputService::removeInputCallBack(InputCallback * inputCallback_)
	{
		mRemoves.push_back(inputCallback_);
	}

	bool InputService::mouseMoved(const OIS::MouseEvent & mouseEvent_) 
	{
		for (ListenerList::iterator i = mListenerList.begin(); 
				 i != mListenerList.end(); ++i)
		{
			(*i)->mouseMoved(mouseEvent_);
		}
		return true;
	}

	bool InputService::mousePressed(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_)
	{
		for (ListenerList::iterator i = mListenerList.begin(); 
			i != mListenerList.end(); ++i)
		{
			(*i)->mousePressed(mouseEvent_, mouseButton_);
		}
		return true;
	}

	bool InputService::mouseReleased(const OIS::MouseEvent & mouseEvent_, OIS::MouseButtonID mouseButton_) 
	{
		for (ListenerList::iterator i = mListenerList.begin(); 
			i != mListenerList.end(); ++i)
		{
			(*i)->mouseReleased(mouseEvent_, mouseButton_);
		}
		return true;
	}

	bool InputService::keyPressed(const OIS::KeyEvent & keyboardEvent_) 
	{
		_keystate[keyboardEvent_.key] = 1;

		for (ListenerList::iterator i = mListenerList.begin(); 
			i != mListenerList.end(); ++i)
		{
			(*i)->keyPressed(keyboardEvent_);
		}
		return true;
	}

	bool InputService::keyReleased(const OIS::KeyEvent & keyboardEvent_)
	{
		_keystate[keyboardEvent_.key] = 0;

		for (ListenerList::iterator i = mListenerList.begin(); 
			i != mListenerList.end(); ++i)
		{
			(*i)->keyReleased(keyboardEvent_);
		}
		return true;
	}
}
