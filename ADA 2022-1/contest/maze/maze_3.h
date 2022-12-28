#pragma once
#include <iostream>
#include <fstream>
#include <chrono>
#include<string>
#include<vector>
using namespace std;
using namespace::chrono;
//Algoritmo maze
void ImprimirLaberinto(string** a, int fila, int columna, int posx, int posy)
{
    for (int i = 0; i < fila; i++) {
        for (int j = 0; j < columna; j++) {
            a[posx][posy] = "x";
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }
}
bool VerificarPosibilidad(string** a, int x, int y, int FilaLaberinto, int ColumnaLaberinto)
{
    //chequear el fuera de limite, no tocar una pared
    if (x >= 0 && x < FilaLaberinto && y >= 0 && y < ColumnaLaberinto && a[x][y] == ".")return true;
    return false;
}
//Valores a usar pared #, camino posible ., entrada x, salida y
//Sobre le algoritmo, a priori solo sabe donde esta x, no conoce y; saber pos de x
bool Laberinto(string** a, int x, int y, int FilaLaberinto, int ColumnaLaberinto)
{
    if (VerificarPosibilidad(a, x, y, FilaLaberinto, ColumnaLaberinto))
    {
        if (a[x][y] == "y")return true;
        if (a[x][y] == "*")return false;
        a[x][y] = "*";
        //moverse hacia arriba
        if (Laberinto(a, x, y - 1, FilaLaberinto, ColumnaLaberinto))return true;
        //direccional hacia arriba izquierda
        if (Laberinto(a, x + 1, y - 1, FilaLaberinto, ColumnaLaberinto))return true;
        //moverse hacia la izquierda
        if (Laberinto(a, x + 1, y, FilaLaberinto, ColumnaLaberinto))return true;
        //direccional hacia abajo izquierda
        if (Laberinto(a, x + 1, y + 1, FilaLaberinto, ColumnaLaberinto))return true;
        //moverse hacia abajo
        if (Laberinto(a, x, y + 1, FilaLaberinto, ColumnaLaberinto))return true;
        //direccional hacia abajo derecha
        if (Laberinto(a, x - 1, y + 1, FilaLaberinto, ColumnaLaberinto))return true;
        //moverse hacia la derecha
        if (Laberinto(a, x - 1, y, FilaLaberinto, ColumnaLaberinto))return true;
        //direccional hacia arriba derecha
        if (Laberinto(a, x - 1, y - 1, FilaLaberinto, ColumnaLaberinto))return true;
        a[x][y] = ".";
        return false;
    }
    return false;
}
void maze_31(string** a, int posx, int posy, int FilaLaberinto, int ColumnaLaberinto)
{
    if ((Laberinto(a, posx, posy, FilaLaberinto, ColumnaLaberinto)))
    {
        ImprimirLaberinto(a, FilaLaberinto, ColumnaLaberinto, posx, posy);
    }
    else
    {
        cout << "No hay solucion\n";
    }
}


long long int maze_3()
{
    vector<long long int> l1;
    int posx(0), posy(0), FilaLaberinto(0), ColumnaLaberinto(0);
    int beg = 0;
    string** a = nullptr;
    string linea;
    long long int t3;
    long long int t4 = 0;
    string b = "maze/maze_";
    string aux2;
    string aux3 = ".txt";
    string fileName;
    for (int x = 1; x <= 12; x++)
    {
        string aux(to_string(x));
        aux2 = b + aux + aux3;
        fileName = aux2;
        aux2 = "";
        ifstream archi(fileName);
        if (archi.is_open())
        {
            while (getline(archi, linea))
            {
                int end = 0;
                for (int i = 0; i < linea.size(); ++i)
                {
                    if (linea[i] != ' ') { end++; }
                }
                beg++;
                ColumnaLaberinto = end;
            }
            FilaLaberinto = beg;
            ifstream file(fileName);
            a = new string * [FilaLaberinto];
            for (int i = 0; i < FilaLaberinto; i++)
            {
                a[i] = new string[ColumnaLaberinto];
            }
            for (int u = 0; u < FilaLaberinto; u++)
            {
                for (int v = 0; v < ColumnaLaberinto; v++) {
                    file >> a[u][v];
                    if (a[u][v] == "x" || a[u][v] == "X")
                    {
                        posx = u; posy = v; a[u][v] = ".";
                    }
                }
            }
            auto t1 = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            maze_31(a, posx, posy, FilaLaberinto, ColumnaLaberinto);
            auto t2 = duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            t3 = t2 - t1;
            l1.push_back(t3);
            t4 += t3;
            cout << "mili: " << l1.back() << endl;
            file.close();
            archi.close();
        }
        else {
            cout << "no se abre" << endl << endl;
        }
    }
    return t4;
}


