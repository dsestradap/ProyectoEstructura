#include <iostream>
#include <cstring>
#include "Caracter.h"
#include <vector>
using namespace std;

int main(){
	cout << "Ingrese una cadena (minimo 20 caracteres): ";
	char cadena[100];
	cin.getline(cadena, 100);
	vector <Caracter*> caracteres;

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
		caracteres.push_back(new Caracter(i, frequencia));
	}
	//minuscula
	for (char i = 'a'; i <= 'z'; ++i) {
		int frequencia = 0;
		for (int j = 0; j < longitud; j++) {
			if (cadena[j] == i)
				frequencia++;
		}
		caracteres.push_back(new Caracter(i, frequencia));
	}
	//espacio
	int frequenciaEspacios = 0;
	for (int i = 0; i < longitud; i++) {
		if (cadena[i] == ' ')
			frequenciaEspacios++;
	}
	caracteres.push_back(new Caracter(' ', frequenciaEspacios));
}