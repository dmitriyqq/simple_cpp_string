//
// Created by dima on 07.02.18.
//
template <typename T>
void HeapSorter<T>::sort(T* a, size_t size) {
    buildHeap(a, size);
    while(size > 1){
        size--;
        std::swap(a[0], a[size]);
        heapify(a, size, 0);
    }
}
template <typename T>
void HeapSorter<T>::heapify(T* a, int size, int i){
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
template <typename T>
void HeapSorter<T>::buildHeap(T* a, int size){
    for(int i = size/2-1; i >=0; i--){
        heapify(a,size,i);
    }
}
