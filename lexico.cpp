#include<stdlib.h>
#include<iostream>
#include<string.h>
#include"listas.c"
#include"processor.h"

/*
@utor Fredy M

desonses@gmail.com

UAEM
*/

/*##########################################################################
Archivo que realiza el analisis sitactico de la expresion aritmetica y evaluacion, identifica las variables, 
fin de linea, parentesis, operandos y los separa(tokens), regresa una lista de las variables que se cargaron a la memoria, 
estas variables corresponden al lado derecho de la expresion, es decir, tomamos la expresion z=a+b;
la lista gresada corresponderia solo a las variables 'a' y 'b'.
############################################################################*/



/*
g++ -o lexico lexico.cpp
./lexico

*/

#define TAM 50
using namespace std;
/* Declaracion de variables globales y funciones */

char operadores[TAM];
char asignacion[TAM];
char VARIABLES[TAM];
char PARENTESIS[TAM];
char CADENA2[TAM];
int state;
char *op[5];
TLE *L=crearLista();

int Separar(char CADENA[]);
int valida(void);
char *Expr(void);
void Expr2();
char *cadenaizq(void);
void VaciaMemoria(void);


/*
int main(){
	state = -1;
	char expresion[TAM];
	int i=0;
	cout << "Introduzca una expresión aritmética: ";
    cin >> expresion;
	Separar(expresion);
	printf("Expresion a revisa: %s", Expr());
//	puts(CADENA);

}
*/

char *Expr(void){
	return (CADENA2);
}


void Expr2(){
	puts(CADENA2);
}


char *cadenaizq(void){
	return (asignacion);
}
/*
void VaciaMemoria(void){
	//Borrar(L);
}

*/

/******************************************************************/
/******************************************************************/

/*
La refuncion recibe la expresion a analizar y separa por tokens, identifica las variables de la expresion y las carga en memoria, cada variable hace uso de 32 bits en memoria, se da por hecho de que cada variable es de tipo Entero, se evalua la expresion haciendo uso de un afd.
*/

int Separar(char CADENA[]) {

	char *ptr = &CADENA[0];
	/*indices*/
	int a = 0; // operadores
	int b = 0; // variables
	int c = 0; // PARENTESIS
	int d = 0; // expresion que se analizara
   	int i; // i es un indice para la CADENA original
	state=-1;

	/*se hace uso de un puntero para recorrer la cadena, cada token se identifica a traves de su codigo ascii.
	Se usa una maquina de estados
	*/

   	for(i=0;i<strlen(CADENA);i++){
		//printf("%c\n", *(puntero+i));
		switch(*(ptr+i)){
			case 40: case 41: // PARENTESIS 
				if(state==2){
					//printf("PARENTESIS: %c\n", *(ptr+i));
					PARENTESIS[c++]=*(ptr+i);
					CADENA2[d++]=*(ptr+i);		
				}

				break;
			case 43: //> +
			case 45: //> -
			case 42: //> *
			case 47: //> /
			if(state==2){
				state=2;
				//printf("operador: %c\n", *(ptr+i));
				operadores[a++]=*(ptr+i);
				CADENA2[d++]=*(ptr+i);
				//meter operadores
			}
			
				break;
			case 48: case 49: case 50: case 51: case 52: // numeros
			case 53: case 54: case 55: case 56: case 57:
			if (state=-1){
				state=0;
			}
			if(state==2){
				state=0;
			}
			case 61://>> =
				if(state==1){
					state=2;
					//printf("asignacion: %c\n", *(ptr+i));
				}

				break;
			case 97: case 98: case 99: case 100: case 101: // letras a - s
			case 102: case 103: case 104: case 105: case 106:
			case 107: case 108: case 109: case 110: case 111:
			case 112: case 113: case 114: case 115: case 116:
				if(state==-1 || state==1){//no son variable
					state=1;
					asignacion[c++]=*(ptr+i);//variable de asignacion
				}
				if(state==2){// son VARIABLES de la expresion (parte derecha)
					state=2;
					//printf("variable: %c\n", *(ptr+i));
					CADENA2[d++]=*(ptr+i);
					VARIABLES[b]=*(ptr+i);

					/*se cargan en memoria las variables*/
					Insertar(L, 0, (char*)&VARIABLES[b++]);
				}
				if(state==3 || state==0){//estados de error en el afd
					state=0;
				}
				break;
			case 59:
				if(state==2){
					state=3;
					//printf("fin de linea: %c\n",*(ptr+i));
				}
				break;
		}
	}
}


/*indica si la expresion al final es valida o no*/

int valida(void){
	return((state==3)?1:-1);
}



/*########################################################################*/
/*############### EVALUACION DE LA EXPRESION ARITMETICA ##################*/
/*########################################################################*/

/*
Gramatica que evalua la expresion aritmetica a traves del metodo eval() de la clase processor
*/


float Processor::eval(){
    return E();
}

/******************************************************************/
/******************************************************************/

float Processor::E(){

    float t = T();
    return Ep(t);
}

/******************************************************************/
/******************************************************************/

float Processor::Ep(float tl){
  float tr;
  char op;
    while(str[pos]==' ') pos++; 
    op=str[pos];
    if (op!='+' && op!='-') return tl;
    pos++;
    tr = T();
    switch(op) {
    case '+': return(Ep(tl+tr));
    case '-': return(Ep(tl-tr));
    }
}

/******************************************************************/
/******************************************************************/

float Processor::T(){

    float f = F();
    return (Tp(f));
}

/******************************************************************/
/******************************************************************/

float Processor::Tp(float fl) {
  float fr;
  char op;

    //while(str[pos]==' ') pos++; 
    op=str[pos];
    if (op!='*' && op!='/') return fl;
    pos++;
    fr = F();
    switch(op) {
    case '*': return(Tp(fl*fr));
	case '/': return(Tp(fl/fr));
    }  

}

/******************************************************************/
/******************************************************************/

float Processor::F() {
  	char op;
	float result;
	float number=0.0;
  //while(str[pos]==' ') pos++;
  op=str[pos];
  if (op == '(') {
    pos++;
    result= E();
    //while(str[pos]==' ') pos++;
    if (str[pos]==')' ) {
      pos++;
      return result;
    }
	}

	else if(op=='a'){
		pos++;
		number=Eliminar(L,(char*)"a");
    	return (number);
 	}

	else if(op=='b'){
		pos++;
		number=Eliminar(L,(char*)"b");
    	return (number);
 	}

	else if(op=='c'){
		pos++;
		number=Eliminar(L,(char*)"c");
    	return (number);
 	}

	else if(op=='d'){
		pos++;
		number=Eliminar(L,(char*)"d");
    	return (number);
 	}
	else if(op=='e'){
		pos++;
		number=Eliminar(L,(char*)"e");
    	return (number);
 	}
	else if(op=='f'){
		pos++;
		number=Eliminar(L,(char*)"f");
    	return (number);
 	}
	else if(op=='g'){
		pos++;
		number=Eliminar(L,(char*)"g");
    	return (number);
 	}
	else if(op=='h'){
		pos++;
		number=Eliminar(L,(char*)"h");
    	return (number);
 	}
	else if(op=='i'){
		pos++;
		number=Eliminar(L,(char*)"i");
    	return (number);
 	}
	else if(op=='j'){
		pos++;
		number=Eliminar(L,(char*)"j");
    	return (number);
 	}
	else if(op=='k'){
		pos++;
		number=Eliminar(L,(char*)"k");
    	return (number);
 	}
	else if(op=='l'){
		pos++;
		number=Eliminar(L,(char*)"l");
    	return (number);
 	}
	else if(op=='m'){
		pos++;
		number=Eliminar(L,(char*)"m");
    	return (number);
 	}
	else if(op=='n'){
		pos++;
		number=Eliminar(L,(char*)"n");
    	return (number);
 	}
	else if(op=='o'){
		pos++;
		number=Eliminar(L,(char*)"o");
    	return (number);
 	}
	else if(op=='p'){
		pos++;
		number=Eliminar(L,(char*)"p");
    	return (number);
 	}
	else if(op=='q'){
		pos++;
		number=Eliminar(L,(char*)"q");
    	return (number);
 	}
	else if(op=='r'){
		pos++;
		number=Eliminar(L,(char*)"r");
    	return (number);
 	}
	else if(op=='s'){
		pos++;
		number=Eliminar(L,(char*)"s");
    	return (number);
 	}
	else if(op=='t'){
		pos++;
		number=Eliminar(L,(char*)"t");
    	return (number);
 	}

}




//~


