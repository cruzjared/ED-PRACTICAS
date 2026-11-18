#ifndef HEAP_H
#define HEAP_H


#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>
#include <Pila.h>
#include <Cola.h>
#include <arbol.h>

typedef enum
{
	HEAPMIN = -1,
	HEAPMAX = 1	
}HeapType;

typedef struct
{
	void **datos;
	size_t cant;
	HeapType type;
	fn_comparar comparar;
}Heap;

void insertarHeap(Heap*,void*);
void* removerHeap(Heap*);

void* eliminarEspecifico(Heap* heap, void* dato);
void imprimirHeap(Heap*,fn_imprimir);

void heapify(Heap *heap);
void liberarHeap(Heap* heap);
void imprimirHeapArbol(Heap* heap, fn_imprimir imprimir);
#endif