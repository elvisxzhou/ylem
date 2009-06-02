#include "EC_ScriptService.h"

extern int tolua__open( lua_State* tolua_S );

namespace ElvCore
{
	ScriptService::ScriptService(unsigned int id,std::string name)
	:	Service(id,name)
	, mLuaState( NULL )
    {
    }
    
    ScriptService::~ScriptService()
    {

    }

    bool ScriptService::initialize(ParameterSet*)
    {
		mLuaState = lua_open();
		luaL_openlibs( mLuaState );

		m_top = lua_gettop(mLuaState);
//		luabind::open(mLuaState);
		return true;
    }
    
    bool ScriptService::shutdown()
    {
		lua_close( mLuaState );
		return true;
    }
    
    bool ScriptService::update(float timestep)
    {
        return true;
    }

	bool ScriptService::runFile( const char* szFileName )
	{
		if ( luaL_dofile( mLuaState, szFileName ) )
		{
			printf("runFile failed! \n %s \n",lua_tostring( mLuaState, -1 ));
			return false;
		}

		return true;
	}

	bool ScriptService::runString( const char* szString )
	{
		if ( luaL_dostring( mLuaState, szString ) )
		{
			printf("runString failed! \n %s \n",lua_tostring( mLuaState, -1 ));
			return false;
		}

		return true;
	}

	bool ScriptService::runCommand( const char* szCommand, ... )
	{
		char szBuf[10240];

		va_list pParamList;

		va_start( pParamList, szCommand );

		vsprintf_s( szBuf, 10240, szCommand, pParamList );

		va_end( pParamList );

		return runString( szBuf );
	}

	void ScriptService::check() const
	{
		assert(lua_gettop(mLuaState) == m_top);
	}
}

