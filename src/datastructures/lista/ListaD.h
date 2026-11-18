#ifndef LISTAD_H
#define LISTAD_H

#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>


typedef struct
{	
	Nodod *inicio;
	Nodod *fin;
	size_t cant;
	Orden orden;
	fn_comparar comparar;	
	int bucle;
}ListaD;

ListaD inicializarListaD(void);
void insertarOrdenadoD(ListaD *lista,void *dato);
void imprimirListaIFD(ListaD lista,fn_imprimir imprimir);
void imprimirListaFID(ListaD lista,fn_imprimir imprimir);
void eliminarListaD(ListaD *lista,fn_free liberar);
int eliminarDatoD(ListaD *lista,void* dato,fn_comparar comparar);
void insertarInicioD(ListaD *lista,void *dato);
void insertarFinalD(ListaD *lista,void *dato);
int buscarDatoD(ListaD lista,void *dato,fn_comparar comparar);
void ordenarListaD(ListaD *lista,fn_comparar comparar,Orden orden);
void agregarPosicion(ListaD *lista,void* valor, int posicion);
void convertirLista(ListaD* lista);

#endif