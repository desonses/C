#include<iostream>
#include<stdlib.h>

/*
@utor Fredy M

desonses@gmail.com

UAEM
*/

/*
gramatica definida para reconocer expresiones del tipo (a+b)*a+b es sensible a espacios
dada la gramatica  siguiente:
E -> E+T | E-T | T |
T -> T*F | E/F | F |
F -> (E) | a | b |...

la gramatica sigue la regla de produccion A-> Ax|B
por lo que eliminamos hacia la izquierda

A  -> BA'
A' -> xA'

por lo que tendremos 

 E -> TE
 E -> +(TE)
 T -> FT
 T -> *(FT)
 F -> (E)|a|b| -F

la expresion es valida si termina con ')' o alguna variable a,b,... esta gramatica se utilizara para realizar la 
evaluacion de la expresion aritmetica

*/



/*

compilar: g++ -o sintactico sintactico.cpp
ejecutar: ./sintactico

*/

using namespace std;

/*Declaracion de variable globales y funciones*/

char entrada[50];
int estado;
char *ca=entrada;

void E();
void Eprima();
void T();
void Tprima();
void R();
void Rprima();
void W();
void Wprima();
void F();
void Aceptado();
char *Revisa(char expresion[]);
int Valida();

/*
int  main(){

	cout<<"ingrese la expresion:" ;
	cin>>entrada;
	E();
	Valida();
}

*/

/*
Func que recibe la cadena del tipo a+b*(a-b), la gramatica verifica si la expresion ingresa es correcta sintacticamente

*/
char *Revisa(char expresion[]){
	strcpy(entrada, expresion);
	E();
}

void E(){// E -> TE

	T();
	Eprima();
}

void Eprima(){ // E -> +TE

	if(*ca=='+'){
		Aceptado();
		estado=1;
		ca++;
		E();
		//T();
		//Eprima();
	}

	else if(*ca=='-'){
		Aceptado();
		estado=1;
		ca++;
		E();
		//T();
		//Eprima();
	}
	
}

void T(){ // T -> FT'

	F();
	Tprima();

}

void Tprima() {// T -> *FT

	if(*ca=='*'){
		Aceptado();
		estado=1;
		ca++;
		T();
		//F();
		//Tprima();
	}
	else if(*ca=='/'){
		Aceptado();
		estado=1;
		ca++;
		T();
		//F();
		//Tprima();
	}
}


void F() {// F -> (E) | a,b,... | -F

	if(*ca=='a' || *ca=='b'|| *ca=='c'|| *ca=='d'|| *ca=='e'|| *ca=='f'|| *ca=='g'|| *ca=='h'|| *ca=='i'|| *ca=='j'|| *ca=='k'|| *ca=='l'|| *ca=='m'|| *ca=='n'|| *ca=='o'|| *ca=='p'|| *ca=='q'|| *ca=='r'|| *ca=='s'|| *ca=='t'){	// a o b...
		Aceptado();
		estado=1;
		ca++;
	}
	
	else if(*ca=='-'){
			Aceptado();
			estado=1;
			ca++;
			F();
		}
	

	else if (*ca=='('){ // parentesis ) y (
			Aceptado();
			estado=1;
			ca++;
			E();
		
			if (*ca==')'){ // parentesis
				Aceptado();
				estado=1;
				ca++;
			}
		
			else{
				cout<<"Expresion no valida..."<<endl;
				estado=0;
				exit(0);
			}
	}
	else{
		cout<<"Expresion no valida..."<<endl;
		estado=0;
		exit(0);
	}
}

void Aceptado(void) {// caracter actual aceptado
	cout<<"caracter: "<< *ca << " ,valido"<<endl;
}

int Valida(void){
	return((estado==1)?1:-1);
}





