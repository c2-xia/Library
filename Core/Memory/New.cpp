#include <string.h>
#include <new>
#include "../defines.h"

#define XIA_LL_ALLOC(l,s,a) ::malloc(s)
#define XIA_LL_REALLOC(l,p,s,a) ::realloc(p, s)
#define XIA_LL_FREE(l,p) ::free(p)


void* operator new (size_t size, char* label, bool set_root, int align, const char* file, int line)
{ 
	void* p = malloc_internal(size, align, label, kAllocateOptionNone, file, line); 
	return p;
}

void* operator new [](size_t size, char* label, bool set_root, int align, const char* file, int line)
{ 
	void* p = malloc_internal(size, align, label, kAllocateOptionNone, file, line);
	return p;
}


void operator delete (void* p, char* label, bool /*set_root*/, int /*align*/, const char* /*file*/, int /*line*/) { free_alloc_internal(p, label); }
void operator delete [](void* p, char* label, bool /*set_root*/, int /*align*/, const char* /*file*/, int /*line*/) { free_alloc_internal(p, label); }

#if _DEBUG
class New_G_Values
{
public:
	int value ;
	static   New_G_Values* Instance;
};
New_G_Values* New_G_Values::Instance = new New_G_Values();
#endif


void* malloc_internal(size_t size, int align, char* label, int allocateOptions, const char* file, int line)
{
#if _DEBUG
	New_G_Values::Instance->value = 20191;
#endif
	return XIA_LL_ALLOC(label, size, align);
}

void* calloc_internal(size_t count, size_t size, int align, char* label, int allocateOptions, const char* file, int line)
{
#if _DEBUG
	New_G_Values::Instance->value = 20192;
#endif
	void* ptr = XIA_LL_ALLOC(label, size * count, align);
	memset(ptr, 0, size * count);
	return ptr;
}

void* realloc_internal(void* ptr, size_t size, int align, char* label, int allocateOptions, const char* file, int line)
{
#if _DEBUG
	New_G_Values::Instance->value = 20193;
#endif
	return XIA_LL_REALLOC(label, ptr, size, align);
}

void free_alloc_internal(void* ptr, char* label)
{
#if _DEBUG
	New_G_Values::Instance->value = 20194;
#endif
	XIA_LL_FREE(label, ptr);
}
#define THROWING_NEW_THROW throw()
void* operator new (size_t size) THROWING_NEW_THROW
{
#if _DEBUG
	if(New_G_Values::Instance!=NULL) 
		New_G_Values::Instance->value = 20195;
#endif
	return XIA_LL_ALLOC(kMemNewDelete, size, kDefaultMemoryAlignment); 
}
void* operator new[](size_t size) THROWING_NEW_THROW{
	#if _DEBUG
	if (New_G_Values::Instance != NULL)
		New_G_Values::Instance->value = 20196;
#endif
	return XIA_LL_ALLOC(kMemNewDelete, size, kDefaultMemoryAlignment);
}
void operator delete (void* p) throw() {
#if _DEBUG
	if (New_G_Values::Instance != NULL)
		New_G_Values::Instance->value = 20197;
#endif
	XIA_LL_FREE(kMemNewDelete, p);
} // can't make allocator assumption, since ptr can be newed by other operator new
void operator delete [](void* p) throw() {
#if _DEBUG
	if (New_G_Values::Instance != NULL)
		New_G_Values::Instance->value = 20198;
#endif
	XIA_LL_FREE(kMemNewDelete, p);
}

void* operator new (size_t size, const std::nothrow_t&) throw() {
	return XIA_LL_ALLOC(kMemNewDelete, size, kDefaultMemoryAlignment);
}
void* operator new [](size_t size, const std::nothrow_t&) throw() { 
	return XIA_LL_ALLOC(kMemNewDelete, size, kDefaultMemoryAlignment);
};
void operator delete (void* p, const std::nothrow_t&) throw() {
	XIA_LL_FREE(kMemNewDelete, p); 
}
void operator delete [](void* p, const std::nothrow_t&) throw() {
	XIA_LL_FREE(kMemNewDelete, p);
}