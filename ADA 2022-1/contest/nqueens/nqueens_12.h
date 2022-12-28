#include <iostream>
#include <stdio.h>

#include <chrono>
#include <sys/time.h>
#include <ctime>

using std::cout; using std::endl;


using namespace std;

void imprimir_tablero(int tablero[], int tam){
    cout<<"tablero: "<<endl;

    for (int i = 0; i < tam; i++){
  	    for (int j = 0; j < tam; j++){
            if(tablero[j] == i)
                cout<<"\tX";
            else
      	        cout<<"\t•";
        }
  	    printf("\n");
    }

    cout<<"\nCOORDENADAS: ";
    for(int i = 0; i < tam; i++)
        cout<<"["<<i+1<<","<<tablero[i]+1<<"]";
    cout<<endl;
}


bool verificar(int tablero[], int etapa){
    for (int i = 0; i < etapa; i++){
        if(tablero[i]==tablero[etapa] || abs(tablero[i]-tablero[etapa]) == abs(i-etapa)){
            return 0;
        }
    }
    return 1;
}

bool reinas(int tablero[], int tam, int etapa){
    int exito = 0;
    if (etapa < tam){
  	    tablero[etapa] = -1;

  	while(tablero[etapa] < tam-1 && !exito)
        {
            tablero[etapa] = tablero[etapa]+1;
            if (verificar(tablero, etapa))
            {
                if (etapa < tam-1 ) 
                    exito = reinas(tablero, tam, etapa+1);
                else
                    exito = 1;
            }
  	    }
  	    return exito;
	}
    return 0;
}




auto queens_12(int tam){
    //medicion de tiempo
    auto start = std::chrono::high_resolution_clock::now();

    //tablero y algoritmo
    int tablero[tam];
    reinas(tablero,tam,0);
  
    //impresion
    imprimir_tablero(tablero,tam);

    //tiempo
    auto end = std::chrono::high_resolution_clock::now();
  auto int_s = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  cout<<"microsegundos: "<<int_s.count();
  return int_s;
}

