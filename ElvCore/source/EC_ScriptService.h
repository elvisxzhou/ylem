#ifndef EC_ScriptService_H
#define EC_ScriptService_H

#include "EC_Service.h"


namespace ElvCore
{
    class ScriptService : public Service
    {
    public:
        ScriptService(unsigned int id,std::string name);
        ~ScriptService();

        bool initialize(ParameterSet*);
        bool shutdown();
        bool update(float timestep);

		bool runFile( const char* szFileName );
		bool runString( const char* szString );
		bool runCommand( const char* szCommand, ... );

		void check() const;

	private:
		lua_State* mLuaState;
		int m_top;
    };
}


#endif
