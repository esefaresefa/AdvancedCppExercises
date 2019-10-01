#pragma once

template<typename T>
class Singleton
{
public:

	static T* GetInstance();

private:
	Singleton();
};

template<typename T>
T* Singleton<T>::GetInstance()
{
	static T instance;
	return &instance;
}
