#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include "Alumno.h"
#include <Lista.h>



Alumno* crearAlumno (size_t  matricula)
{
	
	Alumno* nuevo = calloc(1, sizeof(Alumno));
	nuevo->matricula = matricula; 
	inputCadena("Capturar nombre del alumno: ", nuevo->nombre, MAX);
	inputEntero("Capturar numero de semestres cursados: ", &nuevo->semestre);
	inputFloat("Capturar promedio: ", &nuevo->promedio);
	return nuevo;
	
	
	
}
void imprimirAlumno (void* a )
{
	Alumno alumno = *(Alumno*)a;
	
	
	printf("%-8u | ",alumno.matricula);
	printf("%-20s | ",alumno.nombre);
	printf("%3d | ",alumno.semestre);
	printf("%.2f | ",alumno.promedio);
	//printf("\n");
	
	
}


int compararMatricula(void* pa, void* pb)
{
	Alumno *a,*b;
	a= pa;
	b= pb;
	
	
	if (a-> matricula > b->matricula)
		return 1;
	else if(a->matricula < b->matricula)
		return -1;
	else 
		return 0; 
	
	
	
}

int compararNombre(void* pa, void* pb)
{
	Alumno *a, *b;
	a = pa;
	b= pb;
	return strcmp (a->nombre, b->nombre);
	
	
	
}

int compararSemestre(void* pa, void* pb)
{
	Alumno *a,*b;
	a= pa;
	b= pb;
	
	
	if (a->semestre > b->semestre)
		return 1;
	else if(a->semestre < b->semestre)
		return -1;
	else 
		return 0; 
	
	
	
}

int compararPromedio(void* pa, void* pb)
{
	
	Alumno *a,*b;
	a= pa;
	b= pb;
	
	
	if (a->promedio > b->promedio)
		return 1;
	else if(a->promedio < b->promedio)
		return -1;
	else 
		return 0; 
	
	
	
}

void buscarAlumno(Lista lista, void* dato, fn_comparar comparar)
{
	if(!lista.inicio)
		return; 
	
	Nodo* actual; 
	
	for(actual = lista.inicio; actual; actual = actual->sig)
	{
		
		if(comparar(actual->dato,dato) == 0)
		{
			printf("\n Alumno encontrado: \n");
			imprimirAlumno(actual->dato);
			return;
		}
		
	}
	printf("\n Alumno no encontrado");
	
	
	
	
}

void borrarAlumno(Lista *lista, void* dato, fn_comparar comparar)
{
	
	if(!lista->inicio)
		return; 
	
	Nodo* actual, *aux = NULL; 
	
	for(actual = lista->inicio; actual; actual = actual->sig)
	{
		
		if(comparar(actual->dato,dato) == 0 && actual == lista->inicio)
		{
			
			lista->inicio = actual->sig;
			free(actual);
			lista->cant--;
			printf("\n Alumno borrado");
			return;
		}
		else if (comparar(actual->dato,dato)!= 0)
			aux = actual;
		
		if(comparar(actual->dato,dato) ==0)
		{
			if(actual->sig == NULL)
				lista->fin = aux;
			aux->sig = actual->sig;
			free(actual);
			lista->cant--;
			printf("\n Alumno borrado");
			return;
		}
	
		
		
	}
	printf("\n Alumno no encontrado");
	
	
	
}