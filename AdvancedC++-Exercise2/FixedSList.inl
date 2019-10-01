#include "FixedSList.h"

template<class T, unsigned int N>
FixedSList<T, N>::FixedSList()
{
	_Root = &_Data[0];
	_Size = 0;
};
