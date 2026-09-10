#include "Lista.h"


Lista inicializarLista(void)
{
	return (Lista){.inicio=NULL,.fin=NULL,.cant=0,.orden=NINGUNO};
}


void imprimirLista(Lista lista,fn_imprimir imprimir)
{
	Nodo *aux;
	if(!lista.inicio)
	{
		printf("\n Lista vacia");
		return;
	}	
	printf("\n [ALUMNOS %d]Lista: \n\n",lista.cant);
	aux = lista.inicio;
	while( aux )
	{
		imprimir(aux->dato);
		printf("\n");
		aux = aux->sig;
	}
}

void eliminarLista(Lista *lista)
{
	if( !lista->inicio) return;
	Nodo *aux;
	while( lista->inicio)
	{
		aux = lista->inicio;
		lista->inicio = lista->inicio->sig;
		free(aux);
	}
	lista->fin = lista->inicio;
	lista->cant = 0;
}

void insertarFinal(Lista *lista,void *dato)
{
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = crearNodo(dato);
		lista->cant++;
		return;
	}
	lista->fin->sig = crearNodo(dato);
	lista->fin = lista->fin->sig;
	lista->cant++;
}

void eliminarDato(Lista *lista,void *dato,fn_comparar comparar)
{	
	if(!lista->inicio)
		return;
	
	for(Nodo *ant=NULL,*elim=lista->inicio ; elim ; ant = elim , elim = elim->sig)
	{
		if( comparar( dato , elim->dato ) == 0)
		{
			if( lista->inicio == elim)
				lista->inicio = elim->sig;
			else
				ant->sig = elim->sig;
			if( lista->fin == elim)
				lista->fin = ant;
			free(elim);
			lista->cant--;
			return;
		}
	}	
}

int buscarDato(Lista lista,void *dato,fn_comparar comparar)
{
	if(!lista.inicio)
		return 0;
	while(lista.inicio)
	{
		if(comparar( dato, lista.inicio->dato ) == 0)
			return 1;
		lista.inicio = lista.inicio->sig;
	}
	
	return 0;
}


void ordenarLista(Lista *lista,fn_comparar comparar,Orden orden)
{
	if(orden == NINGUNO)
		return;
	lista -> comparar = comparar;
	lista->orden = orden;
	
	for( Nodo *i = lista->inicio ; i ; i = i->sig)
	{
		Nodo *cmp = i;
		for( Nodo *j = i->sig ; j ; j = j->sig)
		{
			if(orden == ASCENDENTE && comparar(cmp->dato,j->dato)>0)
				cmp = j;
			else if(orden == DESCENDENTE && comparar(cmp->dato,j->dato)<0)
				cmp = j;			
		}
		if(cmp!=i)
			swapNodo(i,cmp);
	}
}



void insertarOrdenada(Lista * lista, void* dato)
{
	if(!lista-> inicio || lista->orden == NINGUNO)
	{
		insertarFinal(lista,dato);
		return;
	}
	
	Nodo* actual, *posterior, *aux;
	aux = crearNodo(dato);
	
	for(actual =lista->inicio, posterior =actual->sig; posterior; actual=actual->sig, posterior = posterior-> sig)
	{
		
		// si va al inicio
		if(actual == lista->inicio && lista->comparar(dato,actual->dato)<= 0 && lista->orden == ASCENDENTE)
		{
		
			lista->inicio = aux;
			aux->sig = actual;
			lista->cant++;
			return;
			
			
		}
		else if(actual == lista->inicio && lista->comparar(dato,actual->dato)>=0 && lista->orden == DESCENDENTE)
		{
			lista->inicio = aux;
			aux->sig = actual;
			lista->cant++;
			return;
			
			
		}
		
		
		//si va en un nodo de en medio
		if((lista->comparar(dato,actual->dato) >= 0 && lista->comparar(dato,posterior->dato)<=0) && lista->orden == ASCENDENTE)
		{
			
			actual->sig = aux;
			aux->sig=posterior;
			lista->cant++;
			return;
		}
		else if(((lista->comparar(dato,actual->dato) <= 0 && lista->comparar(dato,posterior->dato)>=0) && lista->orden == DESCENDENTE))
		{
			
		
			actual->sig = aux;
			aux->sig=posterior;
			lista->cant++;
			return;
			
		}
		
		
		
	}
		insertarFinal(lista,dato);
	
	
	
	
	
	
	
}
