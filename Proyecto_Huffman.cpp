#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include "Caracter.h"
using namespace std;

//Generador de codigos
void generarCodigo(map<Caracter*, string>& codigos, Caracter* nodo, string codigoGenerado) {
	if (nodo->hoja()) {
		codigos[nodo] = codigoGenerado;
		codigoGenerado = "";
		return;
	}
	generarCodigo(codigos, nodo->getIzquierda(), codigoGenerado + "0");
	generarCodigo(codigos, nodo->getDerecha(), codigoGenerado + "1");
}

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
	while (strlen(cadena) <= 19) {
		cout << "Error! Ingrese una cadena con un minimo de 20 caracteres: ";
		cin.getline(cadena, 100);
	}

	//--- CREAR MIN-HEAP ---
	priority_queue<Caracter*, vector<Caracter*>, Comparador> cola;

	//-----CALCULAR FREQUENCIAS---
	int longitud = strlen(cadena);

	//mayuscula
	for (char i = 'A'; i <= 'Z'; ++i){
		int frequencia = 0;
		for (int j = 0; j < longitud; j++){
			if (cadena[j] == i)
				frequencia++;
		}
		if(frequencia > 0)
			cola.push(new Caracter(i, frequencia));
	}
	//minuscula
	for (char i = 'a'; i <= 'z'; ++i) {
		int frequencia = 0;
		for (int j = 0; j < longitud; j++) {
			if (cadena[j] == i)
				frequencia++;
		}
		if (frequencia > 0)
			cola.push(new Caracter(i, frequencia));
	}
	//espacio
	int frequenciaEspacios = 0;
	for (int i = 0; i < longitud; i++) {
		if (cadena[i] == ' ')
			frequenciaEspacios++;
	}
	if (frequenciaEspacios > 0)
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

	//---ASIGNAR CODIGOS----
	map <Caracter*, string> codigos;
	generarCodigo(codigos, raiz, "");

	//----IMPRIMIR RESULTADOS CODIFICADOS---
	cout << "RESULTADOS CODIFICADOS" << endl;
	for (auto& caracter : codigos){
		//hacer setw
		if(caracter.first->getCaracter() == ' ')
			cout << "Caracter: _ || Frequencia: " << caracter.first->getFrequencia() << " || Codigo: " << caracter.second << endl;
		else 
			cout << "Caracter: " << caracter.first->getCaracter() << " || Frequencia: " << caracter.first->getFrequencia() << " || Codigo: " << caracter.second << endl;
	}

	//---CADENA CODIFICADA---
	string cadenaCodificada = "";
	cout << "CADENA CODIFICADA: " << endl;
	for (int i = 0; i < longitud; i++) {
		for (auto& nodo : codigos) {
			if (cadena[i] == nodo.first->getCaracter()) {
				cadenaCodificada += nodo.second;
				break;
			}	
		}
	}
	cout << cadenaCodificada << endl;

	//--- DECODIFICAR CADENA ---
	string cadenaDecodificada = "";
	Caracter* actual = raiz;
	for (int i = 0; i < cadenaCodificada.length(); i++) {
		char bit = cadenaCodificada[i];
		if (bit == '0')
			actual = actual->getIzquierda();
		else
			actual = actual->getDerecha();

		if (actual->hoja()) {
			cadenaDecodificada += actual->getCaracter();
			actual = raiz;
		}
	}
	cout << "CADENA DECODIFICADA: " << cadenaDecodificada << endl;
}//fin main