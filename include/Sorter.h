//
// Created by dima on 18.02.18.
//


#ifndef STRING_CLASS_CPP_SORTER_H
#define STRING_CLASS_CPP_SORTER_H

#include "stdlib.h"
#include  <algorithm>
template <typename T>
class Sorter {
public:
    virtual void sort(T* a, size_t size) = 0;
};

template <typename T>
class MergeSorter : public Sorter<T>{
    static void merge_sort(T * array, size_t size);
    static T* merge(T *a, size_t size_a, T *b, size_t size_b);
public:
    void sort(T* a, size_t size) override;
};
#include "MergeSorter.cpp"


template <typename T>
class HeapSorter : public Sorter<T>{
    static void heapify(T *a, int size, int i);
    static void buildHeap(T *a, int size);
public:
    void sort(T* a, size_t size) override;
};
#include "HeapSorter.cpp"


template <typename T>
class BubbleSorter : public Sorter<T>{
public:
    void sort(T* a, size_t size) override;
};
#include "BubbleSorter.cpp"


template <typename T>
class InsertionSorter : public Sorter<T>{
    static int binary_search(T* a, size_t size, T value);
public:
    void sort(T* a, size_t size) override;
};
#include "InsertionSorter.cpp"


template <typename T>
class SelectionSorter : public Sorter<T>{
public:
    void sort(T* a, size_t size) override;
};
#include "SelectionSorter.cpp"


#endif //STRING_CLASS_CPP_SORTER_H
