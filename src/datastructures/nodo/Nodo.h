#ifndef NODO_H
#define NODO_H

#include <stdlib.h>

typedef void (*fn_free)(void*);
typedef int (*fn_comparar)(void*,void*);
typedef void (*fn_imprimir)(void*);

typedef enum
{
	DESCENDENTE = -1,
	NINGUNO = 0,
	ASCENDENTE = 1	
}Orden;

typedef struct nodo
{
	void *dato;
	struct nodo *sig;
}Nodo;

typedef struct nodod
{
	void *dato;
	struct nodod *sig;
	struct nodod *ant;
}Nodod;

typedef struct nodoa
{
	void *dato;
	struct nodoa *izq;
	struct nodoa *dch;
}Nodoa;


Nodo* crearNodo(void *dato);
void swapNodo(Nodo *a,Nodo *b);
Nodod* crearNodod(void *dato);
void swapNodod(Nodod*,Nodod*);
Nodoa* crearNodoa(void *dato);
void swapNodoa(Nodoa *a,Nodoa *b);

#endif