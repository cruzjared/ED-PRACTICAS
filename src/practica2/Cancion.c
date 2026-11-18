#include "Cancion.h"
#include <iostring.h>




Canciones cargarCanciones(void)
{
	//crear un arreglo estatico -------en segmento de datos, no en el stack--------------
	static Cancion biblioteca[] = 
	{
		(Cancion){"Tourette's","Nirvana",1994},
		(Cancion){"Dumb","Nirvana",1994},
		(Cancion){"Blew","Nirvana",1989},
		(Cancion){"School","Nirvana",1989},
		(Cancion){"Aneurysm","Nirvana",1992},
		(Cancion){"Reckless Abandon","blink-182",2001},
		(Cancion){"Carousel","blink-182",1994},
		(Cancion){"Headup","Deftones",1997},
		(Cancion){"Dai the flu","Deftones",1997},
		(Cancion){"7 words","Deftones",1995},
		(Cancion){"Entombed","Deftones",2012},
		(Cancion){"Comfortable liar","Chevelle",2002},
		(Cancion){"Lying from you", "Linkin Park", 2003},
		(Cancion){"figure.09", "Linkin Park", 2003},
		(Cancion){"Faint", "Linkin Park", 2003}
	};	
	
	static Canciones canciones;
	canciones.cancion = biblioteca;
	canciones.cant = sizeof(biblioteca)/sizeof(Cancion);
	return canciones;
}

void imprimirCanciones(Canciones canciones)
{
	printf("\n Canciones TOTAL:%d",canciones.cant);
	for(int i = 0 ; i< canciones.cant; i++)
	{
		printf("\n[%2d]",i);
		imprimirCancion(&canciones.cancion[i]);
	}
}

void imprimirCancion(void *dato)
{
	Cancion *cancion = dato;
	printf(" %-20s ",cancion->nombre);
	printf("| %-20s ",cancion->autor);
	printf("| %hu ",cancion->release_date);
}
void imprimirNombre(void *dato)
{
	Cancion *cancion = dato;
	printf(" %-20s ",cancion->nombre);	
	
}

int compararPosicionCancion(void* pa, void*pb)
{
	
	
	int a, b;
	a= *(int*)pa;
	b =*(int*)pb;
	
	if(a>b)
		return 1;
	else if (a<b)
		return -1;
	else
		return 0;
}

void displayCanciones(Nodod* cancionActual, fn_imprimir imprimir)
{
	
	if(!cancionActual)
	{
		printf("Ninguna  <<-- Ninguna -->> Ninguna");
		return;
	}
	
	
	
	if(cancionActual->ant == NULL)
		printf("Ninguna <<-- ");
	else
	{
		imprimir(cancionActual->ant->dato);
		printf("<<--");
	}
	

	imprimir(cancionActual->dato);
	printf("-->>");
	
	if(cancionActual->sig == NULL)
		printf("Ninguna");
	else
		imprimir(cancionActual->sig->dato);
	
	
}

Nodod* recorrerLista(Nodod* cancionActual, int OFFSET)
{
	
	if(cancionActual == NULL)
		printf("\n lista de reproduccion vacia");
		
	
		
	if(OFFSET == 1)
		cancionActual = cancionActual->sig;
		
	else if(OFFSET == -1)
		cancionActual = cancionActual->ant; 
	
	
	return cancionActual;
	
	
}

void imprimirMenuListaIFD(ListaD lista,fn_imprimir imprimir)
{
	if(!lista.inicio) return;
	Nodod *aux = lista.inicio;
	int i = 0;
	do
	{
		
		printf("\n");
		printf("[%d]",i);
		imprimir(aux->dato);
		aux = aux->sig;
		i++;
	}while( aux && aux!= lista.inicio);
}

int eliminarCancionPosicion(ListaD *lista,void *dato,Nodod** cancionActual, fn_comparar comparar)
{
	
	
	if(!lista->inicio)
		return 0;
	
	
	Nodod* aux, *actual;
	actual = lista->inicio;
	
	
	for(int i = 0; i<lista->cant; actual = actual->sig,i++)
	{
		//para funcion generica, usar comparar(dato,actual->dato);
		if(comparar(dato, &i) == 0)
		{
			// si el que se va a eliminar es al inicio(se contempla si solo es un nodo en la lista) y es lista normal
			if(actual == lista-> inicio && lista->bucle == 0)
			{
				aux = actual;
				if(actual->sig)
				{
					lista->inicio = lista->inicio->sig;
					lista->inicio->ant = NULL;
				}
				else
					lista->fin = lista->inicio = NULL;
			}
			// si el que se a a eliminar es el primero pero la lista es circular
			else if(actual == lista-> inicio && lista->bucle == 1)
			{
				
				aux = actual; 
				if(actual ->sig!=actual)
				{
					actual->ant->sig = actual->sig; 
					actual->sig->ant= actual->ant;
					lista->inicio = actual->sig; 
				}
				else
					lista->fin = lista->inicio = NULL;
			}
			// si el elemento a eliminar es el final (se contempla si solo es un nodo en la lista)
			else if (actual == lista->fin && lista->bucle == 0)
			{
				aux = actual;
				if(actual ->ant)
				{
					lista->fin = lista->fin->ant;
					lista->fin->sig = NULL;
				}
				else 
					lista->fin = lista->inicio = NULL;
				
			}
			// si el que se va a eliminar es el final pero la lista es circular
			else if (actual == lista->fin && lista->bucle == 1)
			{
					aux = actual;
					if(actual->sig!=actual)
					{
						actual->ant->sig = actual->sig; 
						actual->sig->ant = actual->ant;
						lista->fin = actual->ant;
						
					}
					else
						lista->fin= lista->inicio = NULL;
				
				
			}
			// si el elemento a eliminar es un elemento de en medio
			else
			{
				aux = actual;
				actual->ant->sig  = actual->sig;
				actual ->sig-> ant = actual->ant;
				
				
			}
			//no aplica para funcion generica-------MODIFICADO PARA CANCION
			if((aux == *cancionActual && aux->sig != aux)&& aux->sig)
				*cancionActual= recorrerLista(*cancionActual,1);
			else if((aux == *cancionActual && aux->ant != aux)&&aux->ant)
				*cancionActual= recorrerLista(*cancionActual,-1);
			else if(aux == *cancionActual)
				*cancionActual = NULL;
				
			free(aux);
			lista->cant--;
			return 1;
		}
		
		
		
	}
	
	return -1;
	
	
	
}