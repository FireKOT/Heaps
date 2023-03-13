#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

#include "heaps.hpp"


void HeapSort (int *array, int size, int k) {

    KHeap heap {

        .data = array,
        .size = size,
        .k    = k,
    };

    BuilHeap(&heap);

    for (int i = 0; i < size; i++) {

        ExtractMax(&heap);
    }
}

void SiftDown (KHeap *heap, int id) {

    if (id * heap->k + 1 >= heap->size) return;

    int max = heap->data[id * heap->k + 1];
    int nextid = id * heap->k + 1;

    for (int i = 2; i <= heap->k; i++) {

        if (id * heap->k + i < heap->size && heap->data[id * heap->k + i] > max) {

            max = heap->data[id * heap->k + i];
            nextid = id * heap->k + i;
        }
    }

    if (heap->data[id] < max) {

        Swap(&heap->data[id], &heap->data[nextid], sizeof(int));

        SiftDown(heap, nextid);
    }
}

void ExtractMax (KHeap *heap) {

    (heap->size)--;
    Swap(&heap->data[0], &heap->data[heap->size], sizeof(int));

    SiftDown(heap, 0);
}

void BuilHeap (KHeap *heap) {

    for (int i = (heap->size - 2) / heap->k; i >= 0; i--) {

        SiftDown(heap, i);
    }
}

void Swap (void *val1, void*val2, size_t size) {

    void *buff = calloc(1, size);

    memcpy(buff, val1, size);
    memcpy(val1, val2, size);
    memcpy(val2, buff, size);

    free(buff);
}