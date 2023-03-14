#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

#include "weakheap.hpp"


void WeakHeapSort (int *array, int size) {

    WeakHeap heap {

        .data     = array,
        .size     = size,
        .isswitch = (int*) calloc(size, sizeof(int)),
    };

    BuildHeap(&heap);

    for (int i = size-1; i > 1; i--) {

        Swap(&heap.data[0], &heap.data[i], sizeof(int));

        int idnew = 1;
        while (idnew * 2 + heap.isswitch[idnew] < i) {

            idnew = idnew * 2 + heap.isswitch[idnew];
        }

        while (idnew > 0) {

            if (heap.data[0] < heap.data[idnew]) {

                heap.isswitch[idnew] = 1 - heap.isswitch[idnew];

                Swap(&heap.data[0], &heap.data[idnew], sizeof(int));
            }

            idnew /= 2;
        }
    }

    Swap(&heap.data[0], &heap.data[1], sizeof(int));
}

void BuildHeap (WeakHeap *heap) {

    for (int i = heap->size - 1; i > 0; i--) {

        int j = i;

        while ((j & 1) == heap->isswitch[j / 2]) {
            
            j /= 2;
        }

        if (heap->data[i] > heap->data[j / 2]) {

            heap->isswitch[i] = 1 - heap->isswitch[i];

            Swap(&heap->data[i], &heap->data[j / 2], sizeof(int));
        }
     }
}

void Swap (void *val1, void*val2, size_t size) {

    void *buff = calloc(1, size);

    memcpy(buff, val1, size);
    memcpy(val1, val2, size);
    memcpy(val2, buff, size);

    free(buff);
}