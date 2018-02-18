//
// Created by dima on 07.02.18.
//

#include "Sorter.h"

void HeapSorter::sort(int* a, size_t size) {
    buildHeap(a, size);
    while(size > 1){
        size--;
        std::swap(a[0], a[size]);
        heapify(a, size, 0);
    }
}

void HeapSorter::heapify(int *a, int size, int i){
    int l = 2*i+1;
    int r = 2*i+2;
    int mi;
    if(l < size && r < size){
        if(a[l] > a[r]){
            mi = l;
        }else{
            mi = r;
        };
    }else if(l < size){
        mi = l;
    }else{
        return;
    }


    if(a[i] < a[mi]) {
        std::swap(a[mi], a[i]);
        heapify(a, size, mi);
    }
}

void HeapSorter::buildHeap(int* a, int size){
    for(int i = size/2-1; i >=0; i--){
        heapify(a,size,i);
    }
}
