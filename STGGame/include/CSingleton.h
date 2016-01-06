#pragma once

//µ¥¼þÄ£°å
template <typename T>
class CSingleton
{
private:
	CSingleton( )
	{ 
	m_instance = new T();
	}
	~CSingleton()
	{ 
	if(m_instance)
		delete m_instance;
	m_instance = 0;
	}
public:
	inline static T* Instance()
	{
	static CSingleton i;
	return m_instance;
	}
	static T* m_instance;
};

template<typename T> 
	T* CSingleton<T>::m_instance = 0;

#define INSTANCE(CLASS) CSingleton<CLASS>::Instance()
#define SINGLETON(CLASS) friend CSingleton<CLASS>

