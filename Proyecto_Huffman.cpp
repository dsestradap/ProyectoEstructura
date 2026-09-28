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

void liberarMemoria(Caracter* nodo) {
	if (!nodo->hoja()) {
		liberarMemoria(nodo->getIzquierda());
		liberarMemoria(nodo->getDerecha());
	}
	delete nodo;
}

bool caracteresValidos(string cadena) {
	for (int i = 0; i < cadena.length(); i++){
		char car = cadena[i];
		if (!((car >= 'A' && car <= 'Z') || (car >= 'a' && car <= 'z') || car == ' '))
			return false;
	}
	return true;
}

int main(){
	bool continuar = true;
	while (continuar) {
		string cadena;

		bool valida = false;
		while (!valida) {
			cout << "Ingrese una cadena (minimo 20 caracteres): ";
			getline(cin, cadena);
			if (cadena.length() < 20) 
				cout << "Error! La cadena debe tener un minimo de 20 caracteres." << endl;
			else if (!caracteresValidos(cadena))
				cout << "Error! La cadena contiene caracteres invalidos." << endl;
			else
				valida = true;
		}
		cout << endl;

		//--- CREAR MIN-HEAP ---
		priority_queue<Caracter*, vector<Caracter*>, Comparador> cola;

		//-----CALCULAR FREQUENCIAS---
		int longitud = cadena.length();

		//mayuscula
		for (char i = 'A'; i <= 'Z'; ++i) {
			int frequencia = 0;
			for (int j = 0; j < longitud; j++) {
				if (cadena[j] == i)
					frequencia++;
			}
			if (frequencia > 0)
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
		if (codigos.size() == 1)
			codigos.begin()->second = "0";

		//----IMPRIMIR RESULTADOS CODIFICADOS---
		cout << "RESULTADOS CODIFICADOS" << endl;
		for (auto& caracter : codigos) {
			if (caracter.first->getCaracter() == ' ')
				cout << "Caracter: _ || Frequencia: " << caracter.first->getFrequencia() << " || Codigo: " << caracter.second << endl;
			else
				cout << "Caracter: " << caracter.first->getCaracter() << " || Frequencia: " << caracter.first->getFrequencia() << " || Codigo: " << caracter.second << endl;
		}
		cout << endl;

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
		cout << cadenaCodificada << endl << endl;

		//--- DECODIFICAR CADENA ---
		string cadenaDecodificada = "";
		Caracter* actual = raiz;
		for (int i = 0; i < cadenaCodificada.length(); i++) {
			if (!raiz->hoja()) {
				if (cadenaCodificada[i] == '0')
					actual = actual->getIzquierda();
				else
					actual = actual->getDerecha();
			}

			if (actual->hoja()) {
				cadenaDecodificada += actual->getCaracter();
				actual = raiz;
			}
		}
		cout << "CADENA DECODIFICADA: " << cadenaDecodificada << endl << endl;

		if (cadenaDecodificada == cadena)
			cout << "La cadena de bits coincide con la cadena original.";
		else
			cout << "ERROR! La cadena de bits NO coincide con la cadena original.";
		cout << endl << endl;

		///---TAMAÑOS Y AHORRO----
		double longitud_original = longitud * 8;
		double longitud_codificada = cadenaCodificada.length();
		double porcentajeAhorro = (longitud_original - longitud_codificada) / longitud_original * 100;

		cout << "Tamanio original en bits: " << longitud_original << endl;
		cout << "Tamanio comprimido en bits: " << longitud_codificada << endl;
		cout << "Porcentaje del ahorro: " << porcentajeAhorro << "%" << endl << endl;

		//---LIBERAR MEMORIA---
		liberarMemoria(raiz);

		//--PROBAR OTRA CADENA ---
		cout << "Desea probar otra cadena (1. Si, 2. No): ";
		int continuarResp;
		cin >> continuarResp;
		cin.ignore();
		cout << endl;
		while (continuarResp != 1 && continuarResp != 2) {
			cout << "Error! Ingrese una opcion correcta." << endl;
			cout << "Desea probar otra cadena(1. Si, 2. No) : ";
			cin >> continuarResp;
			cin.ignore();
		}
		continuar = continuarResp == 1 ? true : false;
	}//while continuar
}//fin main