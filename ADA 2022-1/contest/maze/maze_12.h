#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
using namespace std;

class Matrix{
  int sizex;
  int sizey;
  string ** mat;
  short x[2];
  int c=-1;
  short length=1;
  public:
  Matrix(string name) {
    ifstream in(name);
    string temp;
    sizex = sizey = 0;
    while (getline(in, temp)){
        if(temp.empty()) continue;
        sizex ++;
    }
    stringstream ss(temp);
    sizey = temp.length();
    mat = new string*[sizex];
    ifstream inp(name);
    for(int i = 0;i<sizex;i++){
        mat[i] = new string[sizey];
        getline(inp,temp);
        stringstream ss(temp);
        for (int j = 0;j<sizey;j++){
            mat[i][j] = temp[j];
        }
    }
    in.close();
    inp.close();
  }

  Matrix(int size, string a) {
      sizex=sizey=size;
      mat = new string*[sizex];
      for(int i = 0;i<sizex;i++){
          mat[i] = new string[sizey];
          for (int j = 0;j<sizey;j++){
            mat[i][j]= a;
          }
      }
  }

  Matrix(int size1, int size2, string a) {
      sizex=size1;
      sizey=size2;
      mat = new string*[sizex];
      for(int i = 0;i<sizex;i++){
          mat[i] = new string[sizey];
          for (int j = 0;j<sizey;j++){
            mat[i][j]= a;
          }
      }
  }

  string** get_mat(){
    return mat;
  }


  void printM(){
      for (int i = 0; i < sizex; i++){
          for (int j = 0; j < sizey; j++){
              cout << mat[i][j] << " "<<setw(length);
          }
          cout<<endl<<setw(0);
      }
  }
  void printU(int x,int y){
    cout << mat[x][y]<<endl;
  }

  void setX(int x, int y){
    mat[x][y]="x";
    this->x[0]=x;
    this->x[1]=y;
  }

  void lookX(){
    for (int i =0;i<sizex;i++){
      for (int j = 0; j<sizey;j++) {
         if(j==0||j==sizey-1||i==0||i==sizex-1){
           if(mat[i][j]=="x"||mat[i][j]=="X") {setX(i,j);
            }
         }
       }
    }
  }

  bool pathU(int posx, int posy, string**sol){
    if (mat[posx][posy]=="y"){
          sol[posx][posy]="y";
          return true;
        }
    c++;
    stringstream ss;
    ss << c;
    string str = ss.str();
        sol[posx][posy] = str;
        ss.str(""); 
        if (posx-1>=0&&mat[posx-1][posy]!="#"&&sol[posx-1][posy]=="#"){if (pathU(posx - 1, posy, sol) == true)return true;}
    if(posy+1<sizey&&mat[posx][posy+1]!="#"&&sol[posx][posy+1]=="#"){if (pathU(posx, posy + 1, sol) == true)return true;}
        if(posx+1<sizex&&mat[posx+1][posy]!="#"&&sol[posx+1][posy]=="#"){if (pathU(posx + 1, posy, sol) == true) return true;}
        if(posy-1>=0&&mat[posx][posy-1]!="#"&&sol[posx][posy-1]=="#"){if (pathU(posx, posy - 1, sol) == true)return true;}
        c++;
        ss << c;
        str = ss.str();
        sol[posx][posy] = str;
        return false;
  }

  void path(){
    Matrix  *sol= new Matrix (sizex,sizey,"#");
    pathU(x[0],x[1],sol->get_mat());
    sol->setX(x[0],x[1]);
    stringstream ss;
    ss<<c;
    sol->length = ss.str().size();
    sol->printM();
    cout<<endl;
  }
};

auto maze_12(){
  string asd = "maze/maze_";
  //cout<<asd<<endl;
  int int_t=0;
  for(int i =1;i<=12;i++){
    auto start = std::chrono::high_resolution_clock::now();
    stringstream ss;
    ss <<i;
    string name = asd+ss.str()+".txt";
    ifstream my (name);
    if (my.fail()) continue;
    Matrix a(name);
    a.lookX();
    a.path();
    auto end = std::chrono::high_resolution_clock::now();
    auto int_s = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    int_t+=int_s.count();
    cout << name <<" demoro: "<<int_s.count()<< " microsegundos"<<endl;
    }
  return int_t;
}