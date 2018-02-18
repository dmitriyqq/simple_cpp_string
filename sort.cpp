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

bool test(Sorter* sorter, int * sample, size_t size, float *outTime){
    int output[size], ref[size];

    memcpy(output, sample, size*sizeof(output[0]));
    memcpy(ref, sample, size*sizeof(ref[0]));

    time_t s = clock();
    sorter->sort(output, size);
    time_t e = clock();

    *outTime = (e - s) / (float) CLOCKS_PER_SEC;

    std::sort(ref, ref+size);

    for(size_t i = 0; i < size; i++){
        if(output[i] != ref[i]){

            printf("REF: \n");
            printRawArray(ref, size);
            printf("OUT: \n");
            printRawArray(output, size);
            
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

    Sorter *ins, *sel, *bubble;

    ins = new InsertionSorter();
    sel = new SelectionSorter();
    bubble = new BubbleSorter();

    float t[3]; bool c[3];
    c[0] = test(ins, sample, kSize, t);
    c[1] = test(sel, sample, kSize, t+1);
    c[2] = test(bubble, sample, kSize, t+2);

    printf("Insertion sort: %s, time = %f\n", (c[0]? "correct" : "failed"), t[0]);
    printf("Selection sort: %s, time = %f\n", (c[1]? "correct" : "failed"), t[1]);
    printf("Bubble sort: %s, time = %f\n", (c[2]? "correct" : "failed"), t[2]);

}
