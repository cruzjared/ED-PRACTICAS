#ifndef PILA_H
#define PILA_H

#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>

typedef struct
{	
	Nodo *cima;
	size_t cant;
	size_t limite;
}Pila;


typedef enum{
	
	true = 1,
	false = 0
	
}Bool;

Pila *crearPila(void);
Pila inicializarPila(int);
int pilaLlena(Pila);
int pilaVacia(Pila);
void* peek(Pila pila);
void push(Pila *pila,void *dato);
void pushN(Pila *pila,Nodo* nodo);
void* pop(Pila *pila);
Nodo* popN(Pila *pila);
void imprimirPila(Pila pila,fn_imprimir imprimir);
void eliminarPila(Pila *pila,fn_free liberar);
int buscarDatoPila(Pila pila,void *dato,fn_comparar comparar);
int aperturaCorrecta(char* texto);
int esPar(char a, char b);



#endif