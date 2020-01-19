#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctime>
#include<stdlib.h>
#define BLOCK 50

/*
@utor Fredy M

desonses@gmail.com

UAEM
*/


/*
compilar: g++ -o cadenas cadenas.cpp
ejecutar: ./cadenas

*/





/*
Genera cadenas aritmeticas aleatorias del tipo a=(a+b); en el mejor de los casos y regresa dicha cadena para ser evaluada, la longitud puede ser modificada en el ciclo while.

*/


using namespace std;
/*
declaracion de variables, arrays de cadenas(variables), declaracion de funciones y operadores aritmeticos
*/
char op1[]="+"; char op2[]="-"; char op3[]="*"; char op4[]="/";
char asign[]="=";
char termina[]=";";
char a[]="a"; char b[]="b"; char c[]="c"; char d[]="d"; char e[]="e";
char f[]="f"; char g[]="g"; char h[]="h"; char i[]="i"; char j[]="j";
char k[]="k"; char l[]="l"; char m[]="m"; char n[]="n"; char o[]="o";
char p[]="p"; char q[]="q"; char r[]="r"; char s[]="s"; char t[]="t";

char parent1[]="("; char parent2[]=")";
char expresion[BLOCK];

char *operador[]={op1, op2, op3, op4};
char *variables[]={a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t};
char *parentesis[]={parent1, parent2};

char *RandomVar(void);
char *Cadena(void);
char *RandomOp(void);
char *RandomParentesis(void);
void Nuevo(void);

//TLE *L=crearLista();

/*
int main(void){ ////// MAIN
	srand((int)time(0)); 
	printf("aleatorio: %s\n", cadena());
	Imprimir(L,Ascendente);

return 0;

}
*/


/********************************************************/
/*
Genera una expresion aritmetica, el primer ciclo genera la parte izquierda de la igualdad y el segundo, la parte derecha
*/
char *Cadena(void){
	int i=0;
	int j=0;

	while(j++<5){
		strcat(expresion,RandomVar());			
	}
	strcat(expresion,asign);	
	
	while(i++<3){
		
		strcat(expresion,RandomParentesis());
		char *var=RandomVar();
		strcat(expresion,var);
		strcat(expresion,RandomOp());
		char *VAR=RandomVar();
		strcat(expresion,VAR);
		strcat(expresion,RandomParentesis());
		strcat(expresion,RandomOp());
		
	}
	strcat(expresion,termina);
	return(expresion);	
}

/********************************************************/
/*
Funciones para elejir de manera aletarias variables, operadores, y parantesis de la expresion
*/

char *RandomParentesis(void){
	return (parentesis[rand()&1]);
}

/********************************************************/
char *RandomOp(void){
	return (operador[rand()%3]);
}

/********************************************************/

char *RandomVar(void){
//Numero aleatorio
	return (variables[rand()%20]);
}
/********************************************************/

void Nuevo(void){
	expresion[0]=0;
}
/********************************************************/




