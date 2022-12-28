#include<iostream>
#include<stdlib.h>
#include <ctime>
#include <chrono>

using namespace std;

void printSolution(int** matriz, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] == 0) {
                cout << "x ";
            }
            else {
                cout << "Q ";
            }

        }
        cout << endl;
    }

}


bool isSafe(int** matriz, int r, int i, int N) {
    for (int j = 0; j < N; j++) {
        if (matriz[j][i] == 1)
            return 0;
    }
    for (int j = 0; j < N; j++) {
        if (matriz[r][j] == 1)
            return 0;
    }
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            if (((matriz[j][k]) == 1) && ((j + k == r + i) || (j - k == r - i)))
                return 0;
        }
    }
    return 1;
}

bool solveNQUtil(int** matriz, int r, int x, int y, int N) {
    if (r == N && matriz[x][y] == 1) {
        printSolution(matriz, N);
        return 0;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(matriz, r, i, N) or (x == r and y == i)) {
            matriz[r][i] = 1;
            int l = solveNQUtil(matriz, r + 1, x, y, N);
            if (l == 0)
                return 0;
            if (x != r and y != i)
                matriz[r][i] = 0;
        }

    }
    return 1;
}
void nqueens(int n, int x, int y) {

    int** matriz = new int* [n];
    for (int x = 0; x < n; x++) {
        matriz[x] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = 0;
        }
    }
    matriz[x][y] = 1;

    solveNQUtil(matriz, 0, x, y, n);


}

int main()
{
    auto start = chrono::system_clock::now();
    int x,y,z;
    cin>>x;
    cin>>y; 
    cin>>z;
    nqueens(x, y, z);
    auto end = chrono::system_clock::now();
    chrono::duration<float, milli> duration = end - start;
    long long int tim = (long long int)duration.count();
    cout<<tim<<endl;
    return 0;
}