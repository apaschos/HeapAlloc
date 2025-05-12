#include <iostream>
#include <vector>


#include "HeapAlloc.hpp"


int main()
{
	const size_t heapSize = 1024;
	Heap heap(heapSize);
	for (const auto& allocSize : std::vector<size_t>({ 128, 256, 256, 64 }))
	{
		if (heap.allocate(allocSize))
		{
			heap.print();
		}
		else
		{
			std::cout << "Failed to allocate " << allocSize << " bytes" << std::endl;
		}
	}

	void* ptr = heap.findFirstBlock(256);
	if (!ptr)
	{
		std::cout << "Failed to find block of size " << 256 << " bytes" << std::endl;
	}
	else
	{
		if (heap.deallocate(ptr))
		{
			heap.print();
		}
		else
		{
			std::cout << "Failed to deallocate " << ptr << " of size " << 256 << " bytes" << std::endl;
		}
	}

	return 0;
}
