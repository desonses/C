#ifndef PROCESSOR_H 
#define PROCESSOR_H
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctime>
#include<stdlib.h>

/*
@utor Fredy M

desonses@gmail.com

UAEM
*/

/*#########################################################################
Archivo que contiene la clase, variables de instancia y metodos para la evaluacion de
 la expresion aritmetica
###########################################################################*/

using namespace std;

class Processor{
	public:
		Processor(string s): str(s), pos(0){};
		float eval();
	
	private:
		Processor(){};
		float E();
		float T();
		float Ep(float t);
		float Tp(float f);
		float F();
		string str;
		int pos;
};

#endif
