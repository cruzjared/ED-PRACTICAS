#include "Nodo.h"
#include <stdlib.h>

Nodo* crearNodo(void *dato)
{
	Nodo *nuevo = calloc(1,sizeof(Nodo));
	nuevo->dato = dato;
	return nuevo;
}


void swapNodo(Nodo *a,Nodo *b)
{
	void *aux = a->dato;
	a->dato = b->dato;
	b->dato = aux;
}

Nodod* crearNodod(void *dato)
{	
	Nodod *nuevo = calloc(1,sizeof(Nodod));
	nuevo->dato = dato;
	return nuevo;
	
}
void swapNodod(Nodod *a,Nodod *b)
{
	void *aux = a->dato;
	a->dato = b->dato;
	b->dato = aux;	
}

Nodoa* crearNodoa(void *dato)
{
	Nodoa *nuevo = calloc(1,sizeof(Nodoa));
	nuevo->dato = dato;
	//nuevo->dch = NULL;
	//nuevo->izq = NULL;
	return nuevo;	
}
void swapNodoa(Nodoa *a,Nodoa *b)
{
	void *aux = a->dato;
	a->dato = b->dato;
	b->dato = aux;		
}