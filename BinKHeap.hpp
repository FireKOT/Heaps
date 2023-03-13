#ifndef _BINKHEAP_HPP_
#define _BINKHEAP_HPP_


#include <stdio.h>


struct KHeap {

    int *data;
    int size;
    int k;
};  


void HeapSort   (int *array, int size, int k);

void SiftDown    (KHeap *heap, int id);
void SiftDownBin (KHeap *heap, int id); 
void ExtractMax  (KHeap *heap);
void BuildHeap   (KHeap *heap);

void Swap (void *val1, void*val2, size_t size);


#endif