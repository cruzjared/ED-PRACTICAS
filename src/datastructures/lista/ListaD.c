#include "ListaD.h"


ListaD inicializarListaD(void)
{
	return (ListaD){.inicio=NULL,.fin=NULL,.cant=0,.orden=NINGUNO,.comparar=NULL,.bucle=0};
}
void insertarOrdenadoD(ListaD *lista,void *dato)
{
	if(!lista->inicio || lista->comparar(dato,lista->inicio->dato) < 0)
		insertarInicioD(lista,dato);
	else if( lista->comparar(dato,lista->fin->dato) > 0)
		insertarFinalD(lista,dato);
	else
	{
		Nodod *nuevo = crearNodod(dato);
		Nodod *q = lista->inicio;
		Nodod *p = q->sig;
		while( lista->comparar(dato,p->dato) > 0) 
		{
			q = p;
			p = p->sig;
		}
		q->sig = nuevo;
		nuevo->ant = q;
		nuevo->sig = p;
		p->ant = nuevo;
		lista->cant++;
	}	
}

void imprimirListaIFD(ListaD lista,fn_imprimir imprimir)
{
	if(!lista.inicio) return;
	Nodod *aux = lista.inicio;
	do
	{
		//printf("\n");
		imprimir(aux->dato);
		printf("->");
		aux = aux->sig;
	}while( aux && aux!= lista.inicio);
	if(lista.bucle == 0)
		printf(" NULL");
	else
		imprimir(aux->dato);
}
void imprimirListaFID(ListaD lista,fn_imprimir imprimir)
{
	if(!lista.inicio) return;
	Nodod *aux = lista.fin;
	do
	{
		//printf("\n");
		imprimir(aux->dato);
		printf(" --> ");
		aux = aux->ant;
	}while( aux && aux!= lista.fin);
}

int eliminarDatoD(ListaD *lista,void*dato, fn_comparar comparar)
{
	
	
	if(!lista->inicio)
		return 0;
	
	
	Nodod* aux, *actual;
	actual = lista->inicio;
	
	
	for(int i = 0; i<lista->cant; actual = actual->sig,i++)
	{
		//para funcion generica, usar comparar(dato,actual->dato);
		if(comparar(dato, actual->dato) == 0)
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
				
			free(aux);
			lista->cant--;
			return 1;
		}
		
		
		
	}
	
	return -1;
	
	
	
}





void eliminarListaD(ListaD *lista,fn_free liberar)
{
	
	
	if(!lista->inicio)
		return; 
	
	
	Nodod* aux; 
	
	while(lista->inicio)
	{
		
		aux = lista->inicio; 
		lista->inicio = lista->inicio->sig;
		if(lista->inicio)
			lista->inicio->ant = NULL;
		liberar(aux); 
		
		
	}
		
		
		
	
	
	lista->fin = lista->inicio; 
	lista->cant = 0;
	
	
}

void insertarInicioD(ListaD *lista,void *dato)
{
	Nodod *nuevo = crearNodod(dato);
	if(!lista->inicio)
		lista->inicio = lista->fin = nuevo;
	else if(lista->bucle == 0)
	{
		nuevo->sig = lista->inicio;
		lista->inicio->ant = nuevo;
		lista->inicio = nuevo;
	}
	else if(lista->bucle == 1)
	{
		
		lista->inicio->ant = nuevo; 
		lista->fin ->sig = nuevo;
		nuevo->ant = lista->fin; 
		nuevo->sig = lista->inicio; 
		lista->inicio = nuevo;
		
			
	}
	lista->cant++;
}

void insertarFinalD(ListaD *lista,void *dato)
{
	Nodod *nuevo = crearNodod(dato);
	if(!lista->inicio)
		lista->inicio = lista->fin = nuevo;
	else if (lista->bucle == 0)
	{
		nuevo->ant = lista->fin;
		lista->fin->sig = nuevo;
		lista->fin = nuevo;
	}
	else if(lista->bucle == 1)
	{
		lista->fin->sig = nuevo; 
		lista->inicio->ant = nuevo; 
		nuevo->ant = lista->fin;
		nuevo->sig = lista->inicio;
		lista->fin = nuevo;
		
	}
	lista->cant++;
	
}




int buscarDatoD(ListaD lista,void *dato,fn_comparar comparar)
{
	if(!lista.inicio)
		return -1;
	
	
	Nodod* aux; 
	
	
	for(int i = 0; i<lista.cant; i++)
	{
		aux = lista.inicio;
		
		if(comparar(lista.inicio->dato,dato) == 0)
			return 1; 
		
		lista.inicio = lista.inicio->sig; 
		lista.fin->sig = aux; 
		lista.fin = lista.fin->sig; 
		lista.fin->sig = NULL;
		
		
		
	}
	
	
	return 0;
}
void ordenarListaD(ListaD *lista,fn_comparar comparar,Orden orden)
{
	
}


void agregarPosicion(ListaD *lista,void* valor, int posicion)
{
	
	Nodod* actual,*aux; 
	
	int posActual = 0;
	aux = crearNodod(valor);
	
	//si lista inicio no existe y se quiere posicion 0
	if(!lista->inicio && posicion == 0)
	{
		insertarFinalD(lista,valor);
		return;
	}
	
	
	
	for(actual = lista->inicio;actual;actual=actual->sig, posActual++)
	{
		//si se inserta al inicio 
		if(posicion == 0 && actual == lista->inicio)
		{
			insertarInicioD(lista,valor);
			return;
		}
		//insertar al final
		else if(posicion == lista->cant)
		{
			
			insertarFinalD(lista,valor);
			return;
		}
		
		else if(posicion == posActual)
		{
			aux->ant = actual->ant;
			aux ->sig = actual;
			actual->ant->sig = aux;
			actual->ant = aux; 
			lista->cant++;
			return;
			
			
			
		}
	
		
		
		
		
	}
	
	
	
	
	
	
	
}

void convertirLista(ListaD* lista)
{
	if(!lista->inicio)
		return;
	
	
	
	if(lista->bucle == 0)
	{
		
		lista->bucle = 1; 
		lista->inicio->ant = lista->fin; 
		lista->fin->sig = lista->inicio;
		
	}
	else if(lista->bucle == 1)
	{
		lista->bucle = 0;
		lista->inicio->ant = NULL;
		lista->fin->sig = NULL;
	}
	
	
	
}

