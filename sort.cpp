//
// Created by dima on 18.02.18.
//
#include <Sorter.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <cstdio>

void printRawArray(int* a, size_t s){
    for(size_t i = 0; i< s; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

template <typename T>
bool test(Sorter<T>* sorter, T * sample, size_t size, float *outTime){
    T output[size], ref[size];

    memcpy(output, sample, size*sizeof(T)); // !TODO REPLACE IT
    memcpy(ref, sample, size*sizeof(T));

    time_t s = clock();
    sorter->sort(output, size);
    time_t e = clock();

    *outTime = (e - s) / (float) CLOCKS_PER_SEC;

    std::sort(ref, ref+size);

    for(size_t i = 0; i < size; i++){
        if(output[i] != ref[i]){
            return false;
        }
    }

    return true;


}

int main(){
    constexpr int kSize = 10000;
    int sample[kSize];

    for(int i = 0; i < kSize; i++){
        sample[i] = rand();
    }

    Sorter<int> *ins, *sel, *bubble, *merge, *heap;

    ins = new InsertionSorter<int>();
    sel = new SelectionSorter<int>();
    bubble = new BubbleSorter<int>();
    heap = new HeapSorter<int>();
    merge = new MergeSorter<int>();

    float t[5]; bool c[5];
    c[0] = test<int>(ins, sample, kSize, t);
    c[1] = test<int>(sel, sample, kSize, t+1);
    c[2] = test<int>(bubble, sample, kSize, t+2);
    c[3] = test<int>(heap, sample, kSize, t+3);
    c[4] = test<int>(merge, sample, kSize, t+4);

    printf("Insertion sort: %s, time = %f\n", (c[0]? "correct" : "failed"), t[0]);
    printf("Selection sort: %s, time = %f\n", (c[1]? "correct" : "failed"), t[1]);
    printf("Bubble sort: %s, time = %f\n", (c[2]? "correct" : "failed"), t[2]);
    printf("Heap sort: %s, time = %f\n", (c[3]? "correct" : "failed"), t[3]);
    printf("Merge sort: %s, time = %f\n", (c[4]? "correct" : "failed"), t[4]);

}
