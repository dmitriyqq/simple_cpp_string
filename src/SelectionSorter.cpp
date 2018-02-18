//
// Created by dima on 18.02.18.
//
template <typename T>
void SelectionSorter<T>::sort(T* a, size_t size) {
    for(int i = 0; i < size; i++){
        int m = i;
        for(int j = i+1; j < size; j++){
            if(a[j] < a[m]){
                m = j;
            }
        }
        std::swap(a[i],a[m]);
    }
}