#include <stdio.h>
#include <time.h>
#include <cstdlib>

#include "BinKHeap.hpp"


void TestKHeapSort (int k, const char *file_name);


int main () {
    
    TestKHeapSort(5, "Bin5HeapData.txt");
    TestKHeapSort(10, "Bin10HeapData.txt");
    TestKHeapSort(25, "Bin25HeapData.txt");
    TestKHeapSort(50, "Bin50HeapData.txt");
    TestKHeapSort(100, "Bin100HeapData.txt");
    TestKHeapSort(200, "Bin200HeapData.txt");
    TestKHeapSort(300, "Bin300HeapData.txt");
    TestKHeapSort(400, "Bin400HeapData.txt");
    TestKHeapSort(500, "Bin500HeapData.txt");
    TestKHeapSort(1000, "Bin1000HeapData.txt");

    return 0;
}


void TestKHeapSort (int k, const char *file_name) {

    for (int i = 10000; i <= 1000000; i += 10000) {

        double time = 0;
        for (int j = 0; j < 5; j++) {

            int *array = (int*) calloc(i, sizeof(int));

            for (int q = 0; q < i; q++) {

                array[q] = 0;
                for (int b = 0; b < 4; b++) {

                    array[q] *= 256;
                    array[q] += rand() % 256;
                }
            }

            clock_t time_start = clock();
            HeapSort(array, i, k);
            clock_t time_end   = clock();

            time += 1000.0 * (time_end - time_start) / CLOCKS_PER_SEC;

            free(array);
        }

        FILE *output = fopen(file_name, "a");

        fprintf(output, "%d %lg\n", i, time / 5);

        fclose(output);
    }
}

