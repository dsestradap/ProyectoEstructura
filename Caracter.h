#pragma once
class Caracter{
	char caracter;
	int frequencia;
	Caracter* izquierda;
	Caracter* derecha;

public:
	Caracter(int frequencia, Caracter* izquierda, Caracter* derecha);
	Caracter(char caracter, int frequencia);
	int getFrequencia();
	char getCaracter();
	Caracter* getDerecha();
	Caracter* getIzquierda();
	bool hoja();
};

