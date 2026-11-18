#ifndef CANCION_H
#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <string.h>
#include <ListaD.h>
#include <Nodo.h>

#define MAXCADENA 20

typedef struct 
{
    char nombre[MAXCADENA];
    char autor[MAXCADENA];
    short int release_date;
}Cancion;


typedef struct
{
	Cancion *cancion;
	size_t cant;
}Canciones;

Canciones cargarCanciones(void); 
void imprimirCanciones(Canciones);
void imprimirCancion(void*);
void imprimirNombre(void*);
int compararPosicionCancion(void* pa, void*pb);
void displayCanciones( Nodod* cancionActual, fn_imprimir imprimir);
Nodod* recorrerLista(Nodod* cancionActual, int OFFSET);
void imprimirMenuListaIFD(ListaD lista,fn_imprimir imprimir);
int eliminarCancionPosicion(ListaD *lista,void *dato,Nodod** cancionActual, fn_comparar comparar);


#endif