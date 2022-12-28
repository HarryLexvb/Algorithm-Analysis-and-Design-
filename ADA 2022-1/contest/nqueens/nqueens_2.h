#include <iostream>
#include <chrono>
#include <ctime>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std;
 
void print(char **board,int tam)
{
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
            cout<<board[i][j]<<"\t";
        cout<<endl;
    }
}

bool seguro(char **board, int row, int col,int tam)
{
	if(board[row][col]=='X') return false;
	for(int i = 0;i<tam;i++){
		if(board[i][col]=='X') 
			return false;
	}
	for(int i = 0;i<tam;i++){
		if(board[row][i]=='X') 
			return false;
	}
	int i,j;
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j]=='X')
            return false;
    }
 
    for (i = row, j = col; j >= 0 && i < tam; i++, j--)
    {
        if (board[i][j]=='X')
            return false;
    }
    
    for (i = row, j = col; j < tam && i >= 0; i--, j++)
    {
        if (board[i][j]=='X')
            return false;
    }
    
    for (i = row, j = col; i < tam && j < tam; i++, j++)
    {
        if (board[i][j]=='X')
            return false;
    }
    
    return true;
}
 
bool resolver(char **board, int row,int x,int tam)
{
	if(row == x) row++;
    if (row >= tam)
        return true;
        
    for (int i = 0; i < tam; i++)
    {
        if (row != x && seguro(board, row, i,tam) )
        {
            board[row][i] = 'X';
            if (resolver(board, row + 1,x,tam) == true)
                return true;
            board[row][i] = '.';
        }
    }
    return false;
}
 
double nqueens_2(int tam, int x,int y)
{
    auto millisec_since_epoch1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    
	char **board = new char*[tam];
    for(int i=0;i<tam;i++){
    	board[i] = new char[tam];
	}
    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < tam; j++)
            board[i][j] = '.';
    }
    board[x][y] = 'X';
    
    if (resolver(board, 0,x,tam) == false)
    {
        cout<<"Solution does not exist"<<endl;
    }
    print(board,tam);
    delete []board;
    
    auto millisec_since_epoch2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    double tiempo = millisec_since_epoch2 - millisec_since_epoch1;
    //cout << "time: " << tiempo << " milisegundos" << endl;
    return tiempo;
}
