#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector> 
#include <string> 

#include <chrono>
#include <ctime>

using namespace std;
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

class Maze
{
private:
    int xini, yini;
    int filas, columnas;
    string file1;
    vector<vector<string>> A;

public:
    Maze(int _xini=-1, int _yini=-1, string file1 = "")
    //Maze()
    {
        //xini = _xini;
        //yini = _yini;
        filas = 0;
        columnas = 0;
        
        //lectura de txt:
        string filename(file1);
        string columnass;

        ifstream input_file(filename);
        
        while (getline(input_file,columnass,'\n'))
        {
            filas++;
            columnas = columnass.size();
        }
        
        // -----------------------------------------------
        //   A.push_back(vector<string>(columnas.size()));
        A.assign(filas, vector<string>(columnas));
        // -----------------------------------------------

        string filename2(file1);
        
        int j = 0;
        //string s;
        string number;
        
        ifstream input_file2(filename2);

        while (getline(input_file2,number,'\n'))
        {
            for (int i = 0; i < number.size(); i++)
            {
                A[j][i] = number[i];
                if (A[j][i] == "x")
                {
                    xini = j;
                    yini = i;
                }
            }
            j++;
        }

        input_file.close();

        //cout << "filas: " << filas << endl;
        //cout << "columnas: " << columnas << endl;
        //cout << "A.size: " << A.size() << " - A[0].size: "<< A[0].size() << endl;
    }

    void printMatrix() 
    {      
        for (int i = 0; i < filas; i++) 
        {
            for (int j = 0; j < columnas; j++)
            {
                //cout << A[i][j];
                cout << A[i][j] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    bool issafe(int x_pointer, int y_pointer)
    {
        //verificar si el movimiento esta dentro del parametro
        if (x_pointer >= 0 && x_pointer < filas && y_pointer >= 0 && y_pointer < columnas) 
        {
            //verificar si el movimiento se puede hacer(si esta vacio, es el final, o no fue visitado)
            if (A[x_pointer][y_pointer] == "." || A[x_pointer][y_pointer] == "y" || A[x_pointer][y_pointer] == "Y")
            {
                return 1;
            }
        }
        return 0;
    }

    int buscar(int x_pointer, int y_pointer, int it)
    {
        //caso base, si llega al final
        if (A[x_pointer][y_pointer] == "y" || A[x_pointer][y_pointer] == "Y")
        {
            return 1;
        }

        if (A[x_pointer][y_pointer] != "x")
        {
            string stra = to_string(it);
            A[x_pointer][y_pointer] = stra;
            //A[x_pointer][y_pointer] = "1";
            //printMatrix();
        }

        // ----------------- Backtraking --------------------------
        if (issafe(x_pointer + 1, y_pointer + 1))
        {
            if (buscar(x_pointer + 1, y_pointer + 1, it + 1))
            {
                return 1;
            }
        }

        if (issafe(x_pointer - 1, y_pointer + 1))
        {
            if (buscar(x_pointer - 1, y_pointer + 1, it + 1))
            {
                return 1;
            }
        }

        if (issafe(x_pointer + 1, y_pointer - 1))
        {
            if (buscar(x_pointer + 1, y_pointer - 1, it + 1))
            {
                return 1;
            }
        }

        if (issafe(x_pointer - 1, y_pointer - 1))
        {
            if (buscar(x_pointer - 1, y_pointer - 1, it + 1))
            {
                return 1;
            }
        }
        //------------------------------------------------
        if (issafe(x_pointer + 1, y_pointer))
        {
            if (buscar(x_pointer + 1, y_pointer, it + 1))
            {
                return 1;
            }
        }

        if (issafe(x_pointer, y_pointer + 1))
        {
            if (buscar(x_pointer, y_pointer + 1, it + 1))
            {
                return 1;
            }
        }

        if (issafe(x_pointer - 1, y_pointer))
        {
            if (buscar(x_pointer - 1, y_pointer, it + 1))
            {
                return 1;
            }
        }

        if (issafe(x_pointer, y_pointer - 1))
        {
            if (buscar(x_pointer, y_pointer - 1, it + 1))
            {
                return 1;
            }
        }

        A[x_pointer][y_pointer] = 'f';
        it = it - 1;
        return 0;
    }

    void laberinto()
    {
        int it = 0;
        buscar(xini, yini, it);
        printMatrix();
    }
};

void maze01() //no usamos esta
{
    Maze maze;
    maze.printMatrix();
    cout << "solucion:" << endl;
    maze.laberinto();
}

long long int maze_11()
{
    long long sum_tiempo = 0;
    vector<string> archivos = { "maze/maze_1.txt","maze/maze_2.txt","maze/maze_3.txt","maze/maze_4.txt","maze/maze_5.txt","maze/maze_6.txt","maze/maze_7.txt","maze/maze_8.txt","maze/maze_9.txt","maze/maze_10.txt","maze/maze_11.txt","maze/maze_12.txt" };
    //vector<string> archivos = { "maze_11.txt" };

    for (int i = 0; i < archivos.size(); i++)
    {
        auto millisec_start_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        // -1 -1, para inicializar el dato de xini y y ini, cuando los incerta... busca el inicio
        Maze maze(-1, -1, archivos[i]);
        //maze.printMatrix();
        cout << "Solucion:" << endl;
        maze.laberinto();

        auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        sum_tiempo = sum_tiempo + (millisec_end_epoch - millisec_start_epoch);
    }

    cout << "time maze: " << sum_tiempo << endl;
    return sum_tiempo;

    /*
    auto millisec_start_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    Maze maze(-1, -1, "laberinto2.txt");
    maze.printMatrix();
    cout << "Solucion:" << endl;
    maze.laberinto();

    auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    cout << "time maze: " << millisec_end_epoch - millisec_start_epoch << endl;
    return millisec_end_epoch - millisec_start_epoch;
    */
}