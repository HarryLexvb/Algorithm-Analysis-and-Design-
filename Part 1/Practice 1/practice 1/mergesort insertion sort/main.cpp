#include <iostream>
#include <cstdlib>

using namespace std;

int K = 33;

void print(int *arr, int size){
    for(int i = 0; i < size - 1; ++i)
        cout << *(arr+i) << " | ";
}

void insertionSort(int *arr, int p, int r) {
    int i, j;
    int key;
    for (i = p + 1; i <= r; ++i) {
        key = *(arr+i);
        j = i - 1;
        while (j >= p and *(arr+j) > key) {
            arr[j + 1] = *(arr+j);
            --j;
        }
        arr[j + 1] = key;
    }
}

void Merge(int *arr, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;

    int *L = new int[n1 + 1];
    int *R = new int[n2 + 1];

    unsigned i = 0;
    for(; i < n1; ++i)
        L[i] = arr[p + i];

    unsigned j = 0;
    for(; j < n2; ++j)
        R[j] = arr[q + 1 + j];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = j = 0;

    unsigned k = p;
    for(; k <= r; ++k){
        if(L[i] <= R[j])
            arr[k] = L[i++];
        else
            arr[k] = R[j++];
    }
}

void HybridMergesort(int *arr, int p, int r){
    if(r - p < K)
        insertionSort(arr, p, r);
    if(p < r){
        int mid = (r + p) >> 1;
        HybridMergesort(arr, p, mid);
        HybridMergesort(arr, mid + 1, r);
        Merge(arr, p, mid, r);
    }
}

int main(){

    int size = 200, arr[size];

    for(long long i = 0; i < size; ++i)
        *(arr+i) = rand()%size;
    //print(arr, size); cout << endl;
    HybridMergesort(arr, 0, size - 1);
    print(arr, size);
}
