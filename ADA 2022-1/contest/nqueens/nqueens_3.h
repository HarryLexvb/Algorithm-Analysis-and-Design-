#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;
typedef std::chrono::high_resolution_clock Clock;
void rellenar_mapa(char** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = '.';

        }
    }
}

void print(char** a, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << " ";

        }
        cout << endl;
    }
    cout << endl << endl;
}

bool rango(int x, int y, int n, int c_x, int c_y) {
    if (x + c_x >= n || x + c_x < 0 || y + c_y >= n || y + c_y < 0) {
        return false;
    }
    return true;
}

bool coincide_hor(char** a, int n, int x, int y) {
    if (y >= 0) {
        int h_d = y;
        while (h_d < n - 1) {
            h_d++;
            if (a[x][h_d] == 'x')
                return false;
        }
    }
    if (y < n) {
        int h_i = y;
        while (h_i > 0) {
            h_i--;
            if (a[x][h_i] == 'x')
                return false;
        }
    }

    return true;
}


bool coincide_ver(char** a, int n, int x, int y) {
    if (x >= 0) {
        int v_u = x;
        while (v_u > 0) {
            v_u--;
            if (a[v_u][y] == 'x')
                return false;
        }
    }
    if (x < n) {
        int v_d = x;
        while (v_d < n - 1) {
            v_d++;
            if (a[v_d][y] == 'x')
                return false;
        }
    }
    return true;
}
bool coincide_diag1(char** a, int n, int x, int y) {
    if (x < n && y >= 0) {
        int dx = x, dy = y;
        while (dx < n - 1 && dy < n - 1) {
            dx++;
            dy++;
            if (a[dx][dy] == 'x') {
                return false;
            }
        }
    }
    if (x >= 0 && y < n) {
        int dx = x, dy = y;
        while (dx > 0 && dy > 0) {
            dx--;
            dy--;
            if (a[dx][dy] == 'x') {
                return false;
            }
        }
    }
    return true;
}
bool coincide_diag2(char** a, int n, int x, int y) {

    if (x >= 0 && y >= 0) {
        int dx = x, dy = y;
        while (dx > 0 && dy < n - 1) {
            dx--;
            dy++;
            if (a[dx][dy] == 'x')
                return false;
        }
    }

    if (x < n && y < n) {
        int dx = x, dy = y;
        while (dx < n - 1 && dy >0) {
            dx++;
            dy--;
            if (a[dx][dy] == 'x')
                return false;
        }
    }

    return true;
}


bool nqueens(char** a, int n, int x, int y, int cont) {
    int cam_x[80] = { 2,1,-1,-2,-2,-1,1,2, 3, 1, -1, -3,-3, -1, 1, 3, 3, 2, -2, -3, -3, -2, 2, -3, 4, 1, -1, -4, -4, -1, 1, 4, 4, 2, -2, -4, -4, -2, 2, 4, 4, 3, -3, -4, -4, -3,  3,  4, 5, 1, -1, -5, -5, -1,  1,  5, 5, 2, -2, -5, -5, -2,  2,  5, 5, 3, -3, -5, -5, -3,  3,  5, 5, 4, -4, -5, -5, -4,  4,  5 };
    int cam_y[80] = { 1,2,2,1,-1,-2,-2,-1, 1, 3, 3, 1,-1, -3, -3, -1, 2, 3, 3,2, -2, -3, -3, -2, 1, 4, 4, 1, -1, -4, -4, -1, 2, 4, 4, 2, -2, -4, -4, -2, 3, 4,  4,  3, -3, -4, -4, -3, 1, 5,  5,  1, -1, -5, -5, -1, 2, 5,  5,  2, -2, -5, -5, -2, 3, 5,  5,  3, -3, -5, -5, -3, 4, 5,  5,  4, -4, -5, -5, -4 };



    a[x][y] = 'x';

  
    if (cont == 1 && coincide_ver(a, n, x, y) && coincide_hor(a, n, x, y) && coincide_diag1(a, n, x, y) && coincide_diag2(a, n, x, y))
    {
        return true;
    }


    if (coincide_ver(a, n, x, y) && coincide_hor(a, n, x, y) && coincide_diag1(a, n, x, y) && coincide_diag2(a, n, x, y)) {
        for (int i = 0; i < 32; i++) {
            if (rango(x, y, n, cam_x[i], cam_y[i]))
                if (a[x + cam_x[i]][y + cam_y[i]] == '.')
                    if (nqueens(a, n, x + cam_x[i], y + cam_y[i], cont - 1))
                        return true;

        }
    }

    a[x][y] = '.';
    return false;
}

long long int nqueens_3(int n, int x, int y)
{
    auto t1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    

    if (x > n || y > n)return 1;
    char** a = new char* [n];
    for (int i = 0; i < n; ++i)
        a[i] = new char[n];

    rellenar_mapa(a, n);
    
    if (nqueens(a, n, x , y , n))
    {
        print(a, n);
    }
    else {
        cout << "no resuelto";
    }
   
    
    auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    long long int t3= t2 - t1;
       
    
        
    return t3;
       
}
