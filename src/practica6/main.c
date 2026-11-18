#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <Arbol.h>
#include <Nodo.h>
#include <windows.h>
#include <iostring.h>

#define MAX 100







int comparar(void* aa, void *bb);
void imprimir (void* dato);



int main(void)
{

	int opc;
	int validacionArbol = -1;
	int longitud;
	float resultado;
	char c;
	char* cadena = " ";
	char* postfix = " ";
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.comparar = comparar;
	arbol.cant = 0;
	
	
	
	do
	{
		system("cls");
		printf("EXPRESION: ");
		if(aperturaCorrecta(cadena) == 1 && validacionArbol == 1)
			printf("%s", cadena);
		printf("\n\n MENU");
		printf("\n [0] Capturar expresion");
		printf("\n [1] Imprimir arbol de expresion");
		printf("\n [2] Evaluar expresion" );
		printf("\n [3] Terminar programa ");
		printf("\n SELECCIONE OPCION: ");
		scanf("%d",&opc);
		clear_buffer();
		
		
		switch(opc)
		{
			
			case 0:
			inputCadenaDinamica("\nIngresar expresion a evaluar: ", &cadena, MAX);
			if(aperturaCorrecta(cadena) == 1)
			{
				postfix = infix_Postfix(cadena);
				validacionArbol = arbolExpresion(postfix, &arbol);
				if(validacionArbol == -1)
				{
					printf("\n\nExpresion no valida");
					break;
				}
				printf(" \n\n CADENA INFIX: %s", cadena);
				printf("\n CADENA POSTFIX: %s",postfix);
				
			}
			else
				printf("\n\nCadena no valida");
			
				
			break; 
			
			case 1:
			if(postfix[0] == ' ' || arbol.raiz == NULL)
				printf("No es posible realizar la accion");
			else
			{
				
				printf("\n\n");
				imprimirArbol(arbol, imprimir);
				printf("\n\n EXPRESION POSTFIX: %s \n\n",postfix);
				
			}
			
			
			break;
			
			case 2:
			
			if(postfix[0] == ' ' || arbol.raiz == NULL)
				printf("No es posible realizar la accion");
			else
			{
				
				printf("\n\n");
				imprimirArbol(arbol, imprimir);
				printf("\n\n EXPRESION POSTFIX: %s \n\n",postfix);
				resultado = evaluarExpresion(arbol, &longitud);
				printf("EL RESULTADO DE LA EXPRESION ES: %f", resultado);
			}
			
	
		
			break;
			
			case 3:
			printf("\n Terminando programa...");
			liberarArbol(&arbol);
			free(cadena);
			break;
			
			default:
			printf("\n Opcion no valida");
			break;
			
		}
		
		printf("\n\n\n presione ENTER para continuar");
		c = getchar();
		if(c!= '\n')
			clear_buffer();
		
		
		
		
		
		
		
		
		
	}while(opc!=3);








	return 0;

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
	
	printf("%c", *(char*)dato);
	
	
	
}