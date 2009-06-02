#ifndef EC_COMMON_H
#define EC_COMMON_H


#include <windows.h>
#include <mmsystem.h>

#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stack>
#include "Ogre.h"
#include "OIS/OIS.h"
#include <MyGUI.h>
#include <ParticleUniverseSystemManager.h>
#include <tinyxml/tinyxml.h>

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//#include <luabind/open.hpp>

namespace ElvCore
{
	class Core;
	class Service;
	class PhysicService;
	class GuiService;
	class AudioService;
	class AIService;
	class InputService;
	class GfxService;
	class ScriptService;
	class EventService;
	class ParameterSet;
	class Event;
	class ListNode;
	class Serialise;
	class Deserialise;

	template<class T>
	class ObjectPool;

	class Object;
	class Component;
	class TerrainService;
}


#define CORE	ElvCore::Core::getSingletonPtr()
#define GFX		((ElvCore::GfxService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eGfxService))
#define PHYSIC	((ElvCore::PhysicService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::ePhysicService))
#define GUI		((ElvCore::GuiService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eGuiService))
#define AUDIO	((ElvCore::AudioService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eAudioService))
#define AI		((ElvCore::AIService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eAIService))
#define INPUT	((ElvCore::InputService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eInputService))
#define SCRIPT	((ElvCore::ScriptService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eScriptService))
#define EVENT	((ElvCore::EventService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eEventService))
#define OBJ		((ElvCore::ObjectService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eObjectService))
#define TERRAIN	((ElvCore::TerrainService*)ElvCore::Core::getSingletonPtr()->getService(ElvCore::eTerrainService))

#endif