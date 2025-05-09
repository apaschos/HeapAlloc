#include <iostream>
// #include <cassert>
// #include <memory>


#include "HeapAlloc.hpp"


int main()
{
    Heap heap(1024);
    heap.allocate(128);
    heap.print();

    return 0;
}
