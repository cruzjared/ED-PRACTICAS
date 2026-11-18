
#include "Arbol.h"
#include <string.h>
#include <math.h>


size_t altura (Arbol arbol)
{

	if(!arbol.raiz)
		return 0; 
		
	if(!arbol.raiz->izq && !arbol.raiz->dch)
		return 1; 
		
	Arbol temp_izq, temp_dch; 
	size_t hi, hd;
	temp_izq.raiz = arbol.raiz->izq; 
	temp_dch.raiz = arbol.raiz->dch; 
	hi = altura(temp_izq);
	hd = altura(temp_dch); 
	
	
	if(hi > hd)
		return ++hi;
	else 
		return ++hd;
}

//recorrido con pila 
//el recorrido se hace en postorden

size_t alturaI (Arbol arbol)
{

	size_t max_altura = 0;
	
	if (!arbol.raiz)
		return max_altura;

	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			//SE RECORREN LOS HIJOS IZQUIERDOS
			// Apilar nodo padre antes del bajar
			push(&pila, actual);
			
			// Actualizar la altura máxima según la profundidad de la pila
			if (pila.cant > max_altura)
				max_altura = pila.cant;
			
			actual = actual->izq;
		}
		else
		{
			//Se consulta el padre
			Nodoa *padre = peek(pila);
			
			// Si existe hijo derecho y aún no lo hemos visitado, recorrer
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
			{
				actual = padre->dch;
			}
			else
			{
				// Remover si ya se recorrieron los hijos
				ultimo_visitado = pop(&pila);
			}
		}
	}
	  
		return max_altura;


}

//visita todas las ramas izquierdas, despues las derechas

void preordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			printf(" ");
			imprimir(actual->dato);
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = pop(&pila);
		}
	}
}

//visita hijo izquierdo, padre, hijo derecho.

void ordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = pop(&pila);			
			printf(" ");
			imprimir(padre->dato);
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = padre;
		}
	}
}



//visita hijo izquierdo, hijo derecho y padre....
void postordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
			{
				printf(" ");
				imprimir(padre->dato);
				ultimo_visitado = pop(&pila);
			}
		}
	}
}


void imprimirOrden(Arbol arbol,fn_imprimir imprimir,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			//preorden(arbol.raiz,imprimir);
			preordenI(arbol,imprimir);
			break;
		case ORDEN: 
			//orden(arbol.raiz,imprimir);
			ordenI(arbol,imprimir);
			break;
		/*case INVERSO: 
			inverso(arbol.raiz,imprimir);
			break;*/
		case POSTORDEN: 
			//postorden(arbol.raiz,imprimir);			
			postordenI(arbol,imprimir);
			break;
	}
}


void flipArbol(Arbol* arbol)
{
	
	if(!arbol->raiz)
		return;
	
	Pila pila = inicializarPila(-1);
	
	Nodoa* actual = arbol-> raiz;
	Nodoa* temporal; 
	Nodoa* ultimo_visitado = NULL;
	
	
	//recorrer arbol en preorden, si actual existe, hacer intercambio entre los hijos usando nodoa temporal. 
	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			temporal = actual->izq;
			actual->izq = actual->dch;
			actual->dch = temporal;
			
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = pop(&pila);
		}
	}
	
	
	
}


void insertarArbolO( Arbol *arbol, void *dato)
{
	
	
	
	if(!arbol->raiz)
	{
		arbol->raiz = crearNodoa(dato);
		arbol->cant++;
		return;
	}

	Nodoa* actual = arbol->raiz;
	Nodoa* nuevo = NULL;
	
	
	while(!nuevo)
	{
		
		if(arbol->comparar(dato, actual->dato) == -1)
		{
			if(actual->izq)
				actual = actual->izq;
			else
			{
				nuevo = crearNodoa(dato);
				actual->izq = nuevo;
				arbol->cant++;
			}
		}
		else
		{
			if(actual->dch)
				actual = actual->dch;
			else
			{
				nuevo = crearNodoa(dato);
				actual->dch = nuevo;
				arbol->cant++;
			}
		}
		
		
	}
	
	
	
}

void insertarNodoArbolO( Arbol *arbol, Nodoa* nuevo)
{
	
	
	
	if(!arbol->raiz)
	{
		arbol->raiz = nuevo;
		arbol->cant++;
		return;
	}

	Nodoa* actual = arbol->raiz;
	int bandera = 0;
	
	while(bandera == 0)
	{
		
		if(arbol->comparar(nuevo->dato, actual->dato) == -1)
		{
			if(actual->izq)
				actual = actual->izq;
			else
			{
				actual->izq = nuevo;
				bandera = 1;
			}
			
		}
		else
		{
			if(actual->dch)
				actual = actual->dch;
			else
			{
				actual->dch = nuevo;
				bandera = 1;
			}
		}
		
		
	}
	arbol->cant++;
	
	
	
}




void* buscarArbol(Arbol*arbol, void* dato)
{
	
	int* numero = calloc(1,sizeof(int));
	*numero = -1;
	
	if (!arbol->raiz)
		return numero;
	
	Nodoa* actual = arbol->raiz;
	
	while(actual)
	{
		
		if(arbol->comparar(dato,actual->dato)==-1)
			actual = actual->izq;
		else if (arbol->comparar(dato,actual->dato)==1)
			actual = actual->dch;
		else
			return actual->dato;
		
		
	}
	
	return numero;
	
	
	
}

void imprimir_arbol(Nodoa* nodo, int nivel,fn_imprimir imprimir)
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol,fn_imprimir imprimir)
{
	imprimir_arbol(arbol.raiz,0,imprimir);
}


void eliminarDato(Arbol* arbol, void*dato)
{
	
	if (!arbol->raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol->raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			
			if(arbol->comparar(dato,actual->dato) == 0)
			{
				Nodoa* elim = actual;
				Nodoa* padreElim = NULL;
				if(elim!=arbol->raiz)
					padreElim = pop(&pila);
					
				
				Nodoa* reserva = NULL;
				Arbol arbolAuxiliar;
				arbolAuxiliar.comparar = arbol->comparar;
				
				
				//caso dos hijos
				if(elim == arbol->raiz && (arbol->raiz->izq && arbol-> raiz->dch))
				{
					
					arbol->raiz = arbol->raiz->dch; 
					if(arbol->raiz->izq)
						reserva = arbol->raiz->izq; 
					arbol->raiz->izq = elim->izq; 
					if(reserva)
					{
						arbolAuxiliar.raiz = arbol->raiz->izq;
						insertarNodoArbolO(&arbolAuxiliar,reserva);
					}
					free(elim);
						
				}
				else if(elim == arbol->raiz && (arbol->raiz->izq && !arbol-> raiz->dch))
				{
					arbol->raiz = arbol->raiz->izq; 
					free(elim);
				}
				else if(elim == arbol->raiz && (!arbol->raiz->izq && arbol-> raiz->dch))
				{
					arbol->raiz = arbol->raiz->dch; 
					free(elim);
				}
				else if(elim == arbol->raiz && (!arbol->raiz->izq && !arbol->raiz->dch))
				{
					arbol->raiz = NULL;
					free(elim);
				}
				
				else if(elim->izq && elim->dch)
				{
					//prioridad nodo derecha para reemplazar a eliminado
					actual = elim->dch; 
					arbolAuxiliar.raiz = actual;
					if(actual->izq)
						//si actual tiene izquierda se reserva, ya que en esa izquierda se enlaza la izquierda de elim
						reserva = actual->izq; 
					
					//se ve si elim era hijo izquierdo o derecho, se pone actual en la rama correspondiente
					if(arbol->comparar(elim->dato,padreElim->dato)==-1)
						padreElim->izq = actual; 
					else
						padreElim->dch = actual;
					//se enlaza a la izquierda del actual la izquierda de elim
					actual->izq = elim->izq; 
					
					//insertar nodo de reserva en el subarbol.
					if(reserva)
						insertarNodoArbolO(&arbolAuxiliar,reserva);
					free(elim);
					
				}
				else if(elim->izq && !elim->dch)
				{
					if(arbol->comparar(elim->dato, padreElim-> dato) == -1)
						padreElim->izq = elim->izq;
					else 
						padreElim->dch = elim->izq;
					
					free(elim);
					
				}
				else if(!elim->izq && elim->dch)
				{
					if(arbol->comparar(elim->dato, padreElim-> dato) == -1)
						padreElim->izq = elim->dch;
					else 
						padreElim->dch = elim->dch;
					
					free(elim);
				}
				else
				{
					if(arbol->comparar(elim->dato, padreElim-> dato) == -1)
						padreElim->izq = NULL;
					else 
						padreElim->dch = NULL;
					
					free(elim);
				}
				
				arbol->cant--;
				return;
				
				
				
				
				
			}
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = pop(&pila);
		}
	}
	
	printf("\n\n NUMERO NO ENCONTRADO");
	
	
	
	
	
	
	
	
	
	
}





void equilibrarArbol(Arbol*arbol)
{
	
	
	

	
	if (!arbol->raiz)
		return ;
	Arbol subarbol1; 
	Arbol subarbol2; 

	//verificar si el arbol ya esta balanceado
	subarbol1.raiz = arbol->raiz->izq; 
	subarbol2.raiz = arbol->raiz->dch;
	int alturaDch = alturaI(subarbol1);
	int alturaIzq = alturaI(subarbol2); 
	
	
	if((alturaIzq - alturaDch) <= 1 && (alturaIzq - alturaDch) >= -1)
	{
		printf("\nEl arbol ya esta balanceado\n");
		return;
	}
	
	//recorrer en orden y crear arreglo de nodos
	
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol->raiz;
	Nodoa *ultimo_visitado = NULL;
	
	Nodoa* arregloOrdenado[arbol->cant];
	int i = 0;

	
	
	
	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = pop(&pila);
			arregloOrdenado[i] = padre; 
			i++;
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = padre;
		}
	}
	
	//una vez recorrido y armado el arreglo de nodoa en orden.....
	
	
	//eliminar enlaces antiguos de cada nodo del arreglo
	for(int j =0; j<i; j++)
	{
		
		arregloOrdenado[j]->izq = NULL;
		arregloOrdenado[j]->dch = NULL;
		
	}
	
	
	//evaluar el centro del arreglo completo; PENDIENTE DE REVISAR
	Rango rango; 
	int cantidad = i;
	rango.limInf = 0;
	rango.limSup = cantidad-1;
	rango.centro = -1; 
	push(&pila, &rango);
	int contador = 0;
	
	
	
	
	while(!pilaVacia(pila))
	{
		//.centro guarda el indice del centro;
		Rango *rangoAux = pop(&pila);
		rangoAux->centro = (rangoAux->limSup + rangoAux->limInf)/2; 
		if(contador == 0)
			arbol->raiz = arregloOrdenado[rangoAux->centro];
		
		
		
		Rango *rangoDch = calloc(1,sizeof(Rango));
		rangoDch->limInf = rangoAux->centro+1; 
		rangoDch->limSup = rangoAux->limSup;
		rangoDch->centro = (rangoDch->limSup + rangoDch->limInf)/2;
		
		if(rangoDch->limInf <= rangoDch->limSup)
		{
			arregloOrdenado[rangoAux->centro]->dch = arregloOrdenado[rangoDch->centro];
			push(&pila, rangoDch);
		}
		else
			arregloOrdenado[rangoAux->centro]->dch = NULL;
		
		
		
		//limite izquierdo
		Rango* rangoIzq = calloc(1,sizeof(Rango));
		rangoIzq->limInf = rangoAux->limInf; 
		rangoIzq->limSup = rangoAux->centro-1; 
		rangoIzq->centro = (rangoIzq->limSup + rangoIzq->limInf)/2; 
			
			
		if(rangoIzq->limInf <= rangoIzq->limSup)
		{
			arregloOrdenado[rangoAux->centro]->izq = arregloOrdenado[rangoIzq->centro];
			push(&pila, rangoIzq);
		}
		else
			arregloOrdenado[rangoAux->centro]->izq = NULL;
		
		contador++;
		
		
	}
	
	printf(" \n El arbol ha sido balanceado\n");
	
	
	
}


void liberarArbol(Arbol* arbol)
{
	
	if (!arbol->raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol->raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
			{
		
				free(padre);
				ultimo_visitado = pop(&pila);
			}
		}
	}
	
	
	arbol->raiz =NULL;
	arbol->cant = 0;
	
	
	
	
	
	
	
}


 int precedencias(char a)
{
	if(a == '^')
		return 3;
	else if(a == '*' || a == '/' )
		return 2;
	else if (a == '+' || a == '-')
		return 1;
	else if( a == '(' || a == ')')
		return 0; 
	else 
		return -1;
		
	
}


char* infix_Postfix(char* cadena)
{
	
	char* mensajeError = "Cadena no valida";
	
	if(cadena[0] == '\0')
		return mensajeError;
	

	
	Pila pila = inicializarPila(-1);
	
	
	char cadenaTemporal [strlen(cadena)];
	int j = 0;
	char c;
	
	for(int i = 0; cadena[i] != '\0'; i++)
		
	{
			
		// si cadena[i] es letra
		if(precedencias(cadena[i]) == -1)
		{
			cadenaTemporal[j] = cadena[i];
			j++;
		}
		//la pila esta vacia y es signo
		else if((pilaVacia(pila) && precedencias(cadena[i]) != -1) || cadena[i] == '(')
			push(&pila, &cadena[i]);
		else if(cadena[i] == ')')
		{
			
			while(*(char*) peek(pila) != '(')
			{
				char caracter =*(char*) pop(&pila);
				if(caracter != ')')
				{
					cadenaTemporal[j] = caracter; 
					j++; 
					
				}
			}
			//sacar (
			pop(&pila);
			
		}
		//si la cima tiene mayor o igual precedencia a cadena[i]
		else if( precedencias(*(char*) peek(pila)) >= precedencias(cadena[i]))
		{
			c = *(char*)pop(&pila);
			cadenaTemporal[j] = c; 
			j++;
			//push(&pila, &cadena[i]);
			i--;
		}
		//si es ( o de menor precedencia, push
		else
			push(&pila,&cadena[i]);	
	}
		
		
		

	//si se llego a \0 y sigue habiendo cosas en la pila
	while(!pilaVacia(pila))
	{
		c = *(char*)pop(&pila);
			cadenaTemporal[j] = c; 
			j++;
	}
	cadenaTemporal[j] = '\0';
	
	
	char* cadenaPostfix = calloc(strlen(cadenaTemporal)+1, sizeof(char));
	strcpy(cadenaPostfix, cadenaTemporal);
	return cadenaPostfix;
	
	
	
}



int arbolExpresion(char* cadenaPostfix, Arbol* arbol)
{
	if(cadenaPostfix[0] == '\0')
		return -1;

	
	
	
	
	Pila pila = inicializarPila(-1);
	
	for(int i = 0; cadenaPostfix[i] != '\0'; i++)
	{
		
		if(precedencias(cadenaPostfix[i]) == -1)
		{
			push(&pila,crearNodoa(&cadenaPostfix[i]) );
			
			
		}
		else
		{
			if(pila.cant < 2)
				return -1;
			
			Nodoa* nodoSigno = crearNodoa(&cadenaPostfix[i]);
			nodoSigno->dch = pop(&pila);
			nodoSigno->izq = pop(&pila);
			push(&pila, nodoSigno);
		}

	}

	arbol->raiz = pop(&pila);
	if(pilaVacia(pila))
	{
		arbol->cant = strlen(cadenaPostfix);
		return 1;
	}
	else
		return -1;
	
	
}


int buscarVariable(char c, Variable* arreglo, int contador)
{
	
	if(contador == 0)
		return -1; 
	
	for(int i = 0; i< contador; i++)
	{
		if(arreglo[i].operando == c)
			return 1;
	}
	
	return -1;
	
}



Variable* crearArregloVariables(Arbol arbol, int* longitud)
{
	
	
	
	if (!arbol.raiz)
		return NULL;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;
	Variable* variables = calloc(arbol.cant, sizeof(Variable));
	int contador = 0;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = pop(&pila);	
			if(precedencias(*(char*)padre->dato) == -1)
			{
				if(buscarVariable(*(char*)padre->dato, variables, contador) == -1)
				{
					char c;
					variables[contador].operando = *(char*)padre->dato;
					printf("Ingresar valor para variable %c: ", variables[contador].operando);
					scanf("%f", &variables[contador].valor);
					while( (c = getchar()) != '\n' && c !=EOF);
					contador++; 
				}
			}
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = padre;
		}
	}
	
	
	if(contador == 0)
	{
		free(variables);
		return NULL;
	}
	
	Variable* temporal = realloc(variables, contador*sizeof(Variable));
	if(temporal)
		variables = temporal;
	
	*longitud = contador;
	
	
	return variables;

	
	
	
	
	
}



Variable* buscarValorVariable(char c, Variable* arreglo, int longitud)
{
	
	
	if(arreglo == NULL)
		return NULL;
	
	for(int i = 0; i < longitud; i++)
	{
		
		if(arreglo[i].operando == c)
			return &arreglo[i];
	}
	
	
	return NULL;
	
	
}


float calcular(char c, float a, float b)
{
	
	
	if(c == '+')
		return a + b;
	else if( c == '-')
		return a - b;
	else if(c == '*')
		return a*b;
	else if(c == '/')
		return a/b;
	else if(c == '^')
		return pow(a,b);
	else 
		return -1;
	
	
	
}



float evaluarExpresion(Arbol arbol, int* longitudArreglo)
{
	

	float valorIzq = 0, valorDch = 0;
	Variable* variables = crearArregloVariables(arbol, longitudArreglo);
	
	
	//realizar recorrido postorden
	
	if (!arbol.raiz)
		return -1 ;
	Pila pila = inicializarPila(-1);
	Pila pilaAcum = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
			{
				Variable* valor = calloc(1, sizeof(Variable));
				if(precedencias(*(char*)padre->dato) == -1)
				{
					valor = buscarValorVariable(*(char*)padre->dato, variables, *longitudArreglo);
					push(&pilaAcum, &valor->valor);
				}
				else
				{
					valorDch = *(float*)pop(&pilaAcum);
					valorIzq = *(float*)pop(&pilaAcum);
					valor->valor = calcular(*(char*)padre->dato, valorIzq, valorDch);
					push(&pilaAcum, &valor->valor);
				}
				ultimo_visitado = pop(&pila);
			}
		}
	}
	
	return *(float*)pop(&pilaAcum);
	
	
	
	
}
