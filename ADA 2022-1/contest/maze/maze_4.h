#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <time.h>
#include <chrono>
#include <ctime>

using namespace std;
using chrono::duration_cast;
using chrono::milliseconds;
using chrono::seconds;
using chrono::system_clock;

#define vvs vector<vector<string>> 

bool esunnumero(string valor) {
    for (int i = 0; i < valor.size(); i++) {
        if (!isdigit(valor[i])) {
            return false;
        }
    }
    return true;
}
void printtablero(vvs & tablero) 
{
    for (int x = 0; x < tablero.size(); x++) {
        for (int y = 0; y < tablero[x].size(); y++) {
            cout << tablero[x][y] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

bool esposible(vvs & maze, int x, int y) {
    int c = 0;

    if (x >= 0)
        c = x;

    return x >= 0 && x < maze.size() && y >= 0 && y < maze[c].size() && maze[x][y] != "#" && maze[x][y] != " ";
}
//bool resolvemaze(vvs& maze, int x, int y, int& num, vvs& sol);
bool resolvemaze(vvs& maze, int x, int y, int& num, vvs& sol) {

    if (x < maze.size()) {
        if (y < maze[0].size()) {
            if (maze[x][y] == "y") {
                return true;
            }
        }
    }
    if (esposible(maze, x, y) == true) {
        if (esunnumero(sol[x][y])) {
            return false;
        }
        if (sol[x][y] != "x") {
            stringstream ss;
            string str;
            ss << num;
            ss >> str;
            sol[x][y] = str;
            num++;
        }
        if (num==300) {
             cout<<endl;
         }

         /*if (resolvemaze(maze, x, y - 1, num, sol))
             return true;
         if (resolvemaze(maze, x + 1, y - 1, num, sol))
             return true;
         if (resolvemaze(maze, x + 1, y, num, sol))
             return true;
         if (resolvemaze(maze, x + 1, y + 1, num, sol))
             return true;
         if (resolvemaze(maze, x, y + 1, num, sol))
             return true;
         if (resolvemaze(maze, x - 1, y + 1, num, sol))
             return true;
         if (resolvemaze(maze, x - 1, y, num, sol))
             return true;
         if (resolvemaze(maze, x - 1, y - 1, num, sol))
             return true;
         */

        if (resolvemaze(maze, x, y - 1, num, sol) ||
            resolvemaze(maze, x + 1, y - 1, num, sol) ||
            resolvemaze(maze, x + 1, y, num, sol) ||
            resolvemaze(maze, x + 1, y + 1, num, sol) ||
            resolvemaze(maze, x, y + 1, num, sol) ||
            resolvemaze(maze, x - 1, y + 1, num, sol) ||
            resolvemaze(maze, x - 1, y, num, sol) ||
            resolvemaze(maze, x - 1, y - 1, num, sol))

            return true;
        
        if (sol[x][y] == "x")
            return false;

        sol[x][y] = ".";
        num--;
        return false;
    }
    return false;
}
bool maze_solve(vvs & maze) {
    int x = 0;
    int y = 0;
    int num = 0;

    vvs sol = maze;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (maze[i][j] == "x") {
                x = i;
                y = j;
            }
        }
    }
    if (resolvemaze(maze, x, y, num, sol) == false) {
        cout << "No hay solucion" << endl;
        return false;
    }
    printtablero(sol);
    return true;
}

long long int maze_4()
{
    
    
    auto mini = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    vector<string> nombres(12);
    for (int i = 0; i < 12; i++)
    {
        nombres[i] = "maze/maze_" + to_string(i + 1) + ".txt";
    }
    auto mfin = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    
    long long int total = mfin - mini;

    for (int i = 0; i < 12; i++)
    {
        auto mini_aux = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        ifstream mymatrix(nombres[i]);
        string line;
        vvs maze;
        while (getline(mymatrix, line)) {
            vector<string> fila;
            for (int i = 0; i < line.size(); i++) {
                string a;
                a.push_back(line[i]);
                fila.push_back(a);
            }
            maze.push_back(fila);
        }
        maze_solve(maze);
        auto mfin_aux = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        auto aux = mfin_aux - mini_aux;
        total += aux;
        cout << "Grupo "<<i+1<<": "<< aux << endl;
    }
    return total;
}

