#include <iostream>
#include <vector>


#include "FirstFitLinkedListAllocator.hpp"


using HeapAllocator::FirstFitLinkedListAllocator;

int main()
{
	const size_t heapSize = 1024;
	FirstFitLinkedListAllocator heap(heapSize);
	std::vector<void*> blocksAllocated;
	for (const auto& allocSize : std::vector<size_t>({ 128, 256, 256, 64 }))
	{
		if (void* ptr = heap.allocate(allocSize))
		{
			blocksAllocated.push_back(ptr);
			heap.print();
		}
		else
		{
			std::cout << "Failed to allocate " << allocSize << " bytes" << std::endl;
		}
	}

	for (const auto& blockPtr : blocksAllocated)
	{
		if (!heap.deallocate(blockPtr))
		{
			std::cout << "Failed to deallocate " << blockPtr << std::endl;
		}
		heap.print();
	}

	return 0;
}
