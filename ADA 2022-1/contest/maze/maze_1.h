#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <queue>
#include <vector>
#include<fstream>
#include<string>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::ifstream;

struct coord {
    int x;
    int y;

    coord() {
        x = 0; y = 0;
    }
    coord(int x1, int y1) :
        x(x1), y(y1) {  };
};

class board {
public:
    int row = 0;
    int col = 0;
    int** brd;
    int number = 1;
    coord initial;

    board(std::string maze) {
        ifstream array(maze);
        if (!array.is_open())
            cout << "Error al abrir el archivo";
  
        std::vector<std::string>elements;
        std::string filas;
        row = 0;
        col = 0;

        while (std::getline(array, filas)) {
            col = 0;
            for (char& x : filas) {
                if (x == 'x') {
                    initial.x = row;
                    initial.y = col;
                }
                col++;
            }
            elements.push_back(filas);
            row++;
        }

        brd = new int* [row * col];
        for (int i = 0; i < row; i++) {
            brd[i] = new int[col];
            std::string tempstr = elements.at(i);
            for (int j = 0; j < col; j++) {
                switch (tempstr[j])
                {
                case '.':
                    brd[i][j] = -1;
                    break;
                case '#':
                    brd[i][j] = -2;
                    break;
                case 'x':
                    brd[i][j] = -3;
                    break;
                case 'y':
                    brd[i][j] = -4;
                    break;
                case ' ':
                    brd[i][j] = -5;
                    break;
                }
            }
        }
    }

    coord next(int i, coord pos)
    {
        switch (i)
        {
        case 0:
            return coord(pos.x + 1, pos.y);
        case 1:
            return coord(pos.x, pos.y + 1);
        case 2:
            return coord(pos.x - 1, pos.y);
        case 3:
            return coord(pos.x, pos.y - 1);
        case 4:
            return coord(pos.x + 1, pos.y + 1);
        case 5:
            return coord(pos.x - 1, pos.y + 1);
        case 6:
            return coord(pos.x + 1, pos.y - 1);
        case 7:
            return coord(pos.x - 1, pos.y - 1);

        }
        return coord(0, 0);
    }

    bool solve(coord pos) {
        if (brd[pos.x][pos.y] == -4)
            return 1;

        bool paths[8] = { 0,0,0,0,0,0,0,0 };
        int count = 0, way = 0;

        if (pos.x + 1 >= 0 && pos.x + 1 < row) {
            if (brd[pos.x + 1][pos.y] == -1 || brd[pos.x + 1][pos.y] == -4) {
                count++;
                way = 0;
                paths[0] = 1;
            }
        }
        if (pos.y + 1 >= 0 && pos.y + 1 < col) {
            if (brd[pos.x][pos.y + 1] == -1 || brd[pos.x][pos.y + 1] == -4) {
                count++;
                way = 1;
                paths[1] = 1;
            }
        }
        if (pos.x - 1 >= 0 && pos.x - 1 < row) {
            if (brd[pos.x - 1][pos.y] == -1 || brd[pos.x - 1][pos.y] == -4) {
                count++;
                way = 2;
                paths[2] = 1;
            }
        }
        if (pos.y - 1 >= 0 && pos.y - 1 < col) {
            if (brd[pos.x][pos.y - 1] == -1 || brd[pos.x][pos.y - 1] == -4) {
                count++;
                way = 3;
                paths[3] = 1;
            }

        }
        if (pos.y + 1 >= 0 && pos.y + 1 < col && pos.x + 1 >= 0 && pos.x + 1 < row) {
            if (brd[pos.x + 1][pos.y + 1] == -1 || brd[pos.x + 1][pos.y + 1] == -4) {
                count++;
                way = 4;
                paths[4] = 1;
            }

        }
        if (pos.y + 1 >= 0 && pos.y + 1 < col && pos.x - 1 >= 0 && pos.x - 1 < row) {
            if (brd[pos.x - 1][pos.y + 1] == -1 || brd[pos.x - 1][pos.y + 1] == -4) {
                count++;
                way = 5;
                paths[5] = 1;
            }

        }
        if (pos.y - 1 >= 0 && pos.y - 1 < col && pos.x + 1 >= 0 && pos.x + 1 < row) {
            if (brd[pos.x + 1][pos.y - 1] == -1 || brd[pos.x + 1][pos.y - 1] == -4) {
                count++;
                way = 6;
                paths[6] = 1;
            }

        }
        if (pos.y - 1 >= 0 && pos.y - 1 < col && pos.x - 1 >= 0 && pos.x - 1 < row) {
            if (brd[pos.x - 1][pos.y - 1] == -1 || brd[pos.x - 1][pos.y - 1] == -4) {
                count++;
                way = 7;
                paths[7] = 1;
            }

        }

        if (count == 0) {
            brd[pos.x][pos.y] = number;
            number++;
            return 0;
        }
        brd[pos.x][pos.y] = number;
        number++;
        if (count == 1) {
            if (solve(next(way, pos)))
                return 1;
        }
        else {
            int temp = rand() % 8;
            for (int i = 0; i < 8; i++) {
                if (paths[i] == 1) {
                    if (solve(next(i, pos)))
                        return 1;
                    else {
                        brd[pos.x][pos.y] = number;
                        number++;
                    }
                }
            }
            return 0;
        }
        brd[pos.x][pos.y] = number;
        number++;
        return 0;


    }

    void print() {
        int k = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (brd[i][j] >= 0)
                    std::cout << brd[i][j];
                else {
                    switch (brd[i][j])
                    {
                    case -1:
                        cout << ".";
                        break;
                    case -2:
                        cout << "#";
                        break;
                    case -3:
                        cout << "x";
                        break;
                    case -4:
                        cout << "y";
                        break;
                    case -5:
                        cout << " ";
                        break;
                    }
                }
                std::cout << "\t";
            }
            std::cout << "\n";
        }
    }

    ~board() {
        for (int i = 0; i < row; i++)
            delete[] brd[i];
        delete[] brd;
    }
};

long long maze_1()
{
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto tiempo = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for (int i = 1; i < 13; i++) {
        std::string mazo = "maze/maze_";
        mazo.append(std::to_string(i));
        mazo.append(".txt");
        board mb(mazo);
        mb.solve(mb.initial);
        mb.print();
        cout <<"\n\n\n" << mazo << ": " << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - tiempo << "\n\n\n"<<endl;
        tiempo = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;
}
