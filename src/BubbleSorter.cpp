//
// Created by dima on 18.02.18.
//
template <typename T>
void BubbleSorter<T>::sort(T* a, size_t size) {

    bool is_swapped = true;
    int r = size;

    while (is_swapped){
        is_swapped = false;
        for(int i = 0; i < r-1; i++){
            if(a[i] > a[i+1]){
                is_swapped = true;
                std::swap(a[i], a[i+1]);
            }
        }
        r--;
    }

}

