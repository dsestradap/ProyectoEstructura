#include <iostream>
#include <cstring>
#include <queue>
#include "Caracter.h"
#include <vector>
using namespace std;

//Comparador para la cola
struct Comparador {
	bool operator()(Caracter* a, Caracter* b) {
		return a->getFrequencia() > b->getFrequencia();
	}
};

int main(){
	cout << "Ingrese una cadena (minimo 20 caracteres): ";
	char cadena[100];
	cin.getline(cadena, 100);

	//--- CREAR MIN-HEAP ---
	priority_queue<Caracter*, vector<Caracter*>, Comparador> cola;

	//-----CALCULAR FREQUENCIAS---
	int longitud = strlen(cadena);
	int contador;

	//mayuscula
	for (char i = 'A'; i <= 'Z'; ++i){
		int frequencia = 0;
		for (int j = 0; j < longitud; j++){
			if (cadena[j] == i)
				frequencia++;
		}
		cola.push(new Caracter(i, frequencia));
	}
	//minuscula
	for (char i = 'a'; i <= 'z'; ++i) {
		int frequencia = 0;
		for (int j = 0; j < longitud; j++) {
			if (cadena[j] == i)
				frequencia++;
		}
		cola.push(new Caracter(i, frequencia));
	}
	//espacio
	int frequenciaEspacios = 0;
	for (int i = 0; i < longitud; i++) {
		if (cadena[i] == ' ')
			frequenciaEspacios++;
	}
	cola.push(new Caracter(' ', frequenciaEspacios));

	//-----CREAR ARBOL----
	while (cola.size() > 1) {
		Caracter* izquierda = cola.top();
		cola.pop();
		Caracter* derecha = cola.top();
		cola.pop();
		cola.push(new Caracter(izquierda->getFrequencia() + derecha->getFrequencia(), izquierda, derecha));
	}

	Caracter* raiz = cola.top();

}