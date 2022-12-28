#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

void delet(char** arr, int n) {
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

void print(char** arr,int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << arr[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

/*SE USA DESPUES DE PASAR A LA REINA DE LA POSICION(X,Y), YA NO HAY REINAS ADELANTE*/
bool check(char** arr, int i, int j, int n) {
	for (int i1 = 0; i1 < j; i1++) {
		if (arr[i][i1] == 'x')
			return 0;
	}

	for (int i1 = i, j1 = j; i1 >= 0 && j1 >= 0; i1--, j1--){
		if (arr[i1][j1] == 'x')
			return 0;
	}

	for (int i1 = i, j1 = j; i1 <n && j1 >= 0; i1++, j1--) {
		if (arr[i1][j1] == 'x')
			return 0;
	}

	return 1;
}

/*SE USA CUANDO LA REINA DE LA POSICION(X,Y) AUN ESTA ADELANTE DE LA COLUMNA J*/
bool check2(char** arr, int i, int j, int n, int x, int y) {
	
	if (!check(arr, i, j, n))
		return 0;

	for (int i1 = i; i1 <= y; i1++) {
		if (arr[i][i1] == 'x')
			return 0;
	}

	for (int i1 = i + (x - i), j1 = j + (x - i); i1 >= i && j1 >= j; i1--, j1--) {
		if (arr[i1][j1] == 'x')
			return 0;
	}

	for (int i1 = i + (x - i), j1 = j - (x - i); i1 < n && j1 >= j; i1++, j1--) {
		if (arr[i1][j1] == 'x')
			return 0;
	}

	return 1;
}

//recorre las columnas en orden y checkea las filas y diagonales pare ver donde poner la reina
bool solve(char** arr, int j, int n,int x, int y) {
	if (j >= n || (j==y && j==n-1))
		return 1;
	if (j == y)
		j++;
	for (int i = 0; i < n; i++) {
		if (j > y) {
			if (check(arr, i, j, n)) {
				arr[i][j] = 'x';
				if (solve(arr, j + 1, n, x, y))
					return 1;
				arr[i][j] = '0';
			}
		}
		else {
			if (check2(arr, i, j, n,x,y)) {
				arr[i][j] = 'x';
				if (solve(arr, j + 1, n, x, y))
					return 1;
				arr[i][j] = '0';
			}
		}
	}
	return 0;
}

long long nqueens_1(int n, int x, int y) {
	auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	char** arr = new char* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new char[n];
		for (int j = 0; j < n; j++) {
			arr[i][j] = '0';
		}
	}
	arr[x][y] = 'x';
	solve(arr, 0, n, x, y);
	print(arr, n);
	delet(arr, n);
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
}
