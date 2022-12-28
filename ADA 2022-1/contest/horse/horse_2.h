#include <iostream>
#include <chrono>
#include <iostream>
#include <ctime>
#include <math.h>

using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


using namespace std;


static int movimientos_x[8] = { 1,1,2,2,-1,-1,-2,-2 };
static int movimientos_y[8] = { 2,-2,1,-1,2,-2,1,-1 };

bool limites(int x, int y,int N)
{
    //verificamos la posicion y si esta dentro de los limites del array N*N
    return ((x >= 0 && y >= 0) && (x < N&& y < N));
}

bool esta_libre(int a[], int x, int y,int N)
{
    //verificamos que este dentro de los limtes de nuestro array y tambien que no tenga ningun numero (que no este marcado) osea que sea -1
    return (limites(x, y,N)) && (a[y * N + x] < 0);
}

int grados(int a[], int x, int y,int N)
{
    //vemos cuantos movimientos puede hacer y dependiendo de eso vamos a sumar a contar 1 hasta que recorramos todos los movimientos y tengamos el grado
    int contar = 0;
    for (int i = 0; i < 8; i++)
    {
        if (esta_libre(a, (x + movimientos_x[i]), (y + movimientos_y[i]), N))
        {
            contar++;
        }
    }
    return contar;
}

bool movimiento_valido(int a[], int* x, int* y, int N,int pasada)
{
    int aux;
    int aux_x;
    int aux_y;
    int indice_del_menor_grado = -1; //indice de los movimientos (array de 8 movimientos)
    int menor_grado = (N + 1);
    

    int start = pasada; //punto de inicio para empezar a comparar con los movimientos movimientos_x[pasada]
    for (int count = 0; count < 8; count++)
    {
        int i = (start + count) % 8;
        aux_x = *x + movimientos_x[i];
        aux_y = *y + movimientos_y[i];
        if ((esta_libre(a, aux_x, aux_y,N)) && (aux = grados(a, aux_x, aux_y,N)) < menor_grado) //comprobamos que sea una posicion valida (dentro de los limites y sin numero)
        {
            indice_del_menor_grado = i;
            menor_grado = aux;
        }
    }

    // no hay a donde moverse, es decir que el indice de menor grado sigue siendo -1
    if (indice_del_menor_grado == -1)
    {
        return false;
    }

    // generamos nuevas posiciones sumando los valores correspondientes teniendo en cuenta el menor grado y el indice con el que llegamos a este
    aux_x = *x + movimientos_x[indice_del_menor_grado];
    aux_y = *y + movimientos_y[indice_del_menor_grado];

    // le agregamos el valor numerico que le correspondia
    a[aux_y * N + aux_x] = a[(*y) * N + (*x)] + 1;

    // copiamos las nuevas posiciones a los punteros
    *x = aux_x;
    *y = aux_y;

    return true;
}

void print(int a[],int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout<< a[j * N + i]<<'\t';
        cout << endl;
    }
}

// Ennumeramos el camino usando la Heuristica de warnsdorff
bool caballo(int N, int posicionx, int posiciony, int pasada)
{
    // llenamos todo de -1
    int* a;
    a = new int[N*N];
    for (int i = 0; i < N * N; ++i)
        a[i] = -1;

    int x = posicionx, y = posiciony;
    a[y * N + x] = 1; // Marcamos la primera celda

    // Heurisica de Warnsdorff's
    for (int i = 0; i < N * N - 1; ++i)
        if (movimiento_valido(a, &x, &y,N,pasada) == 0)
            return false;

	print(a, N);
    return true;
}

double horse_2(int N, int posx, int posy)
{
	auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	int pasada = 0;
    while (!caballo(N,posx,posy,pasada) && pasada<16)
    {	
		pasada++;
    }
	auto millisec_since_epoch2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	double tiempo = millisec_since_epoch2 - millisec_since_epoch;
	//cout<<"time: "<<tiempo<<endl;
	return tiempo;
}

