#include "Laberinto.h"


Movimientos movimientosPosibles(Laberinto lab,Coordenada punto)
{
	Movimientos movimientos = {0,0,0,0};
	//ARRIBA
	if( lab[punto.x-1][punto.y] == '*' || lab[punto.x-1][punto.y] == 'B')
		movimientos.up = 1;
	//ABAJO
	if( lab[punto.x+1][punto.y] == '*' || lab[punto.x+1][punto.y] == 'B')
		movimientos.down = 1;
	//DERECHA
	if( lab[punto.x][punto.y+1] == '*' || lab[punto.x][punto.y+1] == 'B')
		movimientos.right = 1;
	//IZQUIERDA
	if( lab[punto.x][punto.y-1] == '*'|| lab[punto.x][punto.y-1] == 'B')
		movimientos.left = 1;
	return movimientos;	
}

int moverse(Laberinto lab, Coordenada** punto)
{
	Movimientos movimientos = movimientosPosibles(lab, **punto); 
	
	//si esta bloqueado, no se puede hacer mas movimientos
	if(bloqueado(movimientos) != 0)
		return -1;
	
	
	
	// Se aumenta la coordenada el movimiento prioritario. Antes, se escribe un punto si no es A
	if(lab[(*punto)->x][(*punto)->y] != 'A')
		lab[(*punto)->x][(*punto)->y] = '.';
	if(movimientos.down == 1)
		(*punto)->x += 1; 
	else if(movimientos.left == 1)
		(*punto)->y -= 1;
	else if(movimientos.right == 1)
		(*punto)->y += 1;
	else if(movimientos.up == 1)
		(*punto)->x -= 1; 
	
	 
	
	// 1 si se logró el movimiento
	return 1; 
	
}

/*Coordenada* culdesac (Laberinto lab, Pila*pila, Coordenada* punto){

	Movimientos movimientos = movimientosPosibles(lab, *punto);
	if(bloqueado(movimientos))
		return punto;
	//guardar el inicio de un posible camino sin salida;
	//Coordenada* inicioCamino = punto;
	Coordenada*siguiente, *anterior;
	
	do
	{
		//moverse de acuerdo con la preferencia establecida
		moverse(lab, pila, punto);
		
		siguiente = sigMovimiento(lab, punto, movimientos);
		anterior = peek(*pila);
		movimientos = movimientosPosibles(lab, *anterior);
		
		
	
	}while(compararCoordenada(siguiente, anterior) != 0);
	
	
	//se hace pop hasta que el proximo movimiento sea diferente a retroceder
	while(compararCoordenada(siguiente, anterior) == 0)
	{
		lab[anterior->x][anterior->y] = 'o';
		siguiente = sigMovimiento(lab, punto, movimientos);
		anterior = pop(pila);
	}
	
	// 
	punto = anterior; 
	return anterior;
			
	
	
}
*/

// ver si siguietne movi
/*Coordenada* sigMovimiento (Laberinto lab, Coordenada* punto, Movimientos movimientos)
{
	
	int num = -99; 
	if (bloqueado(movimientos))
		return crearCoordenada(num, num);
	
	Coordenada* aux = crearCoordenada(num, num);
	
	if(movimientos.down == 1 && (lab[punto->x+1][punto->y] != 'x' && lab[punto->x+1][punto->y] != 'o' ))
		aux = crearCoordenada(punto->x+1,punto->y);
	else if(movimientos.left == 1 && (lab[punto->x][punto->y-1] != 'x' && lab[punto->x][punto->y-1] != 'o'))
		aux = crearCoordenada(punto->x, punto->y-1);
	else if(movimientos.right == 1 && (lab[punto->x][punto->y+1] != 'x' && lab[punto->x][punto->y+1] != 'o'))
		aux = crearCoordenada(punto->x, punto->y+1);
	else if(movimientos.up == 1 && (lab[punto->x-1][punto->y] != 'x' && lab[punto->x-1][punto->y] != 'o'))
		aux = crearCoordenada(punto->x-1, punto->y);
		
		
	return aux;
	
}
*/

void imprimirMovimientos(Movimientos movimientos)
{	
	printf("\n");
	//ARRIBA
	if( movimientos.up == 1)
		printf(" ARRIBA");
	//ABAJO
	if( movimientos.down == 1)
		printf(" ABAJO");
	//DERECHA
	if( movimientos.right == 1)
		printf(" DERECHA");
	//IZQUIERDA
	if( movimientos.left == 1)
		printf(" IZQUIERDA");
	
}


int bloqueado(Movimientos mov)
{
	return mov.up == 0 && mov.up == mov.down && mov.up==mov.left && mov.up==mov.right;
}
