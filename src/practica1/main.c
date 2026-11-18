#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Lista.h>
#include <iostring.h>
#include "Alumno.h"
#include <windows.h>
int compararInt(void*,void*);
int compararChar(void*,void*);
int compararCadena(void*,void*);
void imprimirInt(void*);
void imprimirCadena(void*);





int main(void)
{	
	char c; 
	int opc, opc2,opc3;
	Alumno *temporal;
	
	Lista lista = inicializarLista();
		
	
	do 
	{
		system("cls");
		printf("\n MENU");
		printf("\n [1] Registrar alumno");
		printf("\n [2] Desplegar alumnos");
		printf("\n [3] Reordenar");
		printf("\n [4] Buscar alumno");
		printf("\n [5] Borrar alumno");
		printf("\n [6] Terminar programa");
		printf("\n SELECCIONE OPCION: ");
		scanf("%d", &opc);
		clear_buffer();
		switch (opc)
		{
			
			
			case 1:
			
			printf("\n REGISTRAR ALUMNO ");
			temporal = calloc(1, sizeof(Alumno));
			
		
			printf("\n Ingresar matricula del nuevo alumno: ");
			scanf("%u", &temporal->matricula);
			clear_buffer();
			
			if (buscarDato(lista, temporal, compararMatricula) == 1)
			{
				printf("\n Matricula ya existente, volviendo a menu");
				
				
			}
			else
			{
				
				insertarOrdenada(&lista, crearAlumno(temporal->matricula));
				printf("\n Alumno creado");
			}
			free(temporal);
			break; 
			
			case 2:
			imprimirLista(lista, imprimirAlumno);
			break; 
			
			case 3:
			printf("\n\n Criterios de orden");
			printf("\n[1] Por matricula, ascendente");
			printf("\n[2] Por matricula, descendente");
			printf("\n[3] Por nombre, ascendente");
			printf("\n[4] Por nombre, descendente");
			printf("\n[5] Por semestres, ascendente");
			printf("\n[6] Por semestres, descendente");
			printf("\n[7] Por promedio, ascendente");
			printf("\n[8] Por promedio, descendente");
			printf("\n SELECCIONE OPCION:");
			scanf("%d", &opc2);
			clear_buffer();
			
			switch(opc2)
			{
				
				
				case 1:
				ordenarLista(&lista, compararMatricula, ASCENDENTE);
				break;
				
				case 2:
				ordenarLista(&lista, compararMatricula, DESCENDENTE);
				break;
				
				case 3:
				ordenarLista(&lista, compararNombre, ASCENDENTE);
				break;
				
				case 4:
				ordenarLista(&lista, compararNombre, DESCENDENTE);
				break;
				
				case 5:
				ordenarLista(&lista, compararSemestre, ASCENDENTE);
				break;
				
				case 6:
				ordenarLista(&lista, compararSemestre, DESCENDENTE);
				break;
				
				case 7:
				ordenarLista(&lista, compararPromedio, ASCENDENTE);
				break;
				
				case 8:
				ordenarLista(&lista, compararPromedio, DESCENDENTE);
				break;
				
				default:
				printf("\n Opcion no valida");
				
				
			}
			printf("\n\n Lista ordenada");
			
			
			
			break;
			
			case 4: 
			printf("\n Buscar alumno");
			Alumno *temporal = calloc(1, sizeof(Alumno));
			printf("\n [1] Por nombre");
			printf("\n [2] Por matricula");
			printf("\n [3] Por semestres");
			printf("\n [4] Por promedio");
			printf("\n SELECCIONE OPCION: ");
			scanf("%d",&opc3);
			clear_buffer();
			
			switch(opc3)
			{
				
				case 1:
				inputCadena("\nIngresar nombre del alumno a buscar: ", temporal->nombre, 64);
				buscarAlumno(lista,temporal,compararNombre);
				free(temporal);
				break;
				case 2:
				printf("\n Ingresar matricula del alumno a buscar: ");
			    scanf("%u", &temporal->matricula);
				clear_buffer();
				buscarAlumno(lista,temporal,compararMatricula);
				free(temporal);
				break;
				case 3:
				inputEntero("\nCapturar numero de semestres del alumno a buscar: ", &temporal->semestre);
				buscarAlumno(lista,temporal ,compararSemestre);
				free(temporal);
				break;
				case 4:
				inputFloat("\nCapturar promedio del alumno a buscar: ", &temporal->promedio);
				buscarAlumno(lista,temporal ,compararPromedio);
				free(temporal);
				break;
				default:
				printf("\n Opcion no valida");
				free(temporal);
				break;
				
			}
			
			break;
			
			case 5:
			printf("\nEliminar alumno");
			temporal = calloc(1, sizeof(Alumno));
			printf("\n Ingresar matricula del alumno a buscar: ");
			scanf("%u", &temporal->matricula);
			clear_buffer();
			borrarAlumno(&lista,temporal, compararMatricula);
			free(temporal);
			break;
			
			case 6: 
			eliminarLista(&lista);
			break;
			default: 
			printf("\n Opcion no valida");
			break;
			
			
		}
		
		printf("\n presione ENTER para continuar");
		c = getchar();
		if(c!= '\n')
		{
			clear_buffer();
		}
		
		
		
		
		
	}while (opc != 6);
	
	printf("\n Programa finalizado :)"); 
	
	
	return 0;
}

int compararInt(void* pa,void* pb)
{
	int a = *(int*)pa;
	int b = *(int*)pb;
	if( a>b) return 1;
	else if(a<b) return -1;
	else return 0;
}


int compararChar(void* a,void* b)
{
	return strcmp((char*)a,(char*)b);
}

void imprimirInt(void *dato)
{
	printf("%d", *(int*)dato);
}

void imprimirCadena(void *dato)
{	
	printf("%s", (char*)dato);
}


int compararCadena(void *a,void *b)
{
	return strcmp(a,b);
}

