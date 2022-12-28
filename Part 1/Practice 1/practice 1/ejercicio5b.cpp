#include <iostream>
using namespace std; 

int maxSuma(int *a, int n){

    int r = 0, t = a[0], p = 0, q = 0;  ////  C

    for (int i = 1; i < n; ++i){        ////  n
        t += *(a+i);                    ////  n
        if(t > r){                      ////  n
            r = t;                      ////  n
            q = i;                      ////  n
        }else if (t < 0){               ////  n
            t = 0;                      ////  n
            p = i + 1;                  ////  n
        }                               ////  n
    }                                   ////  n
    
    return r;                           ////  C
}

int main(){
    //int A[11] = {31, -41, 59, 26, -53, 58, 97, -93, -23, 84}, n = 11;
    //int A[11] = {0, 0, 0, 0, 0, 0, 0, 0, -1, 1}, n = 11; 
    //int A[11] = {1, 1, 1, 1, 1, 1, 0, 1, -1, 2}, n = 11;
    //int A[11] = {−1, 1, −1, 1, −1, 1, −1, 1, −1, 1000}, n = 11;
    //int A[11] = {23, 1, 12, 11, 41, 22, 18, 4, 2, 6}, n = 11;
    cout << maxSuma(A, n);
}