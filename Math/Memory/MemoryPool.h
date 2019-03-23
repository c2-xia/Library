#include "Std/dynamic_array.h"

class MemoryPool
{
public:
	MemoryPool(const char* name, int blockSize, int allocatedSizeHint);
	~MemoryPool();

	/// Allocate single block
	void*	Allocate();
	/// Allocate less than single block
	void*	Allocate(size_t amount);
	/// Deallocate
	void	Deallocate(void *ptr);
	/// Deallocate everything
	void	DeallocateAll();

	 
	size_t GetBubbleCount() const { return m_Bubbles.size(); }
	int GetAllocCount() const { return m_AllocCount; }
  
	int	GetAllocatedBytes() { return m_Bubbles.size() * m_BlocksPerBubble * m_BlockSize; }

	int	GetAllocatedObjectsCount() { return m_AllocCount; }


	void PreallocateMemory(int size);
	void SetAllocateMemoryAutomatically(bool allocateMemoryAuto) { m_AllocateMemoryAutomatically = allocateMemoryAuto; }


private:
	void	AllocNewBubble();

	struct Bubble
	{
		char	data[1]; // actually byteCount
	};
	typedef dynamic_array<Bubble*>	Bubbles;

	void	Reset();
private:
	int 	m_BlockSize;
	int 	m_BubbleSize;
	int 	m_BlocksPerBubble;

	Bubbles	m_Bubbles;

	void*	m_HeadOfFreeList;
	bool    m_AllocateMemoryAutomatically;


	int 	m_AllocCount; // number of blocks currently allocated
 
	int 	m_PeakAllocCount; // stats
	const char*	m_Name; // for debugging
 
  


};