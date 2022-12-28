#include <iostream>

using namespace std;

void print(int *arr, int b){
    for (int i = 1; i < b; ++i)
        cout << *(arr + i) << " ";
    cout << endl;
}

void algorithm1(int *arr, int suma, int max, int b){ 
    if(suma == 0){
        print(arr, b);
        return;
    }
    for (int i = max; i >= 1; --i){
        if (i > suma)
            continue;
        else if(i <= suma){
            *(arr + b) = i;
            algorithm1(arr, suma - i, i, b + 1);
        }
    }
}

int main(){
    int a = 5, b = 1, arr[300];
    algorithm1(arr, a, a, b);
    /*int b = 7;
    algorithm1(b, b, 1);
    int c = 11;
    algorithm1(c, c, 1);
    int d = 19;
    algorithm1(d, d, 1);
    int e = 23;
    algorithm1(e, e, 1);*/
}