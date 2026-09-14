#pragma once
class Caracter{
	char caracter;
	int frequencia;

public:
	Caracter(char caracter, int frequencia);
	Caracter(int frequencia);
	int getFrequencia();
	char getCaracter();
};

