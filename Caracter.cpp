#include "Caracter.h"
Caracter::Caracter(char caracter, int frequencia)
	:caracter(caracter), frequencia(frequencia) {
}

Caracter::Caracter(int frequencia)
	: frequencia(frequencia) {
}

int Caracter::getFrequencia() { return frequencia; }
char Caracter::getCaracter() { return caracter; }
