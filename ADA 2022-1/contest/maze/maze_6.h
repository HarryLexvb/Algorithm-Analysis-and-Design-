#pragma once
#include <iostream>
#include <chrono>
#include <ctime>
#include <queue>
#include <vector>
#include<fstream>
#include<string>
#include <stack>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


using namespace std;






void print(vector < vector<string> >& maze)
{
    for (int unsigned i = 0; i < maze.size(); i++)
    {
        for (int unsigned j = 0; j < maze[0].size(); j++)
        {
            cout << maze[i][j] << '\t';
        }
        cout << endl;
    }
    cout << "\n\n" << endl;
}

void resolvMaze(vector < vector<string> >& maze)
{
    int unsigned x1 = 0;
    int unsigned x2 = 0;
    bool find = false;

    for (; x1 < maze.size(); x1++)
    {
        for (x2 = 0; x2 < maze[0].size() ; x2++)
        {
            if (maze[x1][x2] == "x")
            {
                find = true;
                break;
            }
            if (x1 != 0 && x2 == 1)
            {
                x2 = maze[0].size() - 1;
            }
            else if (x1 == maze.size() - 1 && x2 == 0)
            {
                x2 = 1;
            }
            if (maze[x1][x2] == "x")
            {
                find = true;
                break;
            }
            //cout << maze[x1][x2];
        }
        if (find)
        {
            break;
        }
        //cout << endl;
    }


    vector <string> num = { "3210", "3201", "3120", "3102", "3021", "3012", "2310", "2301", "2130", "2103", "2031", "2013", "1320", "1302", "1230", "1203", "1032", "1023", "0321", "0312", "0231", "0213", "0132", "0123" };
    /*
    * r   : recorrido
    * pci : punto con mas de un camino inconcluso
    */
    stack < int unsigned > rx;
    stack < int unsigned > ry;
    stack < string* > pci;
    
    rx.push(x1);
    ry.push(x2);
    
    if (x2 > 0 && maze[rx.top()][ry.top() - 1] == ".") //izq
    {
        rx.push(rx.top()); ry.push(ry.top() - 1);
    }
    else if (x1< maze.size() - 1 && maze[rx.top() + 1][ry.top()] == ".") //abajo
    {
        rx.push(rx.top() + 1); ry.push(ry.top());
    }
    else if (x2 < maze[0].size() - 1 && maze[rx.top()][ry.top() + 1] == ".") //der
    {
        rx.push(rx.top()); ry.push(ry.top() + 1);
    }
    else if (x1 > 0 && maze[rx.top() - 1][ry.top()] == ".") //arriba
    {
        rx.push(rx.top() - 1); ry.push(ry.top());
    }
    else if (x2 < maze[0].size() - 1 && x1 > 0 && maze[rx.top() - 1][ry.top() + 1] == ".")//arriba //der
    {
        rx.push(rx.top() - 1); ry.push(ry.top() + 1);
    }
    else if (x2 > 0 && x1 > 0 && maze[rx.top() - 1][ry.top() - 1] == ".")//arriba //izq
    {
        rx.push(rx.top() - 1); ry.push(ry.top() - 1);
    }
    else if (x2 > 0 && x1 < maze.size() - 1 && maze[rx.top() + 1][ry.top() - 1] == ".")//abajo //izq
    {
        rx.push(rx.top() + 1); ry.push(ry.top() - 1);
    }
    else if (x2 < maze[0].size() - 1 && x1 < maze.size() - 1 && maze[rx.top() + 1][ry.top() + 1] == ".")//abajo //der
    {
        rx.push(rx.top() + 1); ry.push(ry.top() + 1);
    }

    pci.push(nullptr);

    int i = 1;
    while (maze[rx.top()][ry.top() - 1] != "y" && maze[rx.top() + 1][ry.top()] != "y" && maze[rx.top()][ry.top() + 1] != "y" && maze[rx.top() - 1][ry.top()] != "y")
    {
        string num_str1(std::to_string(i));
        maze[rx.top()][ry.top()] = num_str1;


        vector <bool> mov = { (maze[rx.top()][ry.top() - 1] == "."), (maze[rx.top() + 1][ry.top()] == "."),
                                (maze[rx.top()][ry.top() + 1] == "."), (maze[rx.top() - 1][ry.top()] == ".") }; // [0]->izq, [1]->abajo, [2]->der, [3]->arriba

        int caminos = 0;

        if (mov[0]) //izq
        {
            caminos++;
        }
        if (mov[1]) //abajo
        {
            caminos++;
        }
        if (mov[2]) //der
        {
            caminos++;
        }
        if (mov[3]) //arriba
        {
            caminos++;
        }
        else if (maze[rx.top() + 1][ry.top() + 1] == ".")
        {
            caminos++;
        }
        else if (maze[rx.top() - 1][ry.top() - 1] == ".")
        {
            caminos++;
        }
        else if (maze[rx.top() + 1][ry.top() - 1] == ".")
        {
            caminos++;
        }
        else if (maze[rx.top() - 1][ry.top() + 1] == ".")
        {
            caminos++;
        }

        if (caminos > 1)
        {
            pci.push(&maze[rx.top()][ry.top()]);

        }
        else if (pci.top() == &maze[rx.top()][ry.top()])
        {
            pci.pop();
        }

        vector < vector <int> > sumas = { {0,-1}, {1, 0}, {0, 1}, {-1, 0} };

        srand(time(NULL));
        int nume = rand() % 24;


        
        //cout << num[0] << " " << num[1] << " " << num[2] << " " << num[3] << endl;
        if (mov[num[nume][0] - 48]) 
        {
            rx.push(rx.top() + sumas[num[nume][0] - 48][0]); ry.push(ry.top() + sumas[num[nume][0] - 48][1]);
        }
        else if (mov[num[nume][1] - 48]) 
        {
            rx.push(rx.top() + sumas[num[nume][1] - 48][0]); ry.push(ry.top() + sumas[num[nume][1] - 48][1]);
        }
        else if (mov[num[nume][2] - 48]) 
        {
            rx.push(rx.top() + sumas[num[nume][2] - 48][0]); ry.push(ry.top() + sumas[num[nume][2] - 48][1]);
        }
        else if (mov[num[nume][3] - 48])
        {
            rx.push(rx.top() + sumas[num[nume][3] - 48][0]); ry.push(ry.top() + sumas[num[nume][3] - 48][1]);
        }
        else if (maze[rx.top() - 1][ry.top() + 1] == ".")
        {
            rx.push(rx.top() - 1); ry.push(ry.top() + 1);
        }
        else if (maze[rx.top() - 1][ry.top() - 1] == ".")
        {
            rx.push(rx.top() - 1); ry.push(ry.top() - 1);
        }
        else if (maze[rx.top() + 1][ry.top() - 1] == ".")
        {
            rx.push(rx.top() + 1); ry.push(ry.top() - 1);
        }
        else if (maze[rx.top() + 1][ry.top() + 1] == ".")
        {
            rx.push(rx.top() + 1); ry.push(ry.top() + 1);
        }
        else
        {
            while (&maze[rx.top()][ry.top()] != pci.top())
            {
                rx.pop();
                ry.pop();

                i++;

                string num_str2(std::to_string(i));
                //cout << maze[rx.top()][ry.top()] << endl;
                maze[rx.top()][ry.top()] = num_str2;
            }
            //cout << maze[rx.top()][ry.top()] << endl;
            //cout << *pci.top() << endl;
            //print(maze);
            continue;
        }
        i++;
        //cout << "r: "<< maze[rx.top()][ry.top()] << endl;
        //if (pci.top() != nullptr) { cout << "pci: " << *pci.top() << endl; }
        //print(maze);
    }

    string num_str1(std::to_string(i));
    maze[rx.top()][ry.top()] = num_str1;
}


void llenarMatriz(string& name, vector<vector<string> >& maze)
{
    string line;
    string word;

    ifstream inFile(name);
    if (inFile)
    {   //read line by line
        while (getline(inFile, line, '\n'))
        {
            vector <string> tokens;

            // stringstream class check1
            //stringstream check1(line);

            string::iterator it = line.begin();
            // Tokenizing w.r.t. space ' '
            while (it != line.end())//getline(check1, intermediate, '\t'))
            {
                string str1(1, *it);
                tokens.push_back(str1);
                it++;
            }
            maze.emplace_back(tokens);
        }
        
    }
    else
    {
        std::cout << "file " << name << " cannot be opened" << std::endl;
    }

    inFile.close();
}




long long maze_6()
{
    vector < vector<string> > maze0;
    vector < vector<string> > maze1;
    vector < vector<string> > maze2;
    vector < vector<string> > maze3;
    vector < vector<string> > maze4;
    vector < vector<string> > maze5;
    vector < vector<string> > maze6;
    vector < vector<string> > maze7;
    vector < vector<string> > maze8;
    vector < vector<string> > maze9;
    vector < vector<string> > maze10;
    vector < vector<string> > maze11;
    vector < vector<string> > maze12;


    vector < vector < vector<string> > > maze = { maze1,maze2, maze3, maze4, maze5, maze6,maze7,maze8,maze9,maze10,maze11,maze12 };
    long long time_int = 0;

    vector <string> nombres = { "maze_1.txt","maze_2.txt","maze_3.txt","maze_4.txt","maze_5.txt","maze_6.txt","maze_7.txt","maze_8.txt","maze_9.txt","maze_10.txt","maze_11.txt","maze_12.txt" };
    
    for (int i = 0; i < 12; i++)
    {
      string pan = "maze/" + nombres[i];
        llenarMatriz(pan, maze[i]);
    }
    for (int i = 0; i < 12; i++)
    {

        if (maze[i] == maze0) continue; // si  la matriz esta vacia



        //################################################
        auto millisec_start_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        resolvMaze(maze[i]);
        print(maze[i]);

        //################################################
        auto millisec_end_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        time_int += (millisec_end_epoch - millisec_start_epoch);
    }
}
