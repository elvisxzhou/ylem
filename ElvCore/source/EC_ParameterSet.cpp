#include "EC_ParameterSet.h"

namespace ElvCore
{

	ParameterSet::ParameterSet( void )
	{
		m_type = UNUSED;
	}

	ParameterSet::~ParameterSet( void )
	{

	}

	std::stack< ParameterSet* > ParameterSet::m_sParameterSetPool;
	std::stack< std::string* > ParameterSet::m_sStringPool[3];

	ParameterSet* ParameterSet::GetNewParameterSet( void )
	{
		if( m_sParameterSetPool.empty() )
		{
			ParameterSet* v = new ParameterSet();
			return v;
		}
		else
		{
			ParameterSet* v = m_sParameterSetPool.top();
			m_sParameterSetPool.pop();
			v->m_type = UNUSED;
			return v;
		}

		return NULL;
	}

	void ParameterSet::FreeParameterSet( ParameterSet* v )
	{
		if(v == NULL)
			return;

		if( v->m_type == STRING )
		{
			FreeString( v->m_value.str );
			v->m_type = UNUSED;
		}
		else if( v->m_type == TABLE )
		{
			for(std::map<std::string, ParameterSet*>::iterator it = v->m_value.table->begin(); it != v->m_value.table->end(); )
			{
				FreeParameterSet( it->second );
				it = v->m_value.table->erase( it );
			}
			delete v->m_value.table;
			v->m_type = UNUSED;
		}
		m_sParameterSetPool.push( v );
	}

	void ParameterSet::ConvertToTable( void )
	{
		if( m_type == STRING )
		{
			FreeString( m_value.str );
		}
		else if( m_type == TABLE )
		{
			return;
		}
		m_value.table = new std::map<std::string, ParameterSet*>;
		m_type = TABLE;
	}

	ParameterSet& ParameterSet::operator = ( const ParameterSet& ps )
	{
		m_type = ps.m_type;

		if( ps.m_type == TABLE )
		{
			ConvertToTable();
			std::map<std::string, ParameterSet*>::iterator itr = ps.m_value.table->begin();
			for( ; itr != ps.m_value.table->end(); itr ++ )
			{
				ParameterSet* pNewSet = GetNewParameterSet();
				*pNewSet = *(itr->second);
				(*m_value.table)[itr->first] = pNewSet;
			}
		}
		else
		{
			m_value = ps.m_value;
		}

		return *this;
	}

	float ParameterSet::GetFloat( const char* name ) const
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it != m_value.table->end() )
			{
				if( it->second->m_type == FLOAT )
				{
					return it->second->m_value.f;
				}
			}
		}

		return 0.0f;
	}

	int ParameterSet::GetInt( const char* name ) const
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it != m_value.table->end() )
			{
				if( it->second->m_type == INT )
				{
					return it->second->m_value.i;
				}
			}
		}

		return 0;
	}

	bool ParameterSet::GetBool( const char* name ) const
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it != m_value.table->end() )
			{
				if( it->second->m_type == BOOL )
				{
					return it->second->m_value.b;
				}
			}
		}

		return false;
	}

	const std::string& ParameterSet::GetString( const char* name ) const
	{
		static std::string strError( "" );

		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it != m_value.table->end() )
			{
				if( it->second->m_type == STRING )
				{
					return *(it->second->m_value.str);
				}
			}
		}

		return strError;
	}

	ParameterSet* ParameterSet::GetTable( const char* name )
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it != m_value.table->end() )
			{
				if( it->second->m_type == TABLE )
				{
					return it->second;
				}
			}
		}

		return NULL;
	}

	bool ParameterSet::QueryName( const char* name ) const
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it != m_value.table->end() )
			{
				return true;
			}
		}

		return false;
	}

	void ParameterSet::AddFloat( const char* name, const float v )
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it == m_value.table->end() )
			{
				ParameterSet* lV = GetNewParameterSet( );
				lV->m_value.f = v;
				lV->m_type = FLOAT;
				(*m_value.table)[ name ] = lV;
			}
			else
			{
				FreeParameterSet( it->second );
				it->second = GetNewParameterSet( );
				it->second->m_value.f = v;
				it->second->m_type = FLOAT;
			}
		}
	}

	void ParameterSet::AddInt( const char* name, const int v )
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it == m_value.table->end() )
			{
				ParameterSet* lV = GetNewParameterSet( );
				lV->m_value.i = v;
				lV->m_type = INT;
				(*m_value.table)[ name ] = lV;
			}
			else
			{
				FreeParameterSet( it->second );
				it->second = GetNewParameterSet( );
				it->second->m_value.i = v;
				it->second->m_type = INT;
			}
		}
	}

	void ParameterSet::AddBool( const char* name, const bool v )
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it == m_value.table->end() )
			{
				ParameterSet* lV = GetNewParameterSet( );
				lV->m_value.b = v;
				lV->m_type = BOOL;
				(*m_value.table)[ name ] = lV;
			}
			else
			{
				FreeParameterSet( it->second );
				it->second = GetNewParameterSet( );
				it->second->m_value.b = v;
				it->second->m_type = BOOL;
			}
		}
	}

	void ParameterSet::AddString( const char* name, const std::string& v )
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it == m_value.table->end() )
			{			
				ParameterSet* lV = GetNewParameterSet( );
				std::string* s = GetNewString( (int)v.size() );
				s->assign( v );
				lV->m_value.str = s;
				lV->m_type = STRING;
				(*m_value.table)[ name ] = lV;
			}
			else
			{
				FreeParameterSet( it->second );
				it->second = GetNewParameterSet( );
				std::string* s = GetNewString( (int)v.size() );
				s->assign( v );
				it->second->m_value.str = s;
				it->second->m_type = STRING;
			}
		}
	}

	ParameterSet* ParameterSet::AddTable( const char* name )
	{
		if( m_type == TABLE )
		{
			std::map<std::string, ParameterSet*>::iterator it = m_value.table->find( name );
			if( it == m_value.table->end() )
			{			
				ParameterSet* v = GetNewParameterSet();
				v->ConvertToTable();
				(*m_value.table)[ name ] = v;
				return v;
			}
			else
			{
				return it->second ;
			}
		}
		return NULL;
	}

	std::string* ParameterSet::GetNewString( int size )
	{
		if( size < 16 )
		{
			if( m_sStringPool[0].empty() )
			{
				std::string* s = new std::string();
				s->reserve(16);
				return s;
			}
			else
			{
				std::string* s = m_sStringPool[0].top();
				m_sStringPool[0].pop();
				return s;
			}
		}
		else if( size < 32 )
		{
			if( m_sStringPool[1].empty() )
			{
				std::string* s = new std::string();
				s->reserve(32);
				return s;
			}
			else
			{
				std::string* s = m_sStringPool[1].top();
				m_sStringPool[1].pop();
				return s;
			}
		}
		else if( size < 64 )
		{
			if( m_sStringPool[2].empty() )
			{
				std::string* s = new std::string();
				s->reserve(64);
				return s;
			}
			else
			{
				std::string* s = m_sStringPool[2].top();
				m_sStringPool[2].pop();
				return s;
			}
		}
		else
		{
			return new std::string();
		}

		return NULL;
	}

	void ParameterSet::FreeString( std::string* s )
	{
		int size = (int)s->size();

		if( size <= 16 )
		{
			m_sStringPool[0].push( s );
		}
		else if( size > 16 && size <= 32 )
		{
			m_sStringPool[1].push( s );
		}
		else if( size > 32 && size <= 64 )
		{
			m_sStringPool[2].push( s );
		}
		else
		{
			delete s;
		}
	}

	void ParameterSet::ClearPool( void )
	{
		while( m_sParameterSetPool.empty() == false )
		{
			delete m_sParameterSetPool.top();
			m_sParameterSetPool.pop();
		}

		for( int i = 0; i<3; i++ )
		{
			while( m_sStringPool[i].empty() == false )
			{
				delete m_sStringPool[i].top();
				m_sStringPool[i].pop();
			}
		}
	}
}