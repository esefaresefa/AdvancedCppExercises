#include <iostream>


// Defining types
typedef char tChar;
typedef uint32_t tU32;


// Defining function helpers
#define Malloc(SIZE, TYPE, DESC) _Malloc(SIZE, TYPE, DESC, __FILE__, __LINE__)
#define Realloc(PTR, SIZE) _Realloc(PTR, SIZE, __FILE__, __LINE__)
#define New(CLASS, TYPE, DESC) new(TYPE, DESC, __FILE__, __LINE__) CLASS
#define Delete delete


// Heap Store
void* _Malloc(tU32 Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line) { return nullptr; };
void* _Realloc(void* Ptr, tU32 Size, const tChar* File, tU32 Line) { return nullptr; };
void _Free(void* Ptr) {};


// Free Store
inline void* operator new(size_t Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line) { return _Malloc(Size, AllocType, Desc, File, Line); }
inline void* operator new[](size_t Size, tU32 AllocType, const tChar* Desc, const tChar* File, tU32 Line) { return _Malloc(Size, AllocType, Desc, File, Line); }
inline void operator delete(void* Ptr) { _Free(Ptr); }
inline void operator delete[](void* Ptr) { _Free(Ptr); }


int main()
{
	return 0;
}