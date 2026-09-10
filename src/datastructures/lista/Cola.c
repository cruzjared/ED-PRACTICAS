#include "Cola.h"

Cola *crearCola(void)
{
	return (Cola*)calloc(1,sizeof(Cola));
}

Cola inicializarCola(void)
{
	return (Cola){.inicio=NULL,.fin=NULL,.cant=0};
}

void enqueue(Cola *cola,void *dato)
{
	
	Nodo*aux = crearNodo(dato);
	if(!cola->inicio)
	{
		cola->inicio = aux; 
		cola->fin = cola->inicio;
		
	}
	else
	{
		cola->fin->sig = aux;
		cola->fin = cola->fin->sig; 
		
	}
	cola->fin->sig = NULL;
	cola->cant++;
	
	
}

void enqueueN(Cola *cola,Nodo* nodo)
{
	
	if(!cola->inicio)
	{
		
		cola->inicio = nodo;
		cola->fin = nodo;
		
	}
	else  
	{
		
		cola->fin->sig = nodo;
		cola->fin = cola->fin->sig;
		
	}
	
	cola->fin->sig = NULL;
	cola->cant++;
	
}

void* dequeue(Cola *cola)
{
	Nodo *aux = NULL;
	void*valor;
	
	if(!cola-> inicio)
		return NULL;
	
	aux = cola->inicio;
	
	cola->inicio = cola->inicio->sig;
	valor = aux->dato;
	
	if(cola->inicio == cola->fin->sig)
	{
		cola->inicio = NULL;
		cola->fin = NULL;
	}
	
	free(aux);
	cola->cant--;
	return valor;
}

Nodo* dequeueN(Cola *cola)
{
	Nodo *aux = NULL;
	
	if(!cola->inicio)
		return aux; 
	
	
	aux = cola->inicio; 
	cola->inicio = cola->inicio->sig;
	
	
	if(cola->inicio == cola->fin->sig)
	{
		cola->inicio = NULL;
		cola->fin = NULL;
	}
	cola->cant--;
	
	
	
	return aux;
}


//revisar
void imprimirCola(Cola cola,fn_imprimir imprimir)
{


	if(!cola.inicio)
	{
		
		printf("\n Lista vacia");
		return;
	}

	Nodo*aux;
	
	
	for(int i =0; i<cola.cant; i++)
	{
		
		
		aux = cola.inicio;
		imprimir(aux);
		cola.inicio = cola.inicio->sig; 
		cola.fin->sig = aux;
		cola.fin = cola.fin->sig;
		cola.fin->sig = NULL;
		
		
				
		
		
		
	}


}

void eliminarCola(Cola *cola,fn_free liberar)
{
	
	if(!cola->inicio)
		return;
	Nodo*aux;
	
	while (cola->inicio)
	{
		
		aux = cola->inicio; 
		cola->inicio = cola->inicio->sig; 
		liberar(aux);
		
		
	}
	
	
	cola->fin = cola->inicio; 
	cola->cant = 0;
	
	
	
	
	
	
	
}


//revisar
int buscarDatoCola(Cola cola,void *dato,fn_comparar comparar)
{
	
	if(!cola.inicio)
		return -1;
	
	Nodo*aux;
	
	for(int i = 0; i<cola.cant;i++)
	{
		
		
		aux = cola.inicio;
		if(comparar(cola.inicio->dato,dato) == 0)
			return 1;
		
		
		cola.inicio = cola.inicio->sig;
		cola.fin->sig= aux;
		cola.fin = cola.fin->sig;
		cola.fin->sig = NULL;

		
		
		
		
	}
	
	
	return 0;
}