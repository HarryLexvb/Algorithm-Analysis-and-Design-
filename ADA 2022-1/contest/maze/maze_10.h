#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>      // std::istringstream
#include <string>       // std::string
#include <deque>
#include <chrono>
#include <sys/time.h>
#include <ctime>


using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


using namespace std;




struct Node{
    bool visited ;
    int step ;
    char val ;
    Node(char _val){
        visited = step = 0;
        val = _val;
    }
};


deque<deque<Node*>> Maze;
int initPos[2];


bool validIndex(int x ,int y){
    return (x>= 0 && x<Maze.size()) && (y>=0 && y<Maze[0].size());
}


bool DFS(int x, int y , int _step ){

    //goal is reached
    if(Maze[x][y]->val == 'y'){
        cout<<"\nsolved";
        return 1;
    }

    //visited node

    Maze[x][y]->visited = 1;
    Maze[x][y]->step = _step+1;

    //tremaux rules r-u-l-d

    if(validIndex(x,y+1) && !Maze[x][y+1]->visited && Maze[x][y+1]->val != '#'){
        if(DFS(x,y+1,Maze[x][y]->step)) return true;
    }
    if(validIndex(x-1,y+1) && !Maze[x-1][y+1]->visited && Maze[x-1][y+1]->val != '#'){
        if(DFS(x-1,y+1,Maze[x][y]->step)) return true;
    }
  if(validIndex(x-1,y) && !Maze[x-1][y]->visited && Maze[x-1][y]->val != '#'){
        if(DFS(x-1,y,Maze[x][y]->step)) return true;
    }

   if(validIndex(x-1,y-1) && !Maze[x-1][y-1]->visited && Maze[x-1][y-1]->val != '#'){
        if(DFS(x-1,y-1,Maze[x][y]->step)) return true;
    }
    if(validIndex(x,y-1) && !Maze[x][y-1]->visited && Maze[x][y-1]->val != '#'){
        if(DFS(x,y-1,Maze[x][y]->step)) return true;
    }

    if(validIndex(x+1,y-1) && !Maze[x+1][y-1]->visited && Maze[x+1][y-1]->val != '#'){
        if(DFS(x+1,y-1,Maze[x][y]->step)) return true;
    }
    if(validIndex(x+1,y) && !Maze[x+1][y]->visited && Maze[x+1][y]->val != '#'){
        if(DFS(x+1,y,Maze[x][y]->step)) return true;
    }
   if(validIndex(x+1,y+1) && !Maze[x+1][y+1]->visited && Maze[x+1][y+1]->val != '#'){
        if(DFS(x+1,y+1,Maze[x][y]->step)) return true;
    }

    return 0;
}


void loadMaze(string filename){

    ifstream ifs(filename);
    string text;
    char tempchar;
    int i=0,j=0;
    while (getline(ifs, text)) {
        j=0;
        istringstream iss(text);
        deque<Node*> tempv;
        while (iss >> tempchar) {
            if(tempchar == 'x'){
                initPos[0] = i;
                initPos[1] = j;
            }
            Node* n = new Node(tempchar);
            tempv.push_back(n);
            j++;
        }
        Maze.push_back(tempv);
        i++;
    }

}


void PrintSolution () {
    cout << '\n';
    for (int i = 0; i < Maze.size(); i++) {
        for (int j = 0; j < Maze[0].size(); j++) {
            cout << Maze[i][j]->val << " ";
        }
        cout << '\n';
    }
}

void PrintSolution2 () {
    cout << '\n';
    for (int i = 0; i < Maze.size(); i++) {
        for (int j = 0; j < Maze[0].size(); j++) {
            if(Maze[i][j]->step > 0)
                cout<<Maze[i][j]->step<<"\t";
            else
                cout << Maze[i][j]->val << "\t";
        }
        cout << '\n';
    }
}


long long int maze_util(string filename){
   
   cout<<"\n\n"<<filename;
    unsigned t0, t1;

    // maze_10
auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    loadMaze(filename);
    DFS(initPos[0],initPos[1],0);
    PrintSolution2();
    Maze.clear();

return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millisec_since_epoch;;

}

long long int maze_10(){
      vector<string> files = {
"maze_1.txt" ,
"maze_2.txt" ,
"maze_3.txt" ,
"maze_4.txt" ,
"maze_5.txt" ,
"maze_6.txt" ,
"maze_7.txt" ,
"maze_8.txt" ,
"maze_9.txt" ,
"maze_10.txt" ,
"maze_11.txt",
"maze_12.txt"
  } ;

    long long int total = 0;
     for(string file : files){
        long long int t = maze_util(file);
        cout<<"\nt: "<<t;
        total += t;
         cout<<"\ntotal "<<total;
     }
     
    return total;
}


