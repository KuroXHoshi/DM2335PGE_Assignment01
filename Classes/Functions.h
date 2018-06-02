#pragma once

template <class T>
T GetData(void* A, void* B);

template<class T>
inline T GetData(void * A, void * B)
{
	T temp = static_cast<T>(A);
	if (temp)
	{
		return temp;
	}
	temp = static_cast<T>(B);
	if (temp)
	{
		return temp;
	}

	return nullptr;
}
