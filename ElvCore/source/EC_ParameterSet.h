#ifndef EC_ParameterSet_H
#define EC_ParameterSet_H

#include "EC_Common.h"

namespace ElvCore
{
	class ParameterSet
	{
	public:
		static ParameterSet* GetNewParameterSet( void );
		static void FreeParameterSet( ParameterSet* v );
		static void ClearPool( void );

		float GetFloat( const char* name ) const;
		int GetInt( const char* name ) const;
		bool GetBool( const char* name ) const;
		const std::string& GetString( const char* name ) const;
		ParameterSet* GetTable( const char* name );

		void AddFloat( const char* name, const float v );
		void AddInt( const char* name, const int v );
		void AddBool( const char* name, const bool v );
		void AddString( const char* name, const std::string& v );
		ParameterSet* AddTable( const char* name );

		bool QueryName( const char* name ) const;

		void ConvertToTable( void );

		ParameterSet& operator = ( const ParameterSet& ps );

	protected:
		ParameterSet( void );
		virtual ~ParameterSet( void );

		static std::string* GetNewString( int size );
		static void FreeString( std::string* );

		union value
		{
			int		i;
			float	f;
			bool	b;
			std::string* str;
			std::map< std::string, ParameterSet* >* table;
		} m_value;

		enum TYPE
		{
			UNUSED,
			FLOAT,
			BOOL,
			STRING,
			TABLE,
			INT
		} m_type;

		static std::stack< std::string* > m_sStringPool[3];
		static std::stack< ParameterSet* > m_sParameterSetPool;	
	};
}

#endif