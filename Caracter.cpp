#include "Caracter.h"

Caracter::Caracter(int frequencia, Caracter* izquierda, Caracter* derecha) 
	: frequencia(frequencia), izquierda(izquierda), derecha(derecha){
}

Caracter::Caracter(char caracter, int frequencia)
	:caracter(caracter), frequencia(frequencia) {
}

int Caracter::getFrequencia() { return frequencia; }
char Caracter::getCaracter() { return caracter; }
