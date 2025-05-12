#pragma once

#include <cstdint>
#include <cstddef>

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

class Heap
{
public:
    Heap(size_t heap_size = DEFAULT_HEAP_SIZE);
    ~Heap();

    void* allocate(size_t size);
    bool deallocate(void* ptr);

    // Find first block with requested size. Convenient for finding blocks to deallocate.
    void* findFirstBlock(size_t blockSize);
    void print();

private:
    Block* findFirstFreeBlock();
    void* split_block(Block* block, size_t req_size);
    void coalesce_blocks(Block* block);

    Block* head;
    size_t heap_size_;
    size_t block_size_;
};
