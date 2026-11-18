#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <Nodo.h>
#include <heap.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#define MAX 20


typedef struct 
{
	
	char nombre [MAX];
	int cantidadHojas; 
	
}Archivo; 



int *crearEntero(int);
int compararHojasArchivo(void*,void*);
int compararEspecifico(void *pa, void* pb);
void imprimir(void*);
void imprimirenArbol(void* dato);
Archivo* crearArchivo(char* nombre);


int main(void)
{
	srand(time(NULL));
	char nombre [MAX]; 
	Heap heap = {NULL,0,HEAPMIN,compararHojasArchivo};; 
	Archivo* archivoProcesado;
	
	int opc, num;
	char c;
	
	
	
	do{
		
		system("cls");
		printf("\n MENU");
		printf("\n[0] Cambiar prioridad");
		printf("\n[1] Mostrar cola de impresion");
		printf("\n[2] Agregar archivo");
		printf("\n[3] Procesar/imprimir archivo");
		printf("\n[4] Eliminar archivo");
		printf("\n[5] Eliminar todos los archivos ");
		printf("\n[6] Terminar programa");
		printf("\n SELECCIONE OPCION: ");
		scanf("%d", &opc);
		clear_buffer();
		
		
		
		
		switch(opc)
		{
			
			case 0: 
			if(heap.type == HEAPMIN)
				heap.type = HEAPMAX;
			else
				heap.type = HEAPMIN;
			
			heapify(&heap);
			printf("\n La prioridad del heap ha cambiado\n");
			break;
			
			case 1:
			if(heap.datos)
			{
				imprimirHeap(&heap, imprimir);
				printf("\n\n\n\n\n VISUALIZACION DE HEAP COMO ARBOL POR # HOJAS \n\n\n");
				imprimirHeapArbol(&heap, imprimirenArbol);
			}
			else
				printf("\nNo hay archivos por imprimir");
			break;
			
			case 2:
			printf("\nIngresar nombre del archivo: ");
			fgets(nombre, MAX, stdin);
			insertarHeap(&heap, crearArchivo(nombre));
			
			break;
			
			case 3:
			if(heap.datos)
			{
				
				archivoProcesado = removerHeap(&heap);
				printf("\n Se proceso el archivo: %s, de %d paginas...", archivoProcesado->nombre, archivoProcesado->cantidadHojas);
			}
			else
				printf("\n No hay archivos por imprimir");
			break;
			
			case 4:
			if(heap.datos)
			{
				heap.comparar = compararEspecifico;
				imprimirHeapArbol(&heap, imprimirenArbol);
				printf("\n\n\n\n\n");
				printf("Insertar numero de hojas del archivo a eliminar: ");
				scanf("%d", &num);
				clear_buffer();
				archivoProcesado = eliminarEspecifico(&heap, crearEntero(num));
				if(archivoProcesado)
					printf("\n Se proceso el archivo: %s, de %d paginas...", archivoProcesado->nombre, archivoProcesado->cantidadHojas);
				else
					printf("El archivo con %d paginas no fue encontrado en la cola de impresion", num);
				heap.comparar = compararHojasArchivo;
			}
			else
				printf("\n No hay archivos por imprimir");
			break;
			
			case 5:
			if(heap.datos)
			{
				liberarHeap(&heap);
				printf("\n Cola de impresion eliminada");
			}
			else
				printf("\n No hay archivos por eliminar");
			break;
			
			
			case 6:
			if(heap.datos)
				liberarHeap(&heap);
			printf("\nTerminando programa...");
			
			break;
			
			
			
		}
		
		printf("\n\n\n presione ENTER para continuar");
		c = getchar();
		if(c!= '\n')
			clear_buffer();
			
		
		
	}while(opc != 6);
	
	
	
	
	
	
	
	
	
	
	
	
	
	printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


int *crearEntero(int num)
{
	int *dato = calloc(1,sizeof(int));
	*dato = num;
	return dato;
}

void imprimir(void *dato)
{
	Archivo archivo = *(Archivo*)dato;
	printf("Nombre: %s, #hojas: %d",archivo.nombre,archivo.cantidadHojas);
	printf(" | ");
}

void imprimirenArbol(void* dato)
{
	Archivo archivo = *(Archivo*)dato;
	printf("%d",archivo.cantidadHojas);
	
}

int compararHojasArchivo(void *pa,void *pb)
{
	Archivo a = *(Archivo*)pa;
	Archivo b = *(Archivo*)pb;
	if(a.cantidadHojas<b.cantidadHojas)return -1;
	if(a.cantidadHojas>b.cantidadHojas)return 1;
	else return 0;
}

int compararEspecifico(void *pa, void* pb)
{
	Archivo a = *(Archivo*)pa;
	int b = *(int*)pb;
	if(a.cantidadHojas<b)return -1;
	if(a.cantidadHojas>b)return 1;
	else return 0;
	
	
}


Archivo* crearArchivo(char* nombre)
{
	
	Archivo* nuevo = calloc(1, sizeof(Archivo));
	strcpy(nuevo->nombre, nombre);
	nuevo->cantidadHojas = rand() % 501;
	
	return nuevo;
	
}


