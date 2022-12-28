#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <ctime>

using namespace std;
using chrono::duration_cast;
using chrono::milliseconds;
using chrono::seconds;
using chrono::system_clock;

#define vv vector<vector<int>> 
#define v vector<int>
/* recorrer la matriz gastaria tiempo
int getQueens(vector<vector<int>>& tablero)
{
    int q = 0;
    vector<vector<int>>::iterator it = tablero.begin();
    vector<int>::iterator it2;
    for (; it != tablero.end(); ++it)
    {
        for (it2 = (*it).begin(); it2 != (*it).end(); ++it2)
        {
            if ((*it2))
                q++;
        }
    }
    return q;
}*/

int queens1 = 0;

void printTablero(v& tablero, int n)
{
    v::iterator it = tablero.begin();
    int cont = 1;
    for (; it != tablero.end(); ++it)
    {
        if (!(*it))
            cout << ".\t";
        else
        {
            cout << "X\t";
            ++queens1;
        }
        if(cont%n==0)
            cout << endl;
        cont++;
    }
    cout << endl;
}

bool esseguro(v& tablero, int r, int i, int n)
{
    for (int j = n - 1; j >= 0; --j)
    {
        if (tablero[(n*j)+i])
            return false;
    }
    for (int j = n - 1; j >= 0; --j)
    {
        if (tablero[(r*n)+j])
            return false;
    }
    for (int j = n - 1; j >= 0; --j)
    {
        for (int k = n - 1; k >= 0; --k)
        {
            if ((tablero[(j*n)+k]) && ((j + k == r + i) || (j - k == r - i)))
                return false;
        }
    }
    return true;
}

bool solucion(v& tablero, int r, int x, int y, int n)
{
    if (r == n && tablero[(x*n)+y])
    {
        printTablero(tablero,n);
        return 0;
    }
    for (int i = n - 1; i >= 0; --i)
    {

        if (esseguro(tablero, r, i,n) || (x == r && y == i))
        {
            tablero[(r*n) + i] = 1;
            bool l = solucion(tablero, r + 1, x, y,n);
            if (!l) return false;
            if (x != r && y != i)
                tablero[(r*n)+i] = 0;
        }
    }
}

long long int nqueens_4(int n, int x, int y)
{
    auto mini = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    v tablero(n * n);
    for (int i = 0; i < tablero.size(); i++)
        tablero[i] = 0;

    tablero[(x*n)+y] = 1;
    solucion(tablero, 0, x, y,n);
    //if (getQueens(tablero) != tablero.size())
    if (queens1 != n)
        cout << "No hay solucion";

    auto mfin = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    long long int total = mfin - mini;

    return total;
}
