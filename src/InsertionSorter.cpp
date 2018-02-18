//
// Created by dima on 18.02.18.
//
template <typename T>
void InsertionSorter<T>::sort(T* a, size_t size) {
    for(int k = 1; k < size; k++){
        T c = a[k];
        int i = binary_search(a, k, c);
        for(int j = k; j > i; j--){
            a[j] = a[j-1];
        }
        a[i] = c;
    }
}
template <typename T>
int InsertionSorter<T>::binary_search(T* a, size_t size, T value) {
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
