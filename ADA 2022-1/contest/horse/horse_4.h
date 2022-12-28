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

#define v vector<int>

v fila = { 2, 1, -1, -2, -2, -1, 1, 2, 2 };
v colum = { 1, 2, 2, 1, -1, -2, -2, -1, 1 };

bool esValido(int x, int y, int n)
{
	if (x < 0 || y < 0 || x >= n || y >= n)
		return false;
	return true;
}
void printTab(v vect, int n)
{
	int a;
}

void horse_walk(v& vect, int n, int x, int y, int pos, bool& termino)
{
	vect[(x*n)+y] = pos;

	if (pos >= n * n)
	{
		for (int i = 0; i < n*n; i++)
		{
			cout << vect[i] << "\t";
			if ((i + 1) % n == 0)
				cout << endl;
		}
		cout << endl;
		termino = true;
		return;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			int newx = x + fila[i];
			int newy = y + colum[i];

			if (esValido(newx, newy, n) && !vect[(newx * n) + newy])
			{
				horse_walk(vect, n, newx, newy, pos + 1, termino);
				if (termino)
					break;
			}		
		}
		vect[(x*n)+y] = 0;
	}
	
}
long long int horse_4(int n, int x, int y)
{
	auto mini = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	v tablero(n*n);

	for (int i = 0; i < n*n; i++)
		tablero[i] = 0;

	bool termino = false;
	horse_walk(tablero, n, x, y, 1,termino);

	if (!termino)
		cout << "No hay solución" << endl;

	auto mfin = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	long long int total = mfin - mini;

	return total;
}