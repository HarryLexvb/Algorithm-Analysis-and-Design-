#include<iostream>
#include<vector>
#include<stack>
#include<ctime>
#include<chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std;

bool truePosition(int* queens, int x, int k) {
    for (int i = 0; i < k; i++) {
        if (queens[i] == queens[k] || abs(queens[i] - queens[k]) == k - i) {
            return false;
        }
    }
    if (queens[x] == queens[k] || abs(queens[x] - queens[k]) == k - x)//|| abs(queens[x]-queens[k])==abs(x-k)
        return false;
    return true;
}

bool nqueens(int* queens, int n, int k, int x, int y) {
    if (k == n) {
        return true;
    }
    for (int i = 0; i < n; i++) {
        queens[k] = i;
        if (truePosition(queens, x, k)) {
            if (k + 1 == x)
            {
                if (nqueens(queens, n, k + 2, x, y)) {

                    return true;
                }
            }
            else {
                if (nqueens(queens, n, k + 1, x, y)) {

                    return true;
                }
            }
        }
    }
    return false;
}

void printQueens(int* queens, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (queens[i] == j) {
                std::cout << " X ";
            }
            else {
                std::cout << " . ";
            }
        }
        std::cout << std::endl;
    }
}

long long nqueens_6(int n, int x, int y) {

    auto millisec_start_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    //inicia
    int* queens = new int[n];
    queens[x] = y;
    if (n <= 3)
    {
        printf("No tiene solucion!\n");
        auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout << "time maze: " << millisec_end_epoch - millisec_start_epoch << endl;
        return millisec_end_epoch - millisec_start_epoch;
    }
    else {
        nqueens(queens, n, 0, x, y);
        printQueens(queens, n);
        delete[] queens;
        //finaliza

        auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        cout << "Nqueens_6 Time: " << millisec_end_epoch - millisec_start_epoch << endl;
        return millisec_end_epoch - millisec_start_epoch;
    }

}