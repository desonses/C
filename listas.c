#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>


#define Ascendente 1
#define INICIO 1
#define BITS 32

/*
@utor Fredy M

desonses@gmail.com

UAEM
*/

/*############################################################################
Archivo que contiene la estrutura de tipo lista doblemente ligada, realiza la reserva de memoria para 
un tipo de dato con 4 parametros, (a,0,1,32), este apartado simula el almacenamiento en memoria de las variables
(nombre de la variable, valor(tamaño en memoria), inicio de bloque(dir), fin de bloque(dir)), respectivamente,
simula el uso de memoria de una variable en sistema. 

En nuestro ejemplo la variable se llama "a", ocupa 0 kb, e inicia en la direccion de memoria 1 y termina en 32.

Realiza operaciones primarias, insertar en la lista y eliminar de la lista, ademas de una funcion de desfragmentar y 
modificar el *valor de la variable.
##############################################################################*/



/*

gcc -o listas listas.c
./listas

*/


//*****************************************************************//
//*****************************************************************//

/*estructura de tipo lista doblemente ligada con 4 campos*/
typedef struct Nodo{
	int dato;
	int start, end;
	char var[5];
 	struct Nodo *siguiente;
	struct Nodo *anterior;

}TNodo;

//*****************************************************************//
//*****************************************************************//

/*estrutura auxiliar para manipular los nodos de la lista*/

typedef struct LE{ // struct TNodo *inicio
	TNodo *inicio;
}TLE;

//*****************************************************************//
//*****************************************************************//

/* Declaracion de funciones y variables */

TNodo *crearNodo(int x, char var[]);
TLE *crearLista();
void Insertar(TLE *lista, int x, char var[]);
static int Eliminar(TLE *lista, char dato[]);
void Borrar(TLE *lista);
void Imprimir(TLE *lista , int Orden );
void Vacia(TLE *lista);
void desfragmentar (TLE *lista);
void ModificaVar(TLE *lista);


//*****************************************************************//
//*****************************************************************//

/*
Func que crea un nodo en memoria, realiza la reserva de memoria, segun el tam de la estructura, inicializa los apuntadores al nodo siguiente y anterior, regresa un nodo del tipo de la estrutura
*/

TNodo *crearNodo(int x, char var[]){

	TNodo *nodo = (TNodo*)malloc(sizeof(TNodo));
 	nodo->dato = x;
	strcpy(nodo->var, var);
	nodo->siguiente = NULL;
 	nodo->anterior = NULL;
 	return nodo;

}

//*****************************************************************//
//*****************************************************************//

/* funcion que crea la lista que contendra los nodos, crea un nodo apuntador al primer elemento*/

TLE *crearLista(){

 	TLE *lista = (TLE*)malloc(sizeof(TLE));
	lista->inicio = NULL;
 	return lista;
}

//*****************************************************************//
//*****************************************************************//

/*Func para insertar una variable a la lista, realiza las actualizaciones a los bloques de inicio y fin, de acuerdo al tam de la variable (32 bits) a traves de los punteros start y end (bloque de inicio y bloque final)*/

void Insertar(TLE *lista, int x, char var[]){

 	TNodo *nodo = crearNodo(x, var);
 	TNodo *p=NULL;

 	if(lista->inicio == NULL){
    	lista->inicio=nodo;

		nodo->start=INICIO;
		nodo->end=BITS;

    	nodo->anterior==NULL; 
   	}
    
 	else{ // p-> es el nodo anterior
     	p = lista->inicio;
     	while(p->siguiente != NULL) p = p->siguiente;

		nodo->start=p->end+INICIO;
		nodo->end=p->end+BITS;

     	p->siguiente = nodo;
     	nodo->anterior=p;
    }
}
//*****************************************************************//
//*****************************************************************//

/*
Funcion que recibe el nombre de la variable a eliminar, toma el valor correspondiente y lo regresa para posteriormente, ese valor ser tomado al momento de evaluar la expresion atirmetica.
*/

int Eliminar(TLE *lista, char dato[]){

 	TNodo *p = lista->inicio;
 	TNodo *anterior = NULL;
	int encontrado=0;
	int valor=0;
 	while((p!=NULL)&&(!encontrado)){
		if(strcmp(p->var,dato) == 0){
			valor=p->dato;
			encontrado=1;
		}
      	else{
         	anterior = p;         
         	p = p->siguiente;
        }
	}
      
	if(p!=NULL){         
   		if (anterior==NULL) lista->inicio=(lista->inicio)->siguiente;
   		else{
       		anterior->siguiente=p->siguiente;
       		p->siguiente->anterior=anterior;
      	}
   	free(p);
  	}
	return (valor);
}

//*****************************************************************//
//*****************************************************************//

/*Func que elimina la lista completa, recorre desde inicio la lista y elimina cada nodo*/
void Borrar(TLE *lista){
 	TNodo *p = NULL;
 	while(lista->inicio != NULL){       
		p = lista->inicio;
       	lista->inicio = p->siguiente;       
       	p->siguiente->anterior==NULL;       
       	free(p);      
	}
	printf("Lista eliminada...\n");
}

//*****************************************************************//
//*****************************************************************//

/*Muestra los nodos que estan en la lista, cada nodo se muestra con sus cuatro parametros*/
void Imprimir(TLE *lista , int Orden ){
 
	TNodo *p = lista->inicio;
 	if( Orden == Ascendente){
		printf("lista -> ");
		while(p!=NULL){
        	printf("[%s,%d,%d,%d]",p->var,p->dato,p->start,p->end);
           	p = p->siguiente;
        }
   	}
printf("\n");
}

//*****************************************************************//
//****************************************************************//

/*indica si la lista esta vacia o no, evita que se eliminen variables que aun no se han utilizado*/

void Vacia(TLE *lista){
 	if(lista->inicio == NULL)
	printf("Lista vacia");
 	else printf("Lista no vacia\n");

}

//*****************************************************************//
//*****************************************************************//

/*Func que actualiza los bloques de inicio y bloque final cuando una variable es eliminada de la memoria(lista)*/

void desfragmentar (TLE *lista){

 	TNodo *p = lista->inicio;
 	TNodo *anterior = NULL;
	TNodo *siguiente = NULL;
	TLE *nodo=NULL;
	
	p->start=1;
	p->end=BITS;
 	while(p!=NULL){
		printf("[%s,%d,%d,%d]",p->var,p->dato,p->start,p->end);
        anterior = p;
    	p = p->siguiente;
	}
}

//*****************************************************************//
//*****************************************************************//

/*
Func que asigna un valor aleatorio a la variable, ejemplo:

[a,0,1,32]->[a,24,1,32]

el valor asignado es de 1-30
*/
void ModificaVar(TLE *lista){ // modifica el valor de la variable
	TNodo *p = lista->inicio;
 	TNodo *anterior = NULL;
	TNodo *siguiente = NULL;

 	while(p!=NULL){
		p->dato=rand()%30 + 1;
		//printf("[%s,%d] ",p->var, p->dato);
	    anterior = p;
    	p = p->siguiente;
	}
printf("\n");
}


//*****************************************************************//
//*****************************************************************//

/*
int main(){
	srand((int)time(0));

 	TLE *L=crearLista();
 	int N,E; 
 	int opcion;
    Insertar(L,0, (char*)"a");
    Insertar(L,0, (char*)"b");
    Insertar(L,0, (char*)"c");
    Insertar(L,0, (char*)"d");
	Imprimir(L,Ascendente);
    //Eliminar(L,21);
    //Borrar(L); se elimina la lista ;
    //Imprimir(L,Ascendente);// imprimir
	//cout<<"desfragmentar..."<<endl;
    //Imprimir(L,Descendente); 
	//desfragmentar(L);
    //Vacia(L); 
	printf("\n");
	ModificaVar(L);
	Eliminar(L,(char*)"c");
	Imprimir(L,Ascendente);
	//Expr2();
	//cout<<"modifica el valor de la variable:";Imprimir(L,Ascendente);
	printf("\n");

  return 0;

Borrar(L); 
}

*/



