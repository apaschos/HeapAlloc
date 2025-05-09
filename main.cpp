#include <iostream>
// #include <cassert>
// #include <memory>


#include "HeapAlloc.hpp"


int main()
{
    Heap heap(1024);
    heap.allocate(128);
    heap.print();
    heap.allocate(256);
    heap.print();
    void* ptr = heap.allocate(256);
    heap.print();
    heap.deallocate(ptr);
    heap.print();

    return 0;
}
