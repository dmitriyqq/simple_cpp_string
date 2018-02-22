//
// Created by dima on 18.02.18.
//

#include <Sorter.h>
#include <cstring>
#include <ctime>
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
    constexpr int kSize = 100;
    constexpr int kNumSorters = 5;

    int sample[kSize];

    for(int i = 0; i < kSize; i++){
        sample[i] = rand();
    }

    Sorter<int>* sorters[5] = {
        new InsertionSorter<int>(),
        new SelectionSorter<int>(),
        new BubbleSorter<int>(),
        new HeapSorter<int>(),
        new MergeSorter<int>()
    };


    float t[5];
    bool c[5];

    for(int i = 0; i < kNumSorters; i++){
        c[i] = test<int>(sorters[i], sample, kSize, t+i);
    }

    printf("Insertion sort: %s, time = %f\n", (c[0]? "correct" : "failed"), t[0]);
    printf("Selection sort: %s, time = %f\n", (c[1]? "correct" : "failed"), t[1]);
    printf("Bubble sort: %s, time = %f\n", (c[2]? "correct" : "failed"), t[2]);
    printf("Heap sort: %s, time = %f\n", (c[3]? "correct" : "failed"), t[3]);
    printf("Merge sort: %s, time = %f\n", (c[4]? "correct" : "failed"), t[4]);

    for(int i = 0; i < kNumSorters; i++){
        delete sorters[i];
    }

}
