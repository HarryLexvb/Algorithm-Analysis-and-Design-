#include <iostream>
#include <chrono>

/*
int move_x[8] = {1, 1, 2, 2, -1, -1, -2, -2};
int move_y[8] = {2, -2, 1, -1, 2, -2, 1, -1}; // */

/*int move_x[8] ={-2, -2, -1, 1, 2, 2, 1, -1};
int move_y[8] = {-1, 1, 2, 2, 1, -1, -2, -2}; // */

/*int move_x[8] ={2, 1 , -1, -2, -2, -1, 1, 2};
int move_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};// */


int move_x[8] = {1,2,2,1,-1,-2,-2,-1};
int move_y[8] = {2,1,-1,-2,-2,-1,1,2};// */

/*int move_x[8] ={2, 2 , -2, -2, 1, 1, -1, -1};
int move_y[8] = {1, -1, 1, -1, 2, -2, 2, -2};// */

void print(int n, int **matrix){
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            std::cout << *(*(matrix + i) + j ) << "\t";
        }
        std::cout<<std::endl;
    }
}

bool check(int x, int y, int **matrix, int n){
    //Verífica que no se sobrepase los limites de la matriz y que la posición a verificar no se haya tomado previamente.
    if(x < 0 or x > n - 1 or y < 0 or y > n - 1 or *(*(matrix + x) + y ) > 0)
        return false;
    return true;
}

int getDegree(int **matrix, int n, int x, int y){
    //Verifica los caminos posibles, en caso de no tener caminos posibles se retorna -1
    int res = -1;
    for(int i = 0; i < 8; ++i)
        if(check(x + move_x[i], y + move_y[i], matrix, n))
            res += 1;
    return res;
}

bool solve(int n, int **matrix, int curr_x, int curr_y, int pos){
    int id1 = -1;
    int min_degree1 = n + 1;
    //matrix[curr_x][curr_y] = pos;
    *(*(matrix + curr_x) + curr_y ) = pos;
    if(pos == n*n){
        print(n, matrix); //Encuentra la solución, imprime el array
        return true;
    }
    for(int i = 0; i < 8; ++i){
        int new_x = curr_x + move_x[i];
        int new_y = curr_y + move_y[i];
        if(check(new_x, new_y, matrix, n)){
            int degree = getDegree(matrix, n, new_x, new_y);
            if(degree <= min_degree1){
                min_degree1 = degree;
                id1 = i;
            }
        }
    }

    if(id1 == -1){
        std::cout << "no hay solucion " << std::endl;
        return false;
    }
    int n_x = curr_x + move_x[id1];
    int n_y = curr_y + move_y[id1];

    solve(n, matrix, n_x, n_y, pos + 1);
    return false;
}

void horse_9(int n, int x, int y){
    int pos_x = x;
    int pos_y = y;

    int** matrix = new int*[n];

    for(int i = 0; i < n; ++i) {
        *(matrix + i) = new int[n];
        for(int j = 0; j < n; ++j) {
            *(*(matrix + i) + j ) = -1;
        }
    }
    //print(n, matrix);
    int pos = 1; //Contador de las posiciones tomadas, se va reemplazando en la matriz.
    auto start = std::chrono::system_clock::now();
    solve(n, matrix, pos_x, pos_y, pos);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "tiempo " << elapsed_seconds.count() << std::endl;
}

int main(){
    horse_9(20, 0, 0);
}