#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <setjmp.h>


jmp_buf env;
int x,y;

using namespace std;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
// tamano del tablero
#define N 1000

// Se amenazan o no
bool noSeAmenazan(char tab[][N], int r, int c,int n)
{
	// si comparten la misma columna
    for (int i = 0; i < n; i++)
		if (tab[i][c] == 'X')
			return false;
    
    // si comparten la misma fila
    for (int i = 0; i < n; i++)
		if (tab[r][i] == 'X')
			return false;

    // revisamos diagonales
    for(int p=0; p < n; p++){
        for(int q=0; q < n; q++){
            if((tab[p][q] == 'X' ) && ((p+q == r+c) || (p-q == r-c))){
                return false;
            }
        }
    }
	return true;
}

void backtracking(char tab[][N], int r,int n)
{
	// si tiene solucion la imprimimos
    if (r == n && (tab[x][y]=='X'))
	{
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++)
				cout << tab[i][j] << "\t";
			cout << endl;
		}
		cout << endl;
        longjmp(env, 1);
	}

    // probamos con la reina en cada fila r
    // y la recorremos si es valida
	for (int c = 0; c < n; c++) 
	{
		// si no se amenazan
        //cout << "R: " << r << " " <<"C: " << c << endl;
		if (noSeAmenazan(tab, r, c,n) || (x==r && y==c)) 
		{
            // le damos la posicion a la reina
			tab[r][c] = 'X';
			// siguiente fila
            backtracking(tab, r + 1,n);
			// backtracking, y sacamos a la ultima reina
            if (x!=r && y!=c)
            {
                tab[r][c] = '.';
            }    
		}
	}
}

long long int nqueens_7(int n,int x,int y){
	auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    
	unsigned t0, t1;
	t0 = clock();
	char tab[N][N];
		
    cout << "x: " << x << " " << "y: " << y << endl;

	// tablero vacio
    for (int i = 0; i <n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            tab[i][j] = '.';
        }
        
    }

    // posicionamos la primera reina
    tab[x][y] = 'X';

    
    if(!setjmp(env)) backtracking(tab, 0,n);
    t1 = clock();
	

    
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
	//return sec_since_epoch;
	//return  millisec_since_epoch;
}

int main()
{
    cout<<nqueens_7(8,0,0)<<endl;
  
    //impresion de la solucion


	return 0;
}
