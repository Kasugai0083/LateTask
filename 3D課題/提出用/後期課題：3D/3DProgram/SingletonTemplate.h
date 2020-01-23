#pragma once

template<class T>
class Singleton 
{
public:
	static void CreateInstance()
	{
		if (IsNull() == true) { p_Instance = new T(); }
	}
	static void DestroyInstance()
	{
		if(IsNull() == false) {	delete p_Instance; }
	}
	static bool IsNull()
	{
		return p_Instance == nullptr;
	}
	static T* GetInstance()
	{
		return p_Instance;
	}
protected:
	Singleton(){}
	~Singleton(){}
private:
	static T* p_Instance;
};

template <class T>
T* Singleton<T>::p_Instance = nullptr;