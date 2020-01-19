#include<iostream>
#include<stdio.h>
#include<string.h>
#include<ctime>
#include<stdlib.h>
#include"cadenas.cpp"
#include"sintactico.cpp"
#include"lexico.cpp"

/*
@utor Fredy M

desonses@gmail.com

UAEM
*/


/*
MENU QUE SIMULA LA EJECUCION DE UNA EXPRESION ARITMETICA, ANALIZA LEXICAMENTE Y SINTACTICAMENTE UNA EXPRESION
 DEL TIPO: a=c+b; SI LA EXPRESION ES CORRECTA SE ASIGNAN VALORES RANDOM A LAS VARIABLES DEL LADO DER DE LA EXPRESION, 
 SE HACE USO UNA GRAMATICA PARA DICHO PROCESO, LA EXPRESION INGRESADA ES SENSIBLE A ESPACIOS Y NO HAY UNA VERIFICACION DE 
 DIVISION POR CERO, SE CONTEMPLAN VALORES ALEATORIOS MAYORES O IGUALES A 1



* Para probar el programa es necesario ingresar una expresion aritmetica sin espacios, reconoce variables de "a hasta la s",
 --> ejemplo:  prueba=a+(c*(f+s));       
debe ser una expresion bien formada, solo variables, si se combina letras y numeros, debido al AFD utilizado seria una
 expresion no valida, ejemplo=a+(3*(f+8)); el AFD no reconoce esta expresion.
 
 */



/*
EJECUTAR
g++ -o main main.cpp
./main

*/

using namespace std;

int main(){
	string str;
	srand((int)time(0));
	state = -1;
	//estado = -1;// para analizador lexico
	char expresion[TAM];
	char *evalua;
	int opcion;
	float Calculo;
    do{
        printf("1. Expresion aleatoria.\n");
        printf("2. Ingresar una expresion.\n");
        printf("0. Salir.\n");
		printf("?: "); 
		scanf("%d",&opcion);

        switch (opcion){
            case 1:// kacsk=(b+t)-(h*l(-)s-f)+;

				cout<<"Cadena generada: "<<Cadena()<<endl;// se obtiene una cadena aleatoria
				// expresion a validar
				strcpy(expresion,Cadena());
				Separar(expresion);// se identifican los tokens >>>> LEXICO
				Valida();// se verifica la expresion >>>> LEXICO
				cout<<"Expresion a analizar: ";Expr2();
				strcpy(entrada,Expr()); //  SE ANALIZA LA EXPRESION SINTACTICAMENTE
				Imprimir(L,Ascendente);				
				E();
				Nuevo();
				Borrar(L);
				break;

            case 2: // afd=a+(b*(c/d));
				fflush( stdin );
				cout << "Introduzca una expresion aritmetica: ";
				cin >> expresion;
				Separar(expresion);// se identifican los tokens >>>> LEXICO
				cout<<"Expresion a analizar: "; Expr2();cout<<endl;
				Revisa(Expr());

				if(1==Valida()){
					cout<<"Expresion valida, se modifica el valor de la variable:"<<endl;
					ModificaVar(L);
					Imprimir(L,Ascendente);
					cout<<"Se evaluara la expresion:"<<Expr()<<endl;
					Processor p(Expr());
					Calculo=p.eval();
					cout<<cadenaizq()<<"="<<Calculo<< endl;
					Insertar(L,Calculo, (char*)cadenaizq());
					Imprimir(L,Ascendente);
				}
				Borrar(L); 
				printf("\n\n");
				break;
		}
		
    } while (opcion!= 0);


return 0;

}



