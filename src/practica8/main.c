#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostring.h>
#include <HashQ.h>
#include "Libro.h"
#include <Arbol.c>
#define MAX 45


int foldingTitulo(void *);
int foldingTituloRango(void *);
int foldingISBN(void *);
int foldingAutor(void *);
int foldingAutorRango(void *);
int foldingInt(void* data);
void llenarTabla(HashQTable* tabla, Acervo acervo );
void imprimirTabla(HashQTable tabla);
HashQTable* crearTabla(fn_folding folding, fn_imprimir imprimir, fn_comparar comparar, int rango);

int main(void)
{

	//tablas
	HashQTable* tablaTitulo =crearTabla(foldingTitulo, imprimirLibro, compararTitulo, 0);
	HashQTable* tablaISBN =crearTabla(foldingISBN, imprimirLibro, compararISBN, 0);
	HashQTable* tablaAutor =crearTabla(foldingAutor, imprimirLibro, compararNombre, 1);
	HashQTable* tablaFecha =crearTabla(foldingInt, imprimirLibro, compararFecha, 1);
	HashQTable* tablaAutorRango =crearTabla(foldingAutorRango, imprimirLibro, compararRangoAutores, 1);
	HashQTable* tablaTituloRango =crearTabla(foldingTituloRango, imprimirLibro, compararRangoTitulo,1);
	HashQTable* tablaFechaRango =crearTabla(foldingInt, imprimirLibro, compararRangoFechas,1);
	//acervo
	Acervo acervo = obtener_libros();
	llenarTabla(tablaTitulo, acervo);
	llenarTabla(tablaISBN, acervo);
	llenarTabla(tablaAutor, acervo);
	llenarTabla(tablaFecha, acervo);
	llenarTabla(tablaAutorRango, acervo);
	llenarTabla(tablaTituloRango, acervo);
	llenarTabla(tablaFechaRango, acervo);
	HashQTable* tablas[7] = {tablaTitulo, tablaISBN, tablaAutor, tablaFecha, tablaAutorRango, tablaTituloRango, tablaFechaRango};
	
	
	imprimirTabla(*tablaTitulo);
	
	void* sup, *inf;
	char c; 
	char charInf, charSup; 
	int intInf, intSup;
	int opc, fecha; 
	Libro libro;
	Arbol arbol; 
	arbol.comparar = compararTitulo;
	void** arreglo; 
	char cadena [MAX];
	
	
	do
	{
		arbol.raiz = NULL;
		printf("\n\n MENU");
		printf("\n[1] Buscar por ISBN");
		printf("\n[2] Buscar por Titulo");
		printf("\n[3] Buscar por autor");
		printf("\n[4] Buscar por a%co", 164);
		printf("\n[5] Eliminar por ISBN");
		printf("\n[6] Terminar programa");
		printf("\n SELECCIONE OPCION: ");
		scanf("%d", &opc);
		clear_buffer();
		
		switch(opc)
		{
			
			case 1:
			printf("\nIngresar ISBN del libro a buscar: ");
			fgets(cadena,MAX,stdin);
			remover_salto(cadena);
			strcpy(libro.isbn,cadena);
			strcpy(libro.titulo,"");
			strcpy(libro.autor,"");
			libro.fecha = 0;
			libro.disponible = 0;
			tablaISBN->verbose = 1; 
			arreglo = fn_searchKey(tablaISBN, &libro);
			if(arreglo)
				{
					for(int i = 0; arreglo[i]; i++)
					{
						insertarArbolO(&arbol, arreglo[i]);
					}
					printf("\n LIBRO ENCONTRADO:");
					ordenI(arbol, imprimirLibro);
				}
			else
				printf("\n No fue encontrado ningun libro con el ISBN: %s", cadena);
			break;
			
			
			
			
			
			
			case 2:
			printf("\n\n POR TITULO ");
			printf("\n[1] Buscar en base a titulo");
			printf("\n[2] Buscar en base a un rango");
			printf("\nSELECCIONE OPCION: ");
			scanf("%d",&opc);
			clear_buffer();
			
			switch(opc)
			{
				
				case 1:
				printf("\nIngresar el titulo del libro a buscar: ");
				fgets(cadena, MAX, stdin);
				remover_salto(cadena);
				strcpy(libro.isbn,"");
				strcpy(libro.titulo,cadena);
				strcpy(libro.autor,"");
				libro.fecha = 0;
				libro.disponible = 0;
				tablaTitulo->verbose = 1; 
				arreglo = fn_searchKey(tablaTitulo, &libro);
				if(arreglo)
				{
					for(int i = 0; arreglo[i]; i++)
					{
						insertarArbolO(&arbol, arreglo[i]);
					}
					printf("\n LIBRO ENCONTRADO:");
					ordenI(arbol, imprimirLibro);
				}
				else
					printf("\n No fue encontrado ningun libro con el titulo: %s", cadena);
				break;
				
				case 2:
				printf("\nIngresar la letra del rango inferior: ");
				scanf("%c", &charInf);
				clear_buffer();
				printf("\nIngresar la letra del rango superior: ");
				scanf("%c",&charSup);
				clear_buffer();
				Libro libroRango = {"","","",0,0};
				
				for(int i = charInf; i<=charSup; i++)
				{
					libroRango.titulo[0] = i;
					arreglo = fn_searchKey(tablaTituloRango, &libroRango);
					if(arreglo)
					{
						for(int j = 0; arreglo[j]; j++)
						{
							insertarArbolO(&arbol, arreglo[j]);
						}
					}
				}
				printf("\n LIBROS ENCONTRADOS: \n");
				ordenI(arbol, imprimirLibro);
				
				if(!arbol.raiz)
					printf("\n No fueron encontrados libros en el rango establecido");
				break;
				
				
				default:
				printf("\n Opcion no valida");
				
				
			}
			break;
			
			
			case 3:
			printf("\n\n POR AUTOR ");
			printf("\n[1] Buscar en base a un nombre");
			printf("\n[2] Buscar en base a un rango");
			printf("\nSELECCIONE OPCION: ");
			scanf("%d",&opc);
			clear_buffer();
			
			switch(opc)
			{
				
				case 1:
				printf("\nIngresar el nombre del autor a buscar: ");
				fgets(cadena, MAX, stdin);
				remover_salto(cadena);
				strcpy(libro.isbn,"");
				strcpy(libro.titulo,"");
				strcpy(libro.autor,cadena);
				libro.fecha = 0;
				libro.disponible = 0;
				tablaAutor->verbose = 1;
				arreglo = fn_searchKey(tablaAutor, &libro);
				if(arreglo)
				{
					for(int i = 0; arreglo[i]; i++)
					{
						insertarArbolO(&arbol, arreglo[i]);
					}
					printf("\n LIBROS ENCONTRADOS DEL AUTOR %s: \n",cadena);
					ordenI(arbol, imprimirLibro);
				}
				if(!arbol.raiz)
					printf("\n No fue encontrado ningun libro del autor: %s", cadena);
				break;
				
				case 2:
				printf("\nIngresar la letra del rango inferior: ");
				scanf("%c", &charInf);
				clear_buffer();
				printf("\nIngresar la letra del rango superior: ");
				scanf("%c",&charSup);
				Libro libroRango = {"","","",0,0};
				tablaAutorRango->verbose = 1;
				for(int i = charInf; i<=charSup; i++)
				{
					libroRango.autor[0] = i;
					arreglo = fn_searchKey(tablaAutorRango, &libroRango);
					if(arreglo)
					{
						for(int j = 0; arreglo[j]; j++)
						{
							insertarArbolO(&arbol, arreglo[j]);
						}
					}
				}
				printf("\n LIBROS ENCONTRADOS: \n");
				ordenI(arbol, imprimirLibro);
				if(!arbol.raiz)
					printf("\n No fueron encontrados libros en el rango establecido");
				break;
				
				
				default:
				printf("\n Opcion no valida");
				
				
			}
			
			break;
			
			case 4:
			printf("\n\n POR FECHA ");
			printf("\n[1] Buscar en base a un a%co", 164);
			printf("\n[2] Buscar en base a un rango");
			printf("\nSELECCIONE OPCION: ");
			scanf("%d",&opc);
			clear_buffer();
			
			switch(opc)
			{
				
				case 1:
				printf("\nIngresar el a%co buscar: ",164);
				scanf("%d",&fecha);
				clear_buffer();
				strcpy(libro.isbn,"");
				strcpy(libro.titulo,"");
				strcpy(libro.autor,"");
				libro.fecha = fecha;
				libro.disponible = 0;
				tablaFecha->verbose = 1;
				arreglo= fn_searchKey(tablaFecha, &libro);
				if(arreglo)
				{
					for(int i = 0; arreglo[i]; i++)
					{
						insertarArbolO(&arbol, arreglo[i]);
					}
					printf("\n LIBROS ENCONTRADOS DEL A%cO %d: \n",165,fecha);
					ordenI(arbol, imprimirLibro);
				}
				else
					printf("\n No fue encontrado ningun libro del a%co: %d",164, fecha);
				break;
				
				case 2:
				printf("\nIngresar la letra del rango inferior: ");
				scanf("%d", &intInf);
				clear_buffer();
				printf("\nIngresar la letra del rango superior: ");
				scanf("%d",&intSup);
				Libro libroRango = {"","","",0,0};
				for(int i = intInf; i<=intSup; i++)
				{
					libroRango.fecha = i; 
					arreglo = fn_searchKey(tablaFechaRango, &libroRango);
					if(arreglo)
					{
						for(int j = 0; arreglo[j]; j++)
						{
							insertarArbolO(&arbol, arreglo[j]);
						}
					}
					
				}
				printf("\n LIBROS ENCONTRADOS: \n");
				ordenI(arbol, imprimirLibro);
				if(!arbol.raiz)
					printf("\n No fueron encontrados libros en el rango establecido");
				break;
				
				default:
				printf("\n Opcion no valida");
				
				
			}
			
			
			break;
			
			
			case 5:
			printf("\nIngresar ISBN del libro a buscar: ");
			fgets(cadena,MAX,stdin);
			remover_salto(cadena);
			strcpy(libro.isbn,cadena);
			strcpy(libro.titulo,"");
			strcpy(libro.autor,"");
			libro.fecha = 0;
			libro.disponible = 0;
			arreglo = fn_searchKey(tablaISBN, &libro);
			
			if(arreglo)
			{
				for(int i = 0; i<7  ; i++)
				{
					tablas[i]->comparar = compararISBN;
					fn_deleteKey(tablas[i], *arreglo); 
				}
				
				printf("\n Libro con ISBN %s ELIMINADO", cadena);
				
				tablaAutor->comparar = compararNombre;
				tablaAutorRango->comparar = compararRangoAutores;
				tablaFecha->comparar = compararFecha;
				tablaFechaRango->comparar = compararRangoFechas;
				tablaTitulo->comparar = compararTitulo;
				tablaTituloRango->comparar = compararRangoTitulo;
				
			}
			else
				printf(" \n No fue encontrado ningun libro con el ISBN %s", cadena);
			
			break;
			
			
			case 6:
			printf("\n TERMINANDO PROGRAMA....");
			break;
			
			
		}
		
		
		
	}while(opc != 6);
	
	
	
	
	
	
	
	
	
	return 0;
}


int foldingTitulo(void *data)
{
	char *cadena = ((Libro*)data)->titulo;
	int key = 0,sector = 1,sumatoria=0;
	for(int i = 0; cadena[i]!='\0'; i++)
	{
		//abc de
		sumatoria += cadena[i];
		if( i!=0 && (i+1)%3 == 0)
		{
			key+= sector*sumatoria;
			sumatoria = 0;
			sector++;
		}
	}	
	key+= sector*sumatoria;
	return key;
}

int foldingTituloRango(void * data)
{
	char caracter = ((Libro*)data)->titulo[0];
	int key = caracter; 
	return key;
}

int foldingISBN(void *data)
{
	char *cadena = ((Libro*)data)->isbn;
	int key = 0,sector = 1,sumatoria=0;
	for(int i = 0; cadena[i]!='\0'; i++)
	{
		//abc de
		sumatoria += cadena[i];
		if( i!=0 && (i+1)%3 == 0)
		{
			key+= sector*sumatoria;
			sumatoria = 0;
			sector++;
		}
	}	
	key+= sector*sumatoria;
	return key;
}


int foldingAutor(void *data)
{
	char *cadena = ((Libro*)data)->autor;
	int key = 0,sector = 1,sumatoria=0;
	for(int i = 0; cadena[i]!='\0'; i++)
	{
		//abc de
		sumatoria += cadena[i];
		if( i!=0 && (i+1)%3 == 0)
		{
			key+= sector*sumatoria;
			sumatoria = 0;
			sector++;
		}
	}	
	key+= sector*sumatoria;
	return key;
}

int foldingAutorRango(void * data)
{
	char caracter = ((Libro*)data)->autor[0];
	int key = caracter; 
	return key;
}





int foldingInt(void* data)
{
	
	int num = (*(Libro*)data).fecha; 
	
	int val1 = num/100; 
	int val2= num%100; 
	
	return (1*val1)+(2*val2);
	
	
	
}

void llenarTabla(HashQTable* tabla, Acervo acervo )
{
	for(int i = 0; i < acervo.cantidad ; i++)
	{
		printf("\n");
		//imprimirLibro(acervo.libros+i);
		fn_insertKey(tabla,acervo.libros+i);		
	}
	remap(tabla);
	
}


void imprimirTabla(HashQTable tabla)
{
	printf("\nTABLA");
	for(int i = 0; i < tabla.len ; i++)
	{		
		printf("\n[%d]",i);
		if( tabla.table[i]!=NULL)		
		{
			imprimirLibro(tabla.table[i]);			
		}
	}
	
	
	
	
}


HashQTable* crearTabla(fn_folding folding, fn_imprimir imprimir, fn_comparar comparar, int rango)
{
	
	HashQTable* tablahash = calloc(1,sizeof(HashQTable));
	tablahash->table = calloc(1000,sizeof(void*));
	tablahash->len = 1000;
	tablahash->cant = 0;
	tablahash->min = 30;
	tablahash->max = 70;
	tablahash->fixed = (tablahash->min+tablahash->max)/2;
	tablahash->folding = folding;
	tablahash->imprimir = imprimir;
	tablahash->comparar = comparar;
	tablahash->verbose = 0;
	tablahash->rango = rango;
	
	return tablahash;
	
	
}

//pendientes folding rango CHAR