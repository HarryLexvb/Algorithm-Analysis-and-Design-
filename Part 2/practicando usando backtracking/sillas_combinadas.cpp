#include <iostream>
#include <queue>
#include <stack>
//restricciones, rojo no se sentara en la silla 1 y  y el amarillo no se sentara en al silla 2
using namespace std; 

int count = 0; 

void printPila(stack<char> s){
	stack<char> aux; 
	while(!s.empty()){
		cout << "\t" << s.top(); 
		aux.push(s.top()); 
		s.pop(); 
	}

	while(!s.empty()){ 
		s.push(aux.top()); 
		aux.pop(); 
	}

	cout << "\n"; 
}

void back(int i, int n, stack<char> pila, queue<char> cola){
	if(i == n){
		count++; 
		cout << count << " . "; 
		printPila(pila);
	}
	else{
		if(!((i == 1 and cola.front() == 'a') or (i == 0 and cola.front() == 'r'))){ // para las restrcciones solo metemos todo el for dentro de un if 
			for (int j = i; j < n; ++j) // con cada for nos movemos a los costados 
			{
				pila.push(cola.front());
				cola.pop();

				//nos movemos hacia abajo con la recursividad
				back(i+1, n, pila, cola); 

				// sacamos objeto de la pila 
				cola.push(pila.top());
				pila.pop();
			}
		}else{ // y este else tambien se agrega si es que hay restrcciones 
			cola.push(cola.front()); 
			cola.pop(); 
		}
	}

}

int main(){

	queue<char> cola; 
	stack<char> pila;

	cola.push('a');  
	cola.push('n');  
	cola.push('r');

	int i = 0; 
	back(i, cola.size(), pila, cola);  

}