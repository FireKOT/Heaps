#ifndef _WEAKHEAP_HPP_
#define _WEAKHEAP_HPP_


#include <stdio.h>


struct WeakHeap {

    int *data;
    int size;
    int *isswitch;
};  


void WeakHeapSort (int *array, int size);
void BuildHeap    (WeakHeap *heap);

void Swap (void *val1, void*val2, size_t size);


#endif