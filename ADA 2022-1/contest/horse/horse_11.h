#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

class Horse
{
private:

	vector<vector<int>> t;
	vector<vector<int>> ops;
	
	int N;
	int NCUAD;
	int VAR_X;
	int VAR_Y;
	int filas;
	int columnas;

	//int h[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
	//int v[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };
	
	int h[8] = { 1, 1, -1, -1, 2, 2,  -2,  -2 };
	int v[8] = { 2, -2,  2,  -2, 1, -1, 1, -1 };

	vector<int> iter = {0};

public:
	Horse(int _x, int _y, int _N)
	{
		N = _N;
		NCUAD = N * N;

		VAR_X = _x;
		VAR_Y = _y;

		filas = N;
		columnas = N;

		t.assign(filas, vector<int>(columnas, 0));
	}

	void printMatrix(vector<vector<int>> Matriz)
	{
		//int col = Matriz[0].size();
		//int row = Matriz.size();

		int col = N;
		int row = N;

		for (int i = 0; i < row; i++)
		{
			
			//cout << "  " << i << "|";
			for (int j = 0; j < col; j++)
			{
				printf("\t%i", Matriz[i][j]);
				//cout << "\t" << Matriz[i][j];
			}
			printf("\n");
			//cout << endl;
		}
	}

	void counter(int x, int y, vector<vector<int>> &ops) //usamos los movimientos posibles para el caballo
	{
		int xn1;
		int yn1;
		int xn2;
		int yn2;

		for (int i = 0; i < 8; i++ )
		{
			xn1 = x + h[i];
			yn1 = y + v[i];
			if ( (xn1 >= 0) && (xn1 < N) && (yn1 >= 0) && (yn1 < N) )
			{
				if (t[xn1][yn1] == 0)
				{
					ops.push_back({ 0,i });
					for(int j = 0; j < 8; j++ )
					{
						xn2 = xn1 + h[j];
						yn2 = yn1 + v[j];
						if ((xn2 >= 0) && (xn2 < N) && (yn2 >= 0) && (yn2 < N)) 
						{
							if (t[xn2][yn2] == 0)
							{
								//cout << "Entra en la suma" << endl;
								ops[ops.size()-1 ][0] += 1;
								//cout << "ops[][0]: "  << ops[ops.size()-1][0] << endl;
							} 
						}
					}
				}
			}
		}

		sort(ops.begin(), ops.end());

		/*
		for (int i = 0; i < ops.size(); i++) {
			cout << ops[i][0] << " " << ops[i][1] << endl;
		}
		cout << endl;
		*/
	}

	void Tenta(int i, int x, int y, vector<bool> q)
	{
		static int xn;
		static int yn;

		ops.clear();
		//vector<vector<int>>().swap(ops);
		counter(x, y, ops);

		int m = 0;
		
		q[0] = 0;
		
		//while ((-1 * q[0] - 1 == -1) && (m < ops.size()))
		while (( ~q[0] == -1) && (m < ops.size()))
		{
			//cout << "entra al while" << endl;
			xn = x + h[ops[m][1]];
			yn = y + v[ops[m][1]];
			if ((xn < N) && (yn < N))
			{
				if (t[xn][yn] == 0)
				{
					t[xn][yn] = i;
					if (i < NCUAD)
					{
						Tenta(i + 1, xn, yn, q);
						
						//if (-1 * q[0] - 1 == -1)
						if (~q[0] == -1)
						{
							t[xn][yn] = 0;
						}
					}
					else
					{
						q[0] = 1;
					}
				}
			}	
			m +=1;
            iter[0] += 1; 
		}
	}
	
	void PasoDelCaballo()
	{
		vector<bool> q = { false };
		t[VAR_X][VAR_Y] = 1;

		Tenta(2,VAR_X, VAR_Y,q);
		printMatrix(t);
	}
};

void horse01aux(int x, int y, int n) //no usamos esta
{
	Horse horse(x, y, n);
	horse.PasoDelCaballo();	
}

long long int horse_11(int n, int x, int y)
{
	auto millisec_start_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	Horse horse(x, y, n);
	horse.PasoDelCaballo();

	auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	cout << "time horse: " << millisec_end_epoch - millisec_start_epoch << endl;
	return millisec_end_epoch - millisec_start_epoch;
}