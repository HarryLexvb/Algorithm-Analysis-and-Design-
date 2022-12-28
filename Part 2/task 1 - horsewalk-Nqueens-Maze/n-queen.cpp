#include <iostream>
#include <chrono>

void print(int **matrix, int n){
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if(*(*(matrix + j) + i ) == 0)
                std::cout << "." <<  "\t";
            else
                std::cout << "x" <<  "\t";
        }
        std::cout << std::endl;
    }
}

bool check(int **matrix, int r, int i, int N){
    for(int j = 0; j < N; ++j)
        if(*(*(matrix + j) + i ) == 1)//Barre verticales desde la posición [j][i] -> i = estático.
            return false;

    for(int j = 0; j < N; ++j)
        if(*(*(matrix + r) + j ) == 1)//Barre horizontales desde la posición [r][j] -> r = estático.
            return false;

    for(int j = 0; j < N; ++j)//Barre diagonales
        for(int k = 0; k < N; ++k)
            if (((*(*(matrix + j) + k )) == 1) and ((j + k == r + i) or (j - k == r - i)))
                return false;

    return true;
}

bool solve(int **matrix, int r, int x, int y, int N ){
    if(r == N and *(*(matrix + x) + y ) == 1){
        print(matrix, N); // llega a su fin, se imprime la solución
        return false;
    }
    for(int i = 0; i < N; ++i){
        if(check(matrix, r, i, N) or (x == r and y == i)){
            //La segunda condición solo se cumple cuando se verifica la posición inicial dentro del bucle.
            //r avanza en cuanto a filas disponibles, i avanza en columnas.
            matrix[r][i] = 1;
            bool l = solve(matrix, r + 1, x, y, N);
            if (l == 0)
                return false;
            if (x != r and y != i)
                *(*(matrix + r) + i ) = 0;
        }
    }
    return true;
}

void nqueens_9(int n, int x, int y ) {

    int** matrix = new int*[n];

    for(int i = 0; i < n; ++i) {
        *(matrix + i) = new int[n];

        for(int j = 0; j < n; ++j) {
            *(*(matrix + i) + j ) = 0;
        }
    }

    *(*(matrix + x) + y ) = 1;

    auto start = std::chrono::system_clock::now();
    solve(matrix, 0, x, y, n);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    //std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::cout << "tiempo " << elapsed_seconds.count() << std::endl;
}

int main() {
    nqueens_9(32, 1, 1);
}

