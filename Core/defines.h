#ifndef _DEFINES_H
#define _DEFINES_H
//#define NDEBUG
#include <assert.h>

#define ALIGN_OF(T) alignof(T)

#define ALIGN_TYPE(val) alignas(val)
 
#define Assert(x) assert(x)

#define DebugAssert(x) assert(x)

#define CompileTimeAssert(x,y) static_assert(x,y)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define Epsilon   1.17549435E-38f

enum
{
	kAllocateOptionNone = 0,						// Fatal: Show message box with out of memory error and quit application
	kAllocateOptionReturnNullIfOutOfMemory = 1		// Returns null if allocation fails (doesn't show message box)
};

#define real float

enum
{
#if XIA_ANDROID 
	DefaultMemoryAlignment = 16
#else
	DefaultMemoryAlignment = sizeof(void*)
#endif
};

void* malloc_internal(size_t size, int align, char* label, int allocateOptions, const char* file, int line);
void* calloc_internal(size_t count, size_t size, int align, char* label, int allocateOptions, const char* file, int line);
void* realloc_internal(void* ptr, size_t size, int align, char* label, int allocateOptions, const char* file, int line);
void  free_alloc_internal(void* ptr, char* label);

#define XIA_MALLOC(label, size)                      malloc_internal(size, DefaultMemoryAlignment, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_MALLOC_NULL(label, size)                 malloc_internal(size, DefaultMemoryAlignment, label, kAllocateOptionReturnNullIfOutOfMemory, __FILE__, __LINE__)
#define XIA_MALLOC_ALIGNED(label, size, align)       malloc_internal(size, align, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_MALLOC_ALIGNED_NULL(label, size, align)  malloc_internal(size, align, label, kAllocateOptionReturnNullIfOutOfMemory, __FILE__, __LINE__)
#define XIA_CALLOC(label, count, size)               calloc_internal(count, size, DefaultMemoryAlignment, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_REALLOC_(label, ptr, size)               realloc_internal(ptr, size, DefaultMemoryAlignment, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_REALLOC_ALIGNED(label, ptr, size, align) realloc_internal(ptr, size, align, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_FREE(label, ptr)                         free_alloc_internal(ptr, label)


#endif // !_DEFINES_H

