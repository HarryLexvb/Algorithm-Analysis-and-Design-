#include <iostream>

#include <chrono>
#include <sys/time.h>
#include <ctime>

using namespace std;


  void print_board(int tam, int **tablero) {
    cout<<"\nrecorrido: "<<endl;
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (tablero[i][j] < 10)
                cout << ' ';
            cout << tablero[i][j] << ' ';
        }
        cout << endl;
    }
    cout<<endl;
}

bool find_tour(int move_no, int current_row, int current_col, int tam, int *row_delta, int *col_delta, int **tablero) {

    if (move_no == tam * tam)
        return true;

    for (int move = 0; move < 8; move++) {
        int new_row = current_row + row_delta[move];
        int new_col = current_col + col_delta[move];

        if (new_row < 0 || new_row >= tam || new_col < 0 || new_col >= tam)
            continue;

        if (tablero[new_row][new_col] != 0)
            continue;

        tablero[new_row][new_col] = move_no + 1;
        if (find_tour(move_no + 1, new_row, new_col, tam, row_delta, col_delta, tablero))
            return true;
        tablero[new_row][new_col] = 0;
    }
    return false;
}




auto horse_12(const int tam, int pos_x, int pos_y) {
    auto start = std::chrono::high_resolution_clock::now();

  

    int **board = new int* [tam];
    for (int i = 0; i < tam; i++) {
        board[i] = new int[tam];
    }

  
    int row_delta[8] = {2, 1, -1, -2, -2, -1, 1, 2};
    int col_delta[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

    //tablero lleno de 0
    for (int row = 0; row < tam; row++)
        for (int col = 0; col < tam; col++)
            board[row][col] = 0;

    //inicializando la posicion
    board[pos_x][pos_y] = 1;

    
    if (find_tour(1, pos_x, pos_y, tam, row_delta, col_delta, board))
        print_board(tam, board);
    else
        cout << "No se encontro el camino\n";

    auto end = std::chrono::high_resolution_clock::now();
  auto int_s = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  
  cout<<"microsegundos: "<<int_s.count();
  return int_s;
}


