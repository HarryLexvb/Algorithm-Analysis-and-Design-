#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

struct coord {
    int x;
    int y;

    coord() {
        x = 0; y = 0;
    }
    coord(int x1, int y1) :
        x(x1), y(y1) {  };
};

coord operator + (coord x1, coord y1)
{
    return coord(x1.x + y1.x, x1.y + y1.y);
}

class board {
public:
    int n;
    int** brd;
    int xmoves[8] = { -2,-1,1,2,2,1,-1,-2 };
    int ymoves[8] = { 1,2,2,1,-1,-2,-2,-1 };
    int number = 1;
    coord initial;

    board(int n1) :
        n(n1)
    {
        brd = new int* [n * n];
        for (int i = 0; i < n; i++) {
            brd[i] = new int[n];
            for (int j = 0; j < n; j++)
                brd[i][j] = -1;
        }
    }

    bool IsPosible(coord nc) {
        if (nc.x >= 0 && nc.x < n && nc.y >= 0 && nc.y < n && brd[nc.x][nc.y] == -1)
            return true;
        return false;
    }

    int nPossibles(coord nc) {
        int cont = 0;
        coord nc1(0, 0);
        for (int i = 0; i < 8; i++) {
            nc1.x = nc.x + xmoves[i];
            nc1.y = nc.y + ymoves[i];
            if (IsPosible(nc1))
                cont++;
        }
        return cont;
    }

    bool warnsdorff(coord& coordini)
    {
        if (number >= n * n) {
            return 1;
        }

        coord nc1(0, 0);
        bool visited[8] = { 0,0,0,0,0,0,0,0 };
        int it = 0, temp = 0;

        coord n_xy(0, 0);
        int min = 9;
        for (int j = 0; j < 8; j++) {
            for (int i = 0; i < 8; i++) {
                nc1.x = coordini.x + xmoves[i];
                nc1.y = coordini.y + ymoves[i];
                if (!IsPosible(nc1)) {
                    continue;
                }
                int temp = nPossibles(nc1);
                if (min > temp && visited[i] == 0 && brd[nc1.x][nc1.y] == -1) {
                    n_xy = nc1;
                    min = temp;
                    it = i;
                }
            }
            if (min == 9)
                break;
            visited[it] = 1;
            min = 9;
            brd[n_xy.x][n_xy.y] = number;
            number++;
            if (warnsdorff(n_xy) == 1) {
                coordini = n_xy;
                return 1;
            }
            else {
                brd[n_xy.x][n_xy.y] = -1;
                number--;
            }
        }
        return 0;
    }

    void solve(coord& nc)
    {
        if (n > 4) {
            warnsdorff(nc);
            return;
        }
    }

    void print() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                std::cout << brd[i][j] << "\t";
            std::cout << "\n\n";
        }
    }

    ~board() {
        for (int i = 0; i < n; i++)
            delete[] brd[i];
        delete[] brd;
    }
};

long long horse_1(int n, int x, int y)
{
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    board mb(n);
    coord pc(x, y);
    mb.brd[x][y] = 0;
    mb.solve(pc);
    mb.print();

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
}
