#include "heap.h"


void insertarHeap(Heap* heap,void* dato)
{
	
	
	if(heap->cant !=0)
	{
		
		void** auxiliar = NULL;
		while(!auxiliar)
		{
			auxiliar  = realloc(heap->datos,(heap->cant+1) * sizeof(void*) );
		}
		
		heap->datos = auxiliar; 
		
	}
	else
		heap->datos = calloc(1, sizeof(void*));
	
	heap->datos[heap->cant++] = dato; 
	if(heap->cant > 1)
		heapify(heap);
	
	
}


void* removerHeap(Heap* heap)
{
	
	
	void* auxiliar = NULL; 
	
	if(heap->cant != 0)
	{
		
		auxiliar = heap->datos[0];
		heap->datos[0] = heap->datos[--heap->cant];
		heap->datos = realloc(heap->datos, (heap->cant)*sizeof(void*));
		if(heap->cant > 0)
			heapify(heap);
		
		
	}
	
	
	return auxiliar; 
	
	
	
}


void* eliminarEspecifico(Heap* heap, void* dato)
{
	
	void* temporal = NULL; 
	
	if(heap->comparar(heap->datos[0], dato) != 0)
	{
		
		
		for(int i= 0; i<heap->cant; i++)
		{
			
			if(heap->comparar(heap->datos[i], dato) == 0)
			{
				
				temporal = heap->datos[i]; 
				heap->datos[i] = heap->datos[0];
				heap->datos[0] = temporal; 
				break;
			}
		}
	}
	
	if(temporal)
		temporal = removerHeap(heap);
		
	
	
	
		
	return temporal;	
	
}

void imprimirHeap(Heap* heap,fn_imprimir imprimir)
{
	if(!heap->datos)
		return;
	
	heapify(heap);
	printf("\n HEAP: ");
	for(int i = 0; i < heap->cant; i++)
	{
		imprimir(heap->datos[i]);
	}
	
	
	
}

void heapify(Heap *heap)
{
	if(!heap->datos)
		return;
	
	int* arregloPadres = calloc((heap->cant/2), sizeof(int)); 
	Pila pilaPadres = inicializarPila(-1);
	
	//creacion del arreglo de indices padres definido por (cant/2)-1 
	
	for(int i = 0; i < (heap->cant/2); i++)
	{
		arregloPadres[i] = i;
		push(&pilaPadres, &arregloPadres[i]);
		
	}
	
	
	
	
	while(!pilaVacia(pilaPadres))
	{
		int padre = *(int*)pop(&pilaPadres);
		int evaluado = padre; 
		int izq = 2*padre+1;
		int dch = 2*padre+2;
		// comparar si dch tiene lugar en el arreglo y si dch es mayor a el padre (es decir, si el heap esta desordenado)
		//primero se verifica hijo derecho, porque al ser completo siempre se tiene hijo izq en caso de ser nodo padre. 
		
		
		
		if(heap->type == HEAPMAX)
		{
			
			if(dch < heap-> cant && heap->comparar(heap->datos[dch], heap->datos[evaluado]) == 1)
				evaluado = dch; 
			if(heap->comparar(heap->datos[izq], heap->datos[evaluado]) == 1)
				evaluado = izq; 
			
		}
		else if (heap->type == HEAPMIN)
		{
			if(dch < heap-> cant && heap->comparar(heap->datos[dch], heap->datos[evaluado]) == -1)
				evaluado = dch; 
			if(heap->comparar(heap->datos[izq], heap->datos[evaluado]) == -1)
				evaluado = izq; 
			
		}
		
		
		if(evaluado != padre)
		{
			void* temporal = heap->datos[padre];
			heap->datos[padre] = heap->datos[evaluado];
			heap->datos[evaluado] = temporal;
			
			if(evaluado < (heap->cant/2))
				push(&pilaPadres, &arregloPadres[evaluado]); 
			
		}
		
	}
		
	
	
	free(arregloPadres);
	
	
	
	
	
	
	
}


void liberarHeap(Heap* heap)
{
	
	if(!heap->datos)
		return; 
	
	
	
	for (int i = 0; i < heap->cant; i++)
	{
		free(heap->datos[i]);
	}
	
	heap->cant = 0;
	heap->datos = NULL; 
	heap->type = HEAPMIN;
	
	
	
	
}


void imprimirHeapArbol(Heap* heap, fn_imprimir imprimir)
{
	
	
	Arbol arbol; 
	Cola cola = inicializarCola(); 
	 
	Nodoa* actual = crearNodoa(heap->datos[0]);
	enqueue(&cola, actual);
	arbol.raiz = actual;
	int padres = heap->cant/2; 
	
	
	

	for(int i = 0; i< padres; i++)
	{
		int izq = 2*i+1;
		int dch = 2*i+2; 
		
		actual = dequeue(&cola);
		actual-> izq = crearNodoa(heap->datos[izq]);
		enqueue(&cola, actual->izq);
		if(dch < heap->cant)
		{
			actual->dch = crearNodoa(heap->datos[dch]);
			enqueue(&cola, actual->dch);
			
		}
		
	}
	imprimirArbol(arbol, imprimir);
	
	
}