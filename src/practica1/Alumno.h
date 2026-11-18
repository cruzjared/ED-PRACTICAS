#ifndef ALUMNO_H
#define ALUMNO_H
#define MAX 64
#include <Lista.h>

typedef struct 
{

	size_t matricula; 
	int semestre; 
	char nombre [64]; 
	float promedio; 


}Alumno;


Alumno* crearAlumno (size_t matricula);
void imprimirAlumno (void*);
int compararMatricula(void*, void*);
int compararNombre(void*, void*);
int compararSemestre(void*, void*);
int compararPromedio(void*, void*);
void buscarAlumno(Lista lista, void* dato, fn_comparar comparar);
void borrarAlumno(Lista *lista, void* dato, fn_comparar comparar);


#endif 