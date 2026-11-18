#ifndef ARBOL_H
#define ARBOL_H

#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>
#include <Pila.h>
//#include <iostring.h>


#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
//#define INVERSO 4
#define IZQUIERDA 0
#define DERECHA 1

typedef struct
{
	Nodoa *raiz;
	size_t cant;
	fn_comparar comparar;
}Arbol;

typedef struct
{
	
	int limInf;
	int limSup;
	int centro; 
	
	
}Rango;

typedef struct
{
	char operando;
	float valor;
}Variable;


size_t altura(Arbol);
size_t alturaI (Arbol);
//Parametor opcion representa el orden en el que se imprime el arbol, ya sea orden, preorden y postorden
void preordenI(Arbol arbol,fn_imprimir imprimir);
void ordenI(Arbol arbol,fn_imprimir imprimir);
void postordenI(Arbol arbol,fn_imprimir imprimir);
void imprimirOrden(Arbol arbol, fn_imprimir, int opcion);
void insertarArbolO( Arbol *arbol, void *dato);
void insertarNodoArbolO( Arbol *arbol, Nodoa* nuevo);
void flipArbol(Arbol* arbol);
void* buscarArbol(Arbol*arbol, void* dato);
void imprimir_arbol(Nodoa* nodo, int nivel,fn_imprimir imprimir);
void imprimirArbol(Arbol arbol,fn_imprimir imprimir);
void eliminarDato(Arbol* arbol, void*dato);
void equilibrarArbol(Arbol*arbol);
void liberarArbol(Arbol* arbol);
int precedencias(char a);
char* infix_Postfix(char* cadena);
int arbolExpresion(char* cadenaPostfix, Arbol* arbol);
int buscarVariable(char c, Variable* arreglo, int contador);
Variable* buscarValorVariable(char c, Variable* arreglo, int longitud);
Variable* crearArregloVariables(Arbol arbol, int* longitud);
float calcular(char c, float a, float b);
float evaluarExpresion(Arbol arbol, int* longitud);


#endif