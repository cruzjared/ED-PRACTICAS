#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <ListaD.h>
#include <windows.h>
#include "Cancion.h"


int main(void)
{
    int option,corre_programa;
	char c;
    corre_programa=1;
	Canciones canciones = cargarCanciones();
	//ListaD lista = inicializarListaD();
	int opc, cancion;
	ListaD lista = inicializarListaD();
	Nodod* cancionActual = NULL;

	

    while(corre_programa)
    {
		system("cls");
		if(lista.cant == 1)
			cancionActual = lista.inicio;
		displayCanciones(cancionActual,imprimirNombre);
        printf("\n\r");
        printf("\n\r");
        printf("\n\r [0] BUCLE");
        printf("\n\r [1] ANTERIOR");
        printf("\n\r [2] SIGUIENTE");
        printf("\n\r [3] AGREGAR CANCION");
        printf("\n\r [4] MOSTRAR LISTA DE REPRODUCCION");
        printf("\n\r [5] QUITAR CANCION");
        printf("\n\r [6] REINICIAR REPRODUCCION");
        printf("\n\r [7] TERMINAR PROGRAMA");

        printf("\n\r Escoge opcion: ");
        scanf("%d",&option);
		while( (c=getchar())!='\n' && c!=EOF);
		switch(option)
        {
        case 0:
                //CAMBIA EL COMPORTAMIENTO DE LA COLA
                //SI NO ERA COLA CIRCULAR, LA HACE CIRCULAR
                //SI ERA COLA CIRCULAR, LA DESHACE
				convertirLista(&lista);
				if(lista.bucle == 1)
					printf("\nLa lista esta en bucle");
				else
					printf("\n El bucle ha sido desactivado");
                break;
        case 1:
                //ACTUALIZA EL APUNTADOR DE LA ELEMENTO ACTUAL EN REPRODUCCION AL ANTERIOR
				if(!lista.inicio)
					printf("\n Lista vacia. Accion no valida");
				else if(cancionActual->ant == NULL)
					printf("\n Primera cancion, no es posible retroceder mas");
				else
					cancionActual =recorrerLista(cancionActual,-1);
                break;
        case 2:
                //ACTUALIZA EL APUNTADOR DE LA ELEMENTO ACTUAL EN REPRODUCCION AL SIGUIENTE
				if(!lista.inicio)
					printf("\n Lista vacia. Accion no valida");
				else if(cancionActual->sig == NULL)
					printf("Ultima cancion, no es posible adelantar mas");
				else
					cancionActual =recorrerLista(cancionActual,1);
                break;
        case 3:
                //SE MUESTRA UN MENU CON LAS CANCIONES DISPONIBLES
                //SE SELECCIONA LA CANCION
                //SE MUESTRA LA COLA DE REPRODUCCION
                //SE SELECCIONA EN QUE POSICION DE LA COLA SE AGREGARA
                //SE AGREGA LA CANCION A LA COLA RESPETANDO FIFO DE LA COLA DE REPRODUCCION
				
				
				printf("\n --------------------MENU CANCIONES--------------------\n");
				imprimirCanciones(canciones);
				printf("\n\n SELECCIONE OPCION: ");
				scanf("%d", &cancion);
				clear_buffer();
				printf("\n\nEn que posicion de la cola desea agregar la cancion?: ");
				scanf("%d", &opc);
				clear_buffer();
				while(opc >lista.cant)
				{
					
					printf("\n Posicion no valida, vuelva a ingresar posicion: ");
					scanf("%d", &opc);
					clear_buffer();
					
				}
				agregarPosicion(&lista,&canciones.cancion[cancion],opc);
				printf("\n Cancion agregada a la cola");
			
                break;
        case 4:
                
				printf("\n\n");
				if(!lista.inicio)
					printf("\n Lista vacia");
				else
					imprimirListaIFD(lista,imprimirNombre);
                break;
        case 5:
                //SE MUESTRA UN MENU CON LAS CANCIONES DE LA COLA DE REPRODUCCION RESPETANDO FIFO
                //SE SELECCIONA UNA OPCION Y SE ELIMINA, RESPETANDO FIFO
				if(!lista.inicio)
					printf("\n Lista vacia");
				else
				{
					printf("\n Canciones a eliminar");
					imprimirMenuListaIFD(lista,imprimirNombre);
					printf("\n SELECCIONE OPCION: ");
					scanf("%d",&opc);
					clear_buffer();
					int eliminar = eliminarCancionPosicion(&lista, &opc,&cancionActual, compararPosicionCancion);
					if(eliminar == -1)
						printf("\n Dato no encontrado");
					
				}
			
                break;
        case 6:
                //LA POSICION ACTUAL CAMBIA AL INICIO DE LA COLA DE REPRODUCCION
				if(!lista.inicio)
					printf("\n Lista vacia");
				else
				{
					cancionActual = lista.inicio;
					printf("\n Lista de reproduccion reiniciada");
				}
                break;
        case 7:
                corre_programa=0;
                break;
        default:
                break;
        }
		printf("\n presione ENTER para continuar");
		c = getchar();
		if(c!= '\n')
		{
			clear_buffer();
		}
    }
    printf("\n FIN DE PROGRAMA \n\r");
    return 0;
}