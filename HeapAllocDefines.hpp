#pragma once

namespace HeapAllocator
{

class HeapAllocator
{
public:
	virtual void* allocate(size_t size) = 0;
	virtual bool deallocate(void* ptr) = 0;

	virtual void print() const = 0;
};

} // namespace HeapAllocator
