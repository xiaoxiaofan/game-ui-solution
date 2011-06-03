#pragma once

template <typename T> class Singleton
{

private:
	Singleton(const Singleton<T> &);

	Singleton& operator=(const Singleton<T> &);

protected:

	static T* ms_Singleton;

public:
	Singleton( void )
	{
		assert( !ms_Singleton );
		ms_Singleton = static_cast< T* >( this );
	}

	~Singleton( void )
	{  
		assert( ms_Singleton );  
		ms_Singleton = 0;  
	}
	static T& getSingleton( void )
	{	
		assert( ms_Singleton );  
		return ( *ms_Singleton ); 
	}
	static T* getSingletonPtr( void )
	{ 
		return ms_Singleton; 
	}
};