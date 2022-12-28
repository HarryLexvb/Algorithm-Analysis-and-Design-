#include <math.h>
#include<iostream>
using namespace std;
#include <ctime>
#include <chrono>


int solveKTUtil(int x, int y, int movei, int** sol, int N, int xMove[], int yMove[]);
int isSafe(int x, int y, int** sol, int N)
{
    return (x >= 0 && x < N&& y >= 0 && y < N
        && sol[x][y] == -1);
}


void printSolution(int** sol, int N)
{
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++)
            cout << " " << " " << sol[x][y] << " ";
        cout << endl;
    }
}

int solveKT(int N, int x, int y)
{
    int** sol = new int* [N];
    for (int x = 0; x < N; x++) {
        sol[x] = new int[N];

    }

    
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;


    int xMove[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    int yMove[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };


    sol[x][y] = 0;


    if (solveKTUtil(0, 0, 1, sol, N, xMove, yMove) == 0) {
        cout << "Solution does not exist";
        return 0;
    }
    else
        printSolution(sol, N);

    return 1;
}


int solveKTUtil(int x, int y, int movei, int** sol, int N, int xMove[8], int yMove[8])
{
    int k, next_x, next_y;
    if (movei == N * N)
        return 1;

    for (k = 0; k < 8; k++) {
        next_x = x + xMove[k];
        next_y = y + yMove[k];
        if (isSafe(next_x, next_y, sol, N)) {
            sol[next_x][next_y] = movei;
            if (solveKTUtil(next_x, next_y, movei + 1, sol, N, xMove, yMove) == 1)
                return 1;
            else

                
                sol[next_x][next_y] = -1;
        }
    }
    return 0;
}

int main()
{
    auto start = chrono::system_clock::now();
    int x,y,z;
    cin>>x;
    cin>>y; 
    cin>>z;
    solveKT(x, y, z);
    auto end = chrono::system_clock::now();
    chrono::duration<float, milli> duration = end - start;
    long long int tim = (long long int)duration.count();
    cout<<tim<<endl;
    return 0;
}

