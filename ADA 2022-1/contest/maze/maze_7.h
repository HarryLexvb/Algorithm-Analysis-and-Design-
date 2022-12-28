#include <iostream>
#include <chrono>
#include <ctime>
#include <math.h>
#include <string>
#include <vector>
#include <fstream>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace std;


int cont = 0;

string** readmatrix(int& posy, int& posx, string dir)
{

    int y = 0;
    int x = 0;
    int cont = 0;

    string nombreArchivo = dir;
    ifstream archivo(nombreArchivo.c_str());
    string aux = "";
    string fila;
    while (getline(archivo, fila)) {

        x++;
        aux = aux + fila;

    }

    string** A;

    A = new string * [x];
    for (int i = 0; i < x; i++)
    {
        A[i] = new string[aux.size() / x];
    }


    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < aux.size() / x; j++)
        {
            A[i][j] = aux[cont];
            cont++;
        }
    }
    posy = x;
    posx = (aux.size() / x);

    return A;
}

void printmatrix(string** sol, int X, int Y)
{
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++)
            cout << sol[i][j] << "	";
        cout << endl;
    }
    cout << endl;
}

bool opcion(string** maze, int x, int y, int X, int Y)
{
  
    if (x >= 0 && x < X && y >= 0 && y < Y && maze[x][y] != "#")
    {
        return true;
    }
    return false;
}

bool caminos(string** maze, int x, int y, string** sol, int X, int Y, string fin = "y")
{
    
    if (maze[x][y] == fin)
    {
        sol[x][y] = fin;
        return true;
    }
    if (opcion(maze, x, y, X, Y) == true)
    {
        string temp = to_string(cont);

        if (sol[x][y] != "." && sol[x][y] != "x")
        {
            return false;
        }
        cont++;
       
        sol[x][y] = temp;

               if (y + 1 < Y && caminos(maze, x, y + 1, sol, X, Y) == true)
        {
            
            return true;
        }

        if (x + 1 < X && caminos(maze, x + 1, y, sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        
        if (x - 1 >= 0 && caminos(maze, x - 1, y, sol, X, Y) == true)
        {
            cont++;
            return true;
        }
       
        if (y - 1 >= 0 && caminos(maze, x, y - 1, sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        if (x + 1 < X && y + 1 < Y && caminos(maze, (x + 1), (y + 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }
        if (x - 1 >= 0 && y - 1 >= 0 && caminos(maze, (x - 1), (y - 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }
        if (x + 1 < X && y - 1 >= 0 && caminos(maze, (x + 1), (y - 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }
        if (x - 1 >= 0 && y + 1 < Y && caminos(maze, (x - 1), (y + 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }    
        cont++;
        sol[x][y] = to_string(cont - 1);
        return false;
    }
    return false;
}

long long int  maze_7(){
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    string a = "maze/maze_";
    string aux2;
    string aux3 = ".txt";
    string fileName;
    for (int x = 1; x <= 12; x++)
    {
        
        string aux(to_string(x));
        aux2 = a + aux + aux3;
        fileName = aux2;
        aux2 = "";

        cout << "Laberinto: " << endl;

        string** maze;
        int X = 0;
        int Y = 0;
        cout << fileName << endl;
        maze = readmatrix(X, Y, fileName);

        string** sol = new string * [X];
        for (int i = 0; i < X; i++)
        {
            sol[i] = new string[Y];
        }
        int inix = 0, iniy = 0;

        for (int i = 0; i < X; i++)
        {
            for (int j = 0; j < Y; j++)
            {
                sol[i][j] = maze[i][j];
            }
        }

        for (int x = 0; x < X; x++)
        {
            for (int y = 0; y < Y; y++)
            {
                if (maze[x][y] == "x")
                {
                    inix = x;
                    iniy = y;
                    x = X;
                    y = Y;
                }
            }

        }

        if (!caminos(maze, inix, iniy, sol, X, Y) )
        {
            cout << "No existe solucion" << endl;
       
        }
        cout << "Solucion: " << endl;
        sol[inix][iniy] = "x";

        printmatrix(sol, X, Y);
        
       
    }


	cont = 0;
    return millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
   
  
}

int main(){
	maze_7();
	return 0;
}
