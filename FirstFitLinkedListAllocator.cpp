#include "FirstFitLinkedListAllocator.hpp"

#include <iostream>


namespace HeapAllocator
{

FirstFitLinkedListAllocator::FirstFitLinkedListAllocator(size_t heap_size)
	: LinkedListHeapAllocator(heap_size)
{
	if (heap_size_ == 0)
	{
		throw std::bad_alloc();
	}

	head_ = reinterpret_cast<Block*>(new uint8_t[heap_size_ + sizeof(Block)]);
	head_->size = heap_size_;
	head_->free = true;
	head_->prev = nullptr;
	head_->next = nullptr;
}

FirstFitLinkedListAllocator::~FirstFitLinkedListAllocator()
{
}

Block* FirstFitLinkedListAllocator::findFirstFreeBlock()
{
	for (Block* current = head_; current; current = current->next)
	{
		if (current->free)
		{
			return current;
		}
	}

	// no free block
	return nullptr;
}

void* FirstFitLinkedListAllocator::allocate(const size_t size)
{
	if (size == 0)
	{
		return nullptr;
	}

	Block* available = findFirstFreeBlock();
	if (available)
	{
		const size_t sizeWithHeader = size + sizeof(Block);
		if (available->size > sizeWithHeader)
		{
			return split_block(available, size);
		}
	}

	return nullptr;
}

bool FirstFitLinkedListAllocator::deallocate(void* ptr)
{
	if (!ptr)
	{
		return false;
	}

	Block* block = reinterpret_cast<Block*>(reinterpret_cast<uint8_t*>(ptr) - sizeof(Block));
	if (!block)
	{
		return false;
	}

	block->free = true;
	coalesce_blocks(block);

	return true;
}

void FirstFitLinkedListAllocator::print() const
{
	const std::string blockAvailable = "free";
	const std::string blockReserved = "reserved";

	int i = 1;
	for (Block* current = head_; current; current = current->next)
	{
		std::cout << (i++) << ": " << current->size << " - " << (current->free ? blockAvailable : blockReserved) << std::endl;
	}
	std::cout << std::endl;
}

void* FirstFitLinkedListAllocator::split_block(Block* block, size_t req_size)
{
	// Create new block and place allocation in beginning.
	// Move original block to after new block and resize.

	Block* oldBlock = reinterpret_cast<Block*>(reinterpret_cast<uint8_t*>(block->data()) + req_size);
	oldBlock->size = block->size - req_size - sizeof(Block);
	oldBlock->free = true;
	oldBlock->next = block->next;

	Block* newBlock = block;
	newBlock->size = req_size;
	newBlock->free = false;
	newBlock->next = oldBlock;
	newBlock->prev = block->prev;
	oldBlock->prev = newBlock;

	return newBlock->data();
}

void FirstFitLinkedListAllocator::coalesce_blocks(Block* block)
{
	// Check if can merge with next block.
	Block* nextBlock = block->next;
	if (nextBlock && nextBlock->free)
	{
		block->next = nextBlock->next;
		block->size += nextBlock->size + sizeof(Block);
		if (nextBlock->next)
		{
			nextBlock->next->prev = block;
		}
	}

	// Check if can merge with previous block.
	Block* prevBlock = block->prev;
	if (prevBlock && prevBlock->free)
	{
		prevBlock->next = block->next;
		prevBlock->size += block->size + sizeof(Block);
		if (block->next)
		{
			block->next->prev = prevBlock;
		}
	}
}

} // namespace HeapAllocator
