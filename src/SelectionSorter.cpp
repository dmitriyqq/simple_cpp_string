//
// Created by dima on 18.02.18.
//

#include "Sorter.h"

void SelectionSorter::sort(int* a, size_t size) {
    for(int i = 0; i < size; i++){
        int m = i;
        for(int j = i+1; j < size; j++){
            if(a[j] < a[m]){
                m = j;
            }
        }
        int t = a[i];
        a[i] = a[m];
        a[m] = t;
    }
}