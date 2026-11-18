#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <Arbol.h>
#include <Nodo.h>
#include <windows.h>



int* crearEntero(int dato);
int comparar(void*,void*);
void imprimir(void*);


int main(void)
{
	
	
	int opc,num;
	char c;
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.comparar = comparar;
	arbol.cant = 0;
	
	
	do
	{
		system("cls");
		printf("\n MENU");
		printf("\n [1] Insertar en arbol");
		printf("\n [2] Eliminar en arbol" );
		printf("\n [3] Balancear arbol ");
		printf("\n [4] Mostrar arbol");
		printf("\n [5] Terminar programa");
		printf("\n SELECCIONE OPCION: ");
		scanf("%d",&opc);
		clear_buffer();
		
		
		switch(opc)
		{
			
			case 1:
			printf("\nIngresar numero para insertar a arbol binario: ");
			scanf("%d",&num);
			clear_buffer();
			insertarArbolO(&arbol, crearEntero(num));
			printf("\n El numero %d ha sido insertado en el arbol",num);
			break;
			
			case 2:
			printf("\nIngresar numero para eliminar en el arbol binario: ");
			scanf("%d",&num);
			clear_buffer();
			eliminarDato(&arbol, crearEntero(num));
			break;
			
			case 3:
			printf("\nArbol antes\n\n");
			imprimirArbol(arbol,imprimir);
			printf("\n\n VALORES DEL ARBOL EN ORDEN:  ");
			imprimirOrden(arbol,imprimir,ORDEN);
			printf("\n\n\n");
			equilibrarArbol(&arbol);
			printf("\nARBOL EQUILIBRADO\n\n");
			imprimirArbol(arbol,imprimir);
			printf("\n\n VALORES DEL ARBOL EN ORDEN:  ");
			imprimirOrden(arbol,imprimir,ORDEN);
			
			break;
			
			
			case 4:
			printf("\n\n");
			imprimirArbol(arbol,imprimir);
			printf("\n\n VALORES DEL ARBOL EN ORDEN:  ");
			imprimirOrden(arbol,imprimir,ORDEN);
			printf("\n\n");
			printf("CANTIDAD DE NODOS EN EL ARBOL: %u",arbol.cant);
			
			break;
			
			
			case 5:
			printf("\n Terminando programa...");
			liberarArbol(&arbol);
			break;
			
			default:
			printf("\n Opcion no valida");
			break;
			
		}
		
		printf("\n presione ENTER para continuar");
		c = getchar();
		if(c!= '\n')
		{
			clear_buffer();
		}
		
		
		
		
		
		
		
		
	}while(opc!=5);
	
	
	return 0;
	
	
	
}


int* crearEntero(int dato)
{
	
	int* entero = calloc(1,sizeof(int));
	*entero = dato; 
	return entero;
	
	
}

int comparar(void* aa, void *bb)
{
	
	int a = *(int*)aa;
	int b = *(int*)bb;
	
	if(a < b) return -1;
	else if (a > b) return 1;
	else return 0;
	
	
}

void imprimir (void* dato)
{
	
	printf("%d", *(int*)dato);
	
	
	
}