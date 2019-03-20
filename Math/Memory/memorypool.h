
class MemoryPool {
public:
	MemoryPool( bool threadCheck, const char* name, int blockSize, int allocatedSizeHint, char* labelInfo);
	~MemoryPool();

	/// Allocate single block
	void*	Allocate();
	/// Allocate less than single block
	void*	Allocate( size_t amount );
	/// Deallocate
	void	Deallocate( void *ptr );
	/// Deallocate everything
	void	DeallocateAll();


	#if !DEPLOY_OPTIMIZED
	size_t GetBubbleCount() const { return m_Bubbles.size(); }
	int GetAllocCount() const { return m_AllocCount; }
	#endif

	int	GetAllocatedBytes() { return m_Bubbles.size () * m_BlocksPerBubble * m_BlockSize;  }

	#if DEBUGMODE
	int	GetAllocatedObjectsCount() { return m_AllocCount; }
	#endif

	void PreallocateMemory(int size);
	void SetAllocateMemoryAutomatically (bool allocateMemoryAuto) { m_AllocateMemoryAutomatically = allocateMemoryAuto; }

	static void StaticInitialize();
	static void StaticDestroy();
	static void RegisterStaticMemoryPool(MemoryPool* pool);

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

	MemLabelId m_AllocLabel;

	int 	m_AllocCount; // number of blocks currently allocated
	#if DEBUGMODE
	int 	m_PeakAllocCount; // stats
	const char*	m_Name; // for debugging
	#endif

	#if ENABLE_THREAD_CHECK_IN_ALLOCS
	bool m_ThreadCheck;
	#endif

	static UNITY_VECTOR(kMemPoolAlloc,MemoryPool*)* s_MemoryPools;
};