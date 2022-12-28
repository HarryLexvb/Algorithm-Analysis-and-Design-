#include <iostream>
#include <chrono>
#include<vector>
using namespace std;
using namespace chrono;
typedef std::chrono::high_resolution_clock Clock;
//RELLENAR
void rellenar_mapa(int** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }
    }
}
void rellenar_list(int* a, int* b) {
    int cam_x[8] = { -1, 1, 2, 2,  1, -1, -2, -2 };
    int cam_y[8] = { 2,  2, 1, -1, -2, -2, -1, 1 };
    for (int i = 0; i < 8; i++) {
        a[i] = cam_x[i];
        b[i] = cam_y[i];
    }
}

//                  //

//POSIBLES

bool rango(int x, int y, int n) {
    if (x >= n || x < 0 || y >= n || y < 0) {
        return false;
    }

    return true;
}

bool dentro(int** t, int x, int y) {
    if (t[x][y] != 0) {
        return false;
    }
    return true;
}

//               //


void print(int** a, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << "\t";

        }
        cout << endl;
    }
    cout << endl << endl;
}


void print_vector(vector<int*> t1) {
    int* p;

    for (int i = 0; i < t1.size(); i++) {
        p = t1[i];
        cout << p[0] << " ";
    }

    cout << endl << endl;
}

// ORDENAR VECTOR DE PUNTEROS

void ordenar(vector<int*>& t1) {

    int i, j;
    int* arr_i;
    int* arr_j;
    int* temp;

    for (i = 0; i < t1.size(); i++)
    {
        for (j = i + 1; j < t1.size(); j++)
        {
            arr_i = t1[i];
            arr_j = t1[j];

            if (arr_i[0] > arr_j[0])
            {
                temp = arr_i;
                t1[i] = arr_j;
                t1[j] = temp;
            }

            arr_i = t1[i];
            arr_j = t1[j];
        }
    }

}



void pop_front(vector<int*>& v) {
    if (v.size() > 0) {
        v.erase(v.begin());
    }
}

bool sub_caballo(int n, int x, int y, int** t, int cont, int* l1, int* l2) {


    int sx, sy;

    vector<int*> t1;

    t[x][y] = cont;

    if (cont == (n * n))
        return true;

    for (int i = 0; i < 8; i++) {
        int px, py;
        px = x + l1[i];
        py = y + l2[i];


        if (rango(px, py, n) && dentro(t, px, py)) {
            int contando = 0;
            for (int j = 0; j < 8; j++) {
                sx = px + l1[j];
                sy = py + l2[j];
                if (rango(sx, sy, n) && dentro(t, sx, sy))
                    contando = contando + 1;
            }


            int* l3 = new int[2];
            l3[0] = contando;
            l3[1] = i;

            t1.push_back(l3);
        }

    }




    if (t1.size() > 0) {
        ordenar(t1);
        int* t2 = t1.front();
        pop_front(t1);
        int px, py;
        px = l1[t2[1]];
        py = l2[t2[1]];



        if (sub_caballo(n, x + px, y + py, t, cont + 1, l1, l2))
            return true;
    }

    t[x][y] = 0;
    return false;


}



long long int horse_3(int n, int x, int y) {

    auto t1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    if (x > n || y > n)return false;
    int** t = new int* [n];
    for (int i = 0; i < n; ++i)
        t[i] = new int[n];

    int* l1 = new int[8];
    int* l2 = new int[8];

    rellenar_list(l1, l2);

    rellenar_mapa(t, n);

    
    sub_caballo(n, x, y, t, 1, l1, l2);
    print(t, n);


    
    auto t2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    long long int t3 = t2 - t1;
    
    return t3;
}


