#pragma once

#include <cstdint>
#include <cstddef>
#include <iostream>

#include "HeapAllocDefines.hpp"


namespace HeapAllocator
{
constexpr size_t DEFAULT_HEAP_SIZE = 1024*1024;
// constexpr int DEFAULT_BLOCK_SIZE = 1024;


struct Block
{
    bool free;
    size_t size;
    Block* next;
    Block* prev;

    void* data() { return reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(this) + sizeof(Block)); }
};

class LinkedListHeapAllocator : public HeapAllocator
{
public:
	LinkedListHeapAllocator(size_t heap_size)
		: HeapAllocator()
		, head_(nullptr)
		, heap_size_(heap_size)
	{
	}

	virtual ~LinkedListHeapAllocator()
	{
		if (head_)
		{
			delete[] reinterpret_cast<uint8_t*>(head_);
		}
	}

protected:
	Block* head_;
	size_t heap_size_;
};

} // namespace HeapAllocator
