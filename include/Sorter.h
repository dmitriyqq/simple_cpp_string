//
// Created by dima on 18.02.18.
//

#ifndef STRING_CLASS_CPP_SORTER_H
#define STRING_CLASS_CPP_SORTER_H
#include <vector>

using std::vector;

class Sorter {

public:
    virtual void sort(int* a, size_t size) = 0;
};

class MergeSorter : public Sorter{
    static void merge_sort(int * array, size_t size);
    static int* merge(int *a, size_t size_a, int *b, size_t size_b);
public:
    void sort(int* a, size_t size) override;
};

class HeapSorter : public Sorter{
    static void heapify(int *a, int size, int i);
    static void buildHeap(int *a, int size);
public:
    void sort(int* a, size_t size) override;
};


class BubbleSorter : public Sorter{
public:
    void sort(int* a, size_t size) override;
};

class InsertionSorter : public Sorter{
    static int binary_search(int* a, size_t size, int value);
public:
    void sort(int* a, size_t size) override;
};

class SelectionSorter : public Sorter{
public:
    void sort(int* a, size_t sizev) override;
};




#endif //STRING_CLASS_CPP_SORTER_H
