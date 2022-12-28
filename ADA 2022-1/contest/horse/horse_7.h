#include <iostream>
#include <stdio.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sys/time.h>


using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std;

int **t;

const int h[8] = { 2, 1, -1, -2, -2, -1,  1,  2 };
const int v[8] = { 1, 2,  2,  1, -1, -2, -2, -1 };

void imprimir(int N) {
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << t[i][j] << "\t";
		}
		cout << "\n";
	}
}

void Counter(int N,int x, int y, vector< pair<int, int> >& ops) {
	for (int i = 0; i < 8; ++i)
	{
		int xn1 = x + h[i];
		int yn1 = y + v[i];
		if (xn1 >= 0 && xn1 < N && yn1 >= 0 && yn1 < N) {
			if (t[xn1][yn1] == 0) {
				ops.push_back(make_pair(0, i));
				for (int j = 0; j < 8; ++j) {
					int xn2 = xn1 + h[j];
					int yn2 = yn1 + v[j];
					if (xn2 >= 0 && xn2 < N && yn2 >= 0 && yn2 < N) {
						if (t[xn2][yn2] == 0) {
							ops.back().first = ops.back().first + 1;
						}
					}
				}
			}
		}
	}
	sort(ops.begin(), ops.end());
}

void backtracking(int N,int i, int x, int y, int* q) {
	vector< pair<int, int> > ops;
	Counter(N,x, y, ops);
	unsigned int m;
	int xn, yn;
	m = 0;
	*q = 0;
	while (!*q && m < ops.size()) {
		xn = x + h[ops[m].second];
		yn = y + v[ops[m].second];
		if (xn < N && yn < N) {
			if (t[xn][yn] == 0) {
				t[xn][yn] = i;
				if (i < N*N) {
					backtracking(N,i + 1, xn, yn, q);
					if (!*q) {
						t[xn][yn] = 0;
					}
				}
				else *q = 1;
			}
		}
		m = m + 1;
	} 
}

long long int horse_7(int N,int x,int y) {
	int i, j, q;
	auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

	unsigned t0, t1;
	t0 = clock();
	
	t= new int*[N];
	for ( int i=0;i<N;i++ ) {
		t[i] = new int[N];
	}
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			t[i][j] = 0;
		}
	}
	
	t[x][y] = 1;
	
	backtracking(N,2, x, y, &q);
	
	
	
	if (q) {
		
		imprimir(N);
		
	}
	else {
		cout << "No existe solucion" << endl;
	}

	//cout << "seconds since epoch: " << sec_since_epoch << endl;
    //cout << "milliseconds since epoch: " << millisec_since_epoch << endl;
    //return sec_since_epoch;
	//return  millisec_since_epoch;
   return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
}
/*
int main() {
	
	cout<<horse_7(10,1,1);
   

  

    return EXIT_SUCCESS;
	

}*/
