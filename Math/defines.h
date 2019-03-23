#ifndef DEFINES_H
#define DEFINES_H



#if defined(__GNUC__)
#define ALIGN_OF(T) __alignof__(T)
#define ALIGN_TYPE(val) __attribute__((aligned(val)))
#define FORCE_INLINE inline __attribute__ ((always_inline))
#elif defined(_MSC_VER)
#define ALIGN_OF(T) __alignof(T)
#define ALIGN_TYPE(val) __declspec(align(val))
#define FORCE_INLINE __forceinline
#else
#define ALIGN_TYPE(size)
#define FORCE_INLINE inline
#endif


#define Assert(x)
#define DebugAssert(x)

#define CompileTimeAssert(x,y)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define Epsilon   1.17549435E-38f
enum
{
	kAllocateOptionNone = 0,						// Fatal: Show message box with out of memory error and quit application
	kAllocateOptionReturnNullIfOutOfMemory = 1	// Returns null if allocation fails (doesn't show message box)
};

#define real float

enum
{
#if XIA_ANDROID 
	kDefaultMemoryAlignment = 16
#else
	kDefaultMemoryAlignment = sizeof(void*)
#endif
};

void* malloc_internal(size_t size, int align, char* label, int allocateOptions, const char* file, int line);
void* calloc_internal(size_t count, size_t size, int align, char* label, int allocateOptions, const char* file, int line);
void* realloc_internal(void* ptr, size_t size, int align, char* label, int allocateOptions, const char* file, int line);
void  free_alloc_internal(void* ptr, char* label);

#define XIA_MALLOC(label, size)                      malloc_internal(size, kDefaultMemoryAlignment, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_MALLOC_NULL(label, size)                 malloc_internal(size, kDefaultMemoryAlignment, label, kAllocateOptionReturnNullIfOutOfMemory, __FILE__, __LINE__)
#define XIA_MALLOC_ALIGNED(label, size, align)       malloc_internal(size, align, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_MALLOC_ALIGNED_NULL(label, size, align)  malloc_internal(size, align, label, kAllocateOptionReturnNullIfOutOfMemory, __FILE__, __LINE__)
#define XIA_CALLOC(label, count, size)               calloc_internal(count, size, kDefaultMemoryAlignment, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_REALLOC_(label, ptr, size)               realloc_internal(ptr, size, kDefaultMemoryAlignment, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_REALLOC_ALIGNED(label, ptr, size, align) realloc_internal(ptr, size, align, label, kAllocateOptionNone, __FILE__, __LINE__)
#define XIA_FREE(label, ptr)                         free_alloc_internal(ptr, label)


#endif // !DEFINES_H

