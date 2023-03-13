#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>

#include "BinKHeap.hpp"


void HeapSort (int *array, int size, int k) {

    KHeap heap {

        .data = array,
        .size = size,
        .k    = k,
    };

    BuildHeap(&heap);

    for (int i = 0; i < size; i++) {

        ExtractMax(&heap);
    }
}

void SiftDown (KHeap *heap, int id) {

    int cur_lvl  = (id - 1) / heap->k * heap->k + 1;
    int next_lvl = ((id - 1) / heap->k + 1) * heap->k + 1;
    int idchild1 = cur_lvl + (id - cur_lvl) * 2 + 1; 
    int idchild2 = cur_lvl + (id - cur_lvl) * 2 + 2;
    int idchild3 = id * heap->k + 1;

    int max = 0;
    int nextid = 0;

    if (idchild1 < next_lvl && idchild1 < heap->size) {

        max = heap->data[idchild1];
        nextid = idchild1;
    }
    else if (idchild3 < heap->size){

        max = heap->data[idchild3];
        nextid = idchild3;
    }
    else return;

    if (idchild2 < heap->size && idchild2 < next_lvl && heap->data[idchild2] > max) {

        max = heap->data[idchild2];
        nextid = idchild2;
    }
    if (idchild3 < heap->size && heap->data[idchild3] > max) {

        max = heap->data[idchild3];
        nextid = idchild3;
    }

    if (heap->data[id] < max) {

        Swap(&heap->data[id], &heap->data[nextid], sizeof(int));

        SiftDown(heap, nextid);
    }
}

void SiftDownBin (KHeap *heap, int id) {

    if (id * 2 + 1 >= heap->size) return;

    int max = heap->data[id * 2 + 1];
    int nextid = id * 2 + 1;

    if (id * 2 + 2 < heap->size && heap->data[id * 2 + 2] > max) {

        max = heap->data[id * 2 + 2];
        nextid = id * 2 + 2;
    }

    if (heap->data[id] < max) {

        Swap(&heap->data[id], &heap->data[nextid], sizeof(int));

        SiftDownBin(heap, nextid);
    }
}

void ExtractMax (KHeap *heap) {

    (heap->size)--;
    Swap(&heap->data[0], &heap->data[heap->size], sizeof(int));

    SiftDown(heap, 0);
}

void BuildHeap (KHeap *heap) {

    for (int i = 1; i < heap->size; i += heap->k) {

        KHeap children {
            
            .data = heap->data + i,
            .size = heap->k,
            .k    = 2,
        };

        if (heap->k > heap->size - i) {

            children.size = heap->size - i;
        }

        for (int j = (children.size - 2) / 2; j >= 0; j--) {

            SiftDownBin(&children, j);
        }
    }

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