#include "Caracter.h"

Caracter::Caracter(int frequencia, Caracter* izquierda, Caracter* derecha) 
	: frequencia(frequencia), izquierda(izquierda), derecha(derecha){
	caracter = '\0';
}

Caracter::Caracter(char caracter, int frequencia)
	:caracter(caracter), frequencia(frequencia) {
	izquierda = nullptr;
	derecha = nullptr;

}

int Caracter::getFrequencia() { return frequencia; }
char Caracter::getCaracter() { return caracter; }

Caracter* Caracter::getDerecha() { return derecha; }
Caracter* Caracter::getIzquierda() { return izquierda; }
bool Caracter::hoja(){
	if (izquierda == nullptr && derecha == nullptr)
		return true;
	return false;
}
