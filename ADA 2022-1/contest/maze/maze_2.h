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

string** leer_matriz(int& posy, int& posx, string dir)
{
    //string** A;
    int y = 0;
    int x = 0;
    int contador = 0;

    string nombreArchivo = dir;
    ifstream archivo(nombreArchivo.c_str());
    string aux = "";
    string linea;
    // Obtener línea de archivo, y almacenar contenido en "linea"
    while (getline(archivo, linea)) {
        // Lo vamos imprimiendo
        x++;
        aux = aux + linea;

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
            A[i][j] = aux[contador];
            contador++;
        }
    }
    posy = x;
    posx = (aux.size() / x);

    return A;
}

void print(string** sol, int X, int Y)
{
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++)
            cout << sol[i][j] << "	";
        cout << endl;
    }
    cout << endl;
}

bool sigCam(string** maze, int x, int y, int X, int Y)
{
    // no salirse del laberinto
    if (x >= 0 && x < X && y >= 0 && y < Y && maze[x][y] != "#")
    {
        return true;
    }
    return false;
}

bool avanzarLab(string** maze, int x, int y, string** sol, int X, int Y, string fin = "y")
{
    // revisar si ya llegó a la salida
    if (maze[x][y] == fin)
    {
        sol[x][y] = fin;
        return true;
    }
    // Revisar si el siguiente paso es valido (no choca pared o fuera del laberinto)
    if (sigCam(maze, x, y, X, Y) == true)
    {
        string temp = to_string(cont);

        // Revisar si la posicion actual no es parte del recorrido ya hecho
        if (sol[x][y] != "." && sol[x][y] != "x")
        {
            return false;
        }
        cont++;
        // Marcas la posicion como recorrida
        sol[x][y] = temp;

        //print(sol,X,Y);

        // Moverse a la derecha

        //cout << "0" << endl;
        // Moverse a abajo
        if (y + 1 < Y && avanzarLab(maze, x, y + 1, sol, X, Y) == true)
        {
            //cont++;
            return true;
        }

        if (x + 1 < X && avanzarLab(maze, x + 1, y, sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        //cout << "1" << endl;

        // Moverse a la izquierda
        if (x - 1 >= 0 && avanzarLab(maze, x - 1, y, sol, X, Y) == true)
        {
            cont++;
            return true;
        }
        //cout << "2" << endl;
        // Moverse a arriba
        if (y - 1 >= 0 && avanzarLab(maze, x, y - 1, sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        if (x + 1 < X && y + 1 < Y && avanzarLab(maze, (x + 1), (y + 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        if (x - 1 >= 0 && y - 1 >= 0 && avanzarLab(maze, (x - 1), (y - 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        if (x + 1 < X && y - 1 >= 0 && avanzarLab(maze, (x + 1), (y - 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        if (x - 1 >= 0 && y + 1 < Y && avanzarLab(maze, (x - 1), (y + 1), sol, X, Y) == true)
        {
            cont++;
            return true;
        }

        //cout << "3" << endl;

        // Si ninguna de las direcciones funciona, retroceder
        cont++;
        sol[x][y] = to_string(cont - 1);
        return false;
    }
    return false;
}

double maze_2()
{
    auto millisec_since_epoch1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    string a = "maze/maze_";
    string aux2;
    string aux3 = ".txt";
    string fileName;
    for (int x = 1; x <= 12; x++)
    {
        auto millisec_since_epoch3 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        string aux(to_string(x));
        aux2 = a + aux + aux3;
        fileName = aux2;
        aux2 = "";

        cout << "Laberinto: " << endl;

        string** maze;
        int X = 0;
        int Y = 0;
        cout << fileName << endl;
        maze = leer_matriz(X, Y, fileName);

        //cout << "X,Y: " << X << "," << Y << endl;
        //print(maze,X,Y);

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
        //cout << "ini: " << inix << ", " << iniy << endl;

        if (avanzarLab(maze, inix, iniy, sol, X, Y) == false)
        {
            cout << "No existe solucion" << endl;
            //return false;
        }
        cout << "Recorrido de solucion: " << endl;
        sol[inix][iniy] = "x";

        print(sol, X, Y);
        //return true;

        auto millisec_since_epoch4 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        double tiempo = millisec_since_epoch4 - millisec_since_epoch3;
        cout << "time: " << tiempo << " milisegundos" << endl;
    }


	cont = 0;
    auto millisec_since_epoch2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    double tiempo = millisec_since_epoch2 - millisec_since_epoch1;
    //cout << "time: " << tiempo << " milisegundos" << endl;
    return tiempo;
}

