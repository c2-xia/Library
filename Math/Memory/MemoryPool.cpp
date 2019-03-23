#include "defines.h"
#include "MemoryPool.h"

 
static int kMinBlockSize = sizeof(void*);

MemoryPool::MemoryPool( const char* name, int blockSize, int hintSize)
	:m_Bubbles()
#if DEBUGMODE
	, m_PeakAllocCount(0)
	, m_Name(name)
#endif
{
#if ENABLE_THREAD_CHECK_IN_ALLOCS
	m_ThreadCheck = threadCheck;
#endif

	if (blockSize < kMinBlockSize)
		blockSize = kMinBlockSize;
	m_BlockSize = blockSize;


	m_BubbleSize = hintSize;
	m_BlocksPerBubble = (m_BubbleSize - sizeof(Bubble) + 1) / blockSize;

	int usedBubbleSize = sizeof(Bubble) + m_BlocksPerBubble * blockSize - 1;
	Assert(usedBubbleSize <= m_BubbleSize);
	Assert(m_BubbleSize - usedBubbleSize <= m_BlockSize);

	Assert(m_BlocksPerBubble >= 128);
	Assert(hintSize % 4096 == 0);

	m_AllocateMemoryAutomatically = true;

	Reset();
}


MemoryPool::~MemoryPool()
{
	DeallocateAll();
}

void MemoryPool::Reset()
{ 
	m_AllocCount = 0; 
	m_HeadOfFreeList = NULL;
}

void MemoryPool::DeallocateAll()
{
	Bubbles::iterator it, itEnd = m_Bubbles.end();
	for (it = m_Bubbles.begin(); it != itEnd; ++it)
		XIA_FREE(NULL, *it);
	m_Bubbles.clear();
	Reset();
}

void MemoryPool::PreallocateMemory(int size)
{
	bool temp = m_AllocateMemoryAutomatically;
	m_AllocateMemoryAutomatically = true;
	for (int i = 0; i <= size / (m_BlocksPerBubble * m_BlockSize); i++)
	{
		AllocNewBubble();
	}
	m_AllocateMemoryAutomatically = temp;
}

void MemoryPool::AllocNewBubble()
{
	if (!m_AllocateMemoryAutomatically)
		return;

	Assert(m_BlocksPerBubble != 1); // can't have 1 element per bubble

	Bubble *bubble = (Bubble*)XIA_MALLOC(NULL, m_BubbleSize);
	Assert(bubble);

	// put to bubble list
	m_Bubbles.push_back(bubble);

	// setup the free list inside a bubble
	void* oldHeadOfFreeList = m_HeadOfFreeList;
	m_HeadOfFreeList = bubble->data;
	Assert(m_HeadOfFreeList);

	void **newBubble = (void**)m_HeadOfFreeList;
	for (int j = 0; j < m_BlocksPerBubble - 1; ++j)
	{
		newBubble[0] = (char*)newBubble + m_BlockSize;
		newBubble = (void**)newBubble[0];
	}

	newBubble[0] = oldHeadOfFreeList; // continue with existing free list (or terminate with NULL if no free elements)

	// still failure, error out
	if (!m_HeadOfFreeList)
	{
		 //error
	}
}


void* MemoryPool::Allocate()
{
	return Allocate(m_BlockSize);
}


void *MemoryPool::Allocate(size_t amount)
{
#if ENABLE_THREAD_CHECK_IN_ALLOCS
	ErrorAndReturnValueIf(m_ThreadCheck && Thread::mainThreadId && !Thread::CurrentThreadIsMainThread(), NULL);
#endif 
	void *returnBlock;

	if (amount > (unsigned int)m_BlockSize) {
		//error
		return NULL;
	}

	if (!m_HeadOfFreeList) {
		// allocate new bubble
		AllocNewBubble();

		// Can't allocate
		if (m_HeadOfFreeList == NULL)
			return NULL;
	}
	 
	++m_AllocCount;
	if (m_AllocCount > m_PeakAllocCount)
		m_PeakAllocCount = m_AllocCount;
  
	returnBlock = m_HeadOfFreeList;

	// move the pointer to the next block
	m_HeadOfFreeList = *((void**)m_HeadOfFreeList);

	return returnBlock;
}



void MemoryPool::Deallocate(void *mem_Block)
{
  
	if (!mem_Block) // ignore NULL deletes
		return;

#ifdef DEBUG
	// check to see if the memory is from the allocated range
	bool ok = false;
	size_t n = m_Bubbles.size();
	for (size_t i = 0; i < n; ++i) {
		Bubble* p = m_Bubbles[i];
		if ((char*)mem_Block >= p->data && (char*)mem_Block < (p->data + m_BlockSize * m_BlocksPerBubble)) {
			ok = true;
			break;
		}
	}
	Assert(ok);

	memset(mem_Block, 0xDD, m_BlockSize);
	AssertIf(m_AllocCount == 0);

	--m_AllocCount;
#endif // DEBUG
	  
	// make the block point to the first free item in the list
	*((void**)mem_Block) = m_HeadOfFreeList;
	// the list head is now the Deallocated block
	m_HeadOfFreeList = mem_Block;
}
