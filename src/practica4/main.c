#include <stdio.h>
#include <stdlib.h>
#include <Pila.h>
#include <iostring.h>
#include "Laberinto.h"



Pila* resolverLab(Laberinto lab, Coordenada origen,Coordenada destino);
void imprimirPilaCoordenadas(Pila pila);

int main(void)
{
    Laberinto lab = crear_laberinto();
	//Movimientos mov;
	Coordenada origen = {1,1}; 
	Coordenada destino = {25,24};
	unsigned int nuevasCoor = 0;	
	inputEnteroSinSigno("\n Nuevas coordenadas? (1:SI 0:NO) : ",&nuevasCoor);
	if(nuevasCoor)
	{
		inputEntero("\n Captura Origen X: ",&origen.x);
		
		inputEntero(" Captura Origen Y: ",&origen.y);
		inputEntero("\n Captura Destino X: ",&destino.x);
		inputEntero(" Captura Destino Y: ",&destino.y);
	}
	setOrigen(lab,origen);
	setDestino(lab,destino);	
	
	Pila *pila = resolverLab(lab,origen,destino);
	printf("Las coordenadas usadas para completar el laberinto son: \n");
	imprimirPilaCoordenadas(*pila);
	
	
	
	printf("LABERINTO COMPLETADO\n\n\n");
	imprimirLab(lab);
	liberarLaberinto(lab);
	//eliminarPila(pila,free);
	//free(pila);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


Pila* resolverLab(Laberinto lab, Coordenada origen,Coordenada destino)
{
	Pila *pila = crearPila();
	*pila = inicializarPila(-1);	
	Coordenada *punto, *anterior, *nuevo;
	Movimientos movimientos;
	//PUSH INICIAL DEL ORIGEN
	punto = crearCoordenada(origen.x,origen.y);
	push(pila,punto);	
	
	//si la ultima coordenada del stack es igual al destino,rompe el ciclo
	while( !pilaVacia(*pila) && compararCoordenada(peek(*pila), &destino) != 1)
	{
		//consultas el anterior y avanzas sobre el
		anterior = peek(*pila);
		nuevo = crearCoordenada(anterior->x, anterior->y);
		
		//ver movimientos posibles para ver si esta bloqueado
		movimientos = movimientosPosibles(lab, *nuevo);
		
		//si no hay moviemientos, dibujas o, haces pop y hay nueva cima.
		if(bloqueado(movimientos))
		{
			lab[nuevo->x][nuevo->y] = 'o';
			pop(pila);
		}
		else
		{
			// aumentas nuevo por referencia. Haces push de la posicion actual;
			moverse(lab, &nuevo);
			push(pila, nuevo);
			
		}
		
		
		
		
		printf("\n\n\n Presione enter para continuar....");
		clear_buffer();
		imprimirLab(lab);		
		//punto = (Coordenada*)peek(*pila);
		//mov = movimientosPosibles(lab,*punto);		
		
	}
	if(!pilaVacia(*pila))
		printf("\n\n\nEl laberinto ha sido resuelto\n\n");
	else
		printf("\n\n\n El laberinto no tiene solucion\n\n");
	
	return pila;
}


void imprimirPilaCoordenadas(Pila pila)
{
	Pila pilaAux = inicializarPila(-1);
	
	while(!pilaVacia(pila))
	{
		
		push(&pilaAux, pop(&pila));
	}
	
	
	
	while(!pilaVacia(pilaAux))
	{
		imprimirCoordenada(pop(&pilaAux));
		printf("-> ");
	}

	
}