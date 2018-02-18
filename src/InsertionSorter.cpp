//
// Created by dima on 18.02.18.
//

#include "Sorter.h"

void InsertionSorter::sort(int* a, size_t size) {
    for(int k = 1; k < size; k++){
        int c = a[k];
        int i = binary_search(a, k, c);
        for(int j = k; j > i; j--){
            a[j] = a[j-1];
        }
        a[i] = c;
    }
}

int InsertionSorter::binary_search(int* a, size_t size, int value) {
    int l = 0, r = size, m;
    while(r-l > 1){
        m = (r+l)/2;

        if(a[m] > value)
            r = m;
        else
            l = m;
    }

    if(value > a[l])
        return r;
    else
        return l;
}
