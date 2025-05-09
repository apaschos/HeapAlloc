#include "HeapAlloc.hpp"

#include <iostream>


Heap::Heap(size_t heap_size)
: heap_size_(heap_size)
{
	if(heap_size_ == 0)
	{
		throw std::bad_alloc();
	}

    head = reinterpret_cast<Block*>(new uint8_t[heap_size_ + sizeof(Block)]);
    head->size = heap_size_;
    head->free = true;
    head->prev = nullptr;
    head->next = nullptr;
}

Heap::~Heap()
{
    delete reinterpret_cast<uint8_t*>(head);
}

Block* Heap::findFirstFreeBlock()
{
    Block* current = head;
    while(current)
    {
        if(current->free)
        {
            return current;
        }
        current = current->next;
    }

    // no free block
    return nullptr;
}

void* Heap::allocate(const size_t size)
{
    if (size == 0)
    {
        return nullptr;
    }

    Block* available = findFirstFreeBlock();
    if(available)
    {
    	const size_t sizeWithHeader = size + sizeof(Block);
        if(available->size > sizeWithHeader)
        {
            return split_block(available, size);
        }
    }

    return nullptr;
}

void Heap::print()
{
	Block* current = head;
	while(current)
	{
		std::cout << (current->free ? "O" : "X") << " - " << current->size << std::endl;
		current = current->next;
	}
	std::cout << std::endl;
}

void* Heap::split_block(Block* block, size_t req_size)
{
    // Create new block andplace allocation in beginning.
    // Move original block to after new block and resize.

    Block* oldBlock = reinterpret_cast<Block*>(reinterpret_cast<uint8_t*>(block->data()) + req_size);
    oldBlock->size = block->size - req_size;
    oldBlock->free = true;
    oldBlock->next = block->next;

    Block* newBlock = block;
    newBlock->size = req_size;
    newBlock->free = false;
    newBlock->next = oldBlock;
    newBlock->prev = oldBlock->prev;
    oldBlock->prev = newBlock;

    return newBlock->data();
}
