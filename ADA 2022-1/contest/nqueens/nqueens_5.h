#pragma once
#include <iostream>
#include <chrono>

using std::cout;
using std::endl;

using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::chrono::system_clock;
using std::chrono::duration_cast;

bool ChooseColumns(char**& mat, int r, int n, int x);
bool IsValid(char**& mat, int r, int c, int n);
long long int nqueens_5(const int n, int x, int y);
void PrintTable(char**& mat, int n);

long long int nqueens_5(const int n, int x, int y)
{
    //auto start = steady_clock::now();
     auto start = std::chrono::high_resolution_clock::now();
    int i, j;
    char** mat = new char* [n];
    mat[0] = new char[n * n];
    for (i = 1; i < n; ++i)
        mat[i] = mat[i - 1] + n;

    for (i = 0; i < n; ++i)
        for ( j = 0; j < n; ++j)
            mat[i][j] = '.';

    mat[x][y] = 'x';
    ChooseColumns(mat, (x+1)%n, n, x);
    PrintTable(mat,n);

    
    delete mat[0];
    delete[] mat;

   // auto end = steady_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
std::chrono::duration<double, std::milli> fp_ms = end - start;
   // std::chrono::duration<long long int, std::milli> float_ms = end - start;

    //return float_ms.count();
    return fp_ms.count();
}

bool ChooseColumns(char**& mat, int r, int n, int x)
{
        if(r == x)
          return true;
        for (int c = 0; c < n; ++c)
        {
            if (IsValid(mat, r, c, n))
            {
                mat[r][c] = 'x';

                if(ChooseColumns(mat, (r + 1)%n, n, x))
                  return true;
             
                mat[r][c] = '.';
                
            }
        }
        return false;

}

bool IsValid(char**& mat, int r, int c, int n)
{
  int i, j;
    // fila
    for ( i = 0; i < n; ++i)
        if (mat[r][i] == 'x')
            return false;
    //columna
    for ( i = 0; i < n; ++i)
        if (mat[i][c] == 'x')
            return false;

    // diagonal
  
    for (i = r, j = c; i >= 0 && j >= 0; i--, j--)
  		if (mat[i][j] == 'x')
  			return false;
  
  	for (i = r, j = c; j >= 0 && i < n; i++, j--)
  		if (mat[i][j]== 'x')
  			return false;
  
  	for (i = r, j = c; i >= 0 && j < n; i--, j++)
  		if (mat[i][j]== 'x')
  			return false;
  
  	for (i = r, j = c; j < n && i < n; i++, j++)
  		if (mat[i][j]== 'x')
  			return false;

  return true;
}

void PrintTable(char**& mat, int n)
{  
  for (int i = 0; i < n; i++)
  {
      for (int j = 0; j < n; j++)
          cout << mat[i][j] << "\t";
      cout << endl;
  }
  cout << endl;
}
