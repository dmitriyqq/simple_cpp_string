//
// Created by dima on 07.02.18.
//

#include "Sorter.h"
#include <cstring>

void MergeSorter::sort(int* a, size_t size) {
    merge_sort(a, size);
}

int* MergeSorter::merge(int *a, size_t size_a, int *b, size_t size_b){
    int j = 0, i = 0;
    int *new_a = new int[size_a + size_b];
    int c = 0;
    while( i < size_a && j < size_b){
        if(a[i] < b[j]){
            new_a[c++] = a[i++];
        }else{
            new_a[c++] = b[j++];
        }
    }

    while(i < size_a){
        new_a[c++] = a[i++];
    }
    while(j < size_b){
        new_a[c++] = b[j++];
    }
    return new_a;
}

void MergeSorter::merge_sort(int *a, size_t size) {
    if(size > 1) {
        int half = size / 2;

        merge_sort(a, half);
        merge_sort(a + half, size - half);

        int * m = merge(a, half, a+half, size - half);

        memcpy(a, m, size*sizeof(int));
    }
}
