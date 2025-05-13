#pragma once

#include "LinkedListHeapAllocator.hpp"


namespace HeapAllocator
{

class FirstFitLinkedListAllocator : public LinkedListHeapAllocator
{
public:
    FirstFitLinkedListAllocator(size_t heap_size = DEFAULT_HEAP_SIZE);
    virtual ~FirstFitLinkedListAllocator();

    virtual void* allocate(size_t size) override;
    virtual bool deallocate(void* ptr) override;

    virtual void print() const override;

private:
    Block* findFirstFreeBlock();
    void* split_block(Block* block, size_t req_size);
    void coalesce_blocks(Block* block);
};

} // namespace HeapAllocator
