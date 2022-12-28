#pragma once
#include <iostream>
#include <vector>

#include <chrono>
#include <ctime>

using namespace std;
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

class Point
{
public:

	int x, y;
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	void copyPoint(Point pt){
		x = pt.x;
		y = pt.y; 
	}
	void set(int a, int b){
		x=a;
		y=b;
	}
};


class Queens
{
private:
	int x, y, N;
	int count;
	int numberOfCells;
	vector <int> queens;
	vector<int> ln;
	vector<int> cl;

public:
	Queens(int _x, int _y, int _N)
	{
		count = _N;
		numberOfCells = (_N + 1) * (_N + 1);

		queens.assign(numberOfCells, 0);
		ln.assign(numberOfCells, 0);
		cl.assign(numberOfCells, 0);

		x = _x;
		y = _y;
		N = _N;
	}

	bool checkDiagonal(int x, int y, int a, int b){
		if ((x < 0) || (y < 0) || (x >= count) || (y>= count)){
			return true;
		} 
		if (queens[x + (y * count)])
			return false;
		if (checkDiagonal(x + a, y + b, a, b))
			return true;
		return false;
	}

	bool check(int x, int y)
	{
		if (ln[y] || cl[x])
			return false;
		if (!(checkDiagonal(x, y, -1, -1)))
			return false;
		if (!(checkDiagonal(x, y, 1, -1)))
			return false;
		if (!(checkDiagonal(x, y, -1, 1)))
			return false;
		if (!(checkDiagonal(x, y, 1, 1)))
			return false;
		return true;
	}

	bool putQueens(Point pnt, int size)
	{
		int i = count;
		while (i > 0)
		{
			if (!(size))
			{
				return true;
			}
			if (check(pnt.x, pnt.y)) {
				queens[pnt.x + (pnt.y * count)] = true;
				cl[pnt.x] = true;
				ln[pnt.y] = true;
				Point temp(pnt.x,pnt.y);
				// temp.copyPoint(pnt);
				temp.x += 1;
				if (temp.x >= count)
					temp.x = 0;
				temp.y += 1;
				if (temp.y >= count)
					temp.y = 0;
				if (putQueens(temp, size - 1))
					return true;
				queens[pnt.x + pnt.y * count] = false;
				cl[pnt.x] = false;
				ln[pnt.y] = false;
			}
			pnt.x += 1;
			if (pnt.x >= count)
				pnt.x = 0;
			
			i = i - 1;
		}
		return false;

	}

	void displayBoard(){
		string line = "";
		//cout << "size de queens: " << queens.size() << endl;
		for(int i = 0; i < queens.size() - count*2; i++)
		{
			if( i % count == 0 )
			{	
				//printf("%s\n",line);
				cout << line << endl;
				line = "";
			}
			if (queens[i])
			{
				line += "X ";
			} 
			else {
				line += ". ";
			}
		}
	}

	void solve()
	{
		Point point(x,y);
		putQueens(point, N);
		displayBoard();
	}
};

void nqueens01(int x, int y, int n) //no usamos esta
{
	Queens reina(x,y,n);
	reina.solve();
}

long long int nqueens_11(int n, int x, int y)
{
	auto millisec_start_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	Queens reina(x, y, n);
	reina.solve();

	auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	cout << "time queens: " << millisec_end_epoch - millisec_start_epoch << endl;
	return millisec_end_epoch - millisec_start_epoch;
}