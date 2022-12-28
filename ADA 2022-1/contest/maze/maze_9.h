#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <string>
#include <iomanip>
#include <chrono>

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

//Función para leer un laberinto de un archivo, si el siguiente std::string es "x" da su posición
void readMaze(std::vector<std::vector<std::string>>& maze, int& y, int& x, const std::string& fileName){
    std::ifstream file;
    file.open(fileName);
    if(!file.is_open()){
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return;
    }
    char c;
    int y_ = 0, x_ = 0;
    if(file.get(c)) maze.resize(1);
    while(file.get(c)){
        std::cout << c;
        if(c == 'x'){
            y = y_;
            x = x_;
        }
        if(c == '\n'){
            std::vector<std::string> row;
            maze.push_back(row);
            ++y_;
            x_ = 0;
        }
        else{
            maze[maze.size()-1].push_back(std::string(1, c));
            ++x_;
        }
    }
    std::cout << std::endl;
    file.close();
}

void print_maze(std::vector<std::vector<std::string>>& maze){
    for(auto & y : maze){
        for(auto & x : y){
            std::cout << std::setw(6) << x;
        }
        std::cout << std::endl;
    }
}

std::vector<std::pair<int, int>> get_neighbours(std::vector<std::vector<std::string>>& maze, int y, int x){
    std::vector<std::pair<int, int>> neighbours;
		if(y > 0 && x > 0 && (maze[y-1][x-1] == "." || maze[y-1][x-1] == "y")){
        neighbours.emplace_back(y-1, x-1);
    }
		if(y < maze.size()-1 && x < maze.size()-1 && (maze[y+1][x+1] == "." || maze[y+1][x+1] == "y")){
        neighbours.emplace_back(y+1, x+1);
    }
		if(y > 0 && x < maze[y].size()-1 && (maze[y-1][x+1] == "." || maze[y-1][x+1] == "y")){
        neighbours.emplace_back(y-1, x+1);
    }
		if(y < maze.size()-1 && x > 0 && (maze[y+1][x-1] == "." || maze[y+1][x-1] == "y")){
        neighbours.emplace_back(y+1, x-1);
    }
    if(x < maze[y].size()-1 && (maze[y][x+1] == "." || maze[y][x+1] == "y")){
        neighbours.emplace_back(y, x+1);
    }
    if(x > 0 && (maze[y][x-1] == "." || maze[y][x-1] == "y")){
        neighbours.emplace_back(y, x-1);
    }
    if(y < maze.size()-1 && (maze[y+1][x] == "." || maze[y+1][x] == "y")){
        neighbours.emplace_back(y+1, x);
    }
    if(y > 0 && (maze[y-1][x] == "." || maze[y-1][x] == "y")){
        neighbours.emplace_back(y-1, x);
    }
		
    return neighbours;
}

bool solve(std::vector<std::vector<std::string>>& maze, int y, int x, int& cont){
    if(maze[y][x] == "y")
        return true;
    if(maze[y][x] != "x" && maze[y][x] != "y"){
        maze[y][x] = std::to_string(cont);
        ++cont;
    }
    std::vector<std::pair<int, int>> neighbours = get_neighbours(maze, y, x);
    for(auto & neighbour : neighbours){
        if(solve(maze, neighbour.first, neighbour.second, cont)){
            return true;
        }
        if(maze[y][x] != "x"){
            maze[y][x] = std::to_string(cont);
            ++cont;
        }
    }
    return false;
}

long long int maze_9(){
    //const std::string fileName="maze9.txt";
  long long int suma=0;
  std::string fileName[12]={"maze_1.txt","maze_2.txt","maze_3.txt","maze_4.txt","maze_5.txt","maze_6.txt","maze_7.txt","maze_8.txt","maze_9.txt","maze_10.txt","maze_11.txt","maze_12.txt"};
    for (int i=0;i<12;i++){
        std::vector<std::vector<std::string>> maze;
        int y=0, x=0, cont = 1;
        readMaze(maze, y, x, "maze/"+fileName[i]);

        if(!maze.empty()){
        std::cout << "y: " << y << " x: " << x << std::endl;
        //print_maze(maze);
        auto start = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
    std::cout << "Solucion: " << ((solve(maze, y, x, cont)) ? "Si" : "No") << std::endl;
  auto end = std::chrono::duration_cast<std::chrono::milliseconds>(system_clock::now().time_since_epoch()).count();
  
    long long int elapsed_seconds = end - start;

    suma=suma+elapsed_seconds;
    std::cout << "tiempo " << time << std::endl;
    print_maze(maze);
    }
      
    }
    return suma;
}