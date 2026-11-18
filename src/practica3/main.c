#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <iostring.h>
#include <Pila.h>

#define MAX 50


void imprimir(void *);
int palindromo(char* texto);
int aperturaCorrecta(char* texto);
int esPar(char a, char b);


int main(void)
{
	
    char cadena[MAX];
	
	int opc, ban = 1;
	int esPalindromo = -1;
	int apertura;
	char c; 
	
	
	
	while (ban == 1)
	{
		
		system("cls");
		printf("\n MENU");
		printf("\n [1] Palindromo");
		printf("\n [2] Verificar parentesis");
		printf("\n [3] Terminar programa");
		printf("\n SELECCIONE OPCION: ");
		scanf("%d", &opc); 
		clear_buffer();
		
		switch(opc)
		{
			
			case 1:
			inputCadena("\n Captura cadena: ",cadena,MAX);
			esPalindromo = palindromo(cadena);
			if(esPalindromo == 1)
				printf("\n La frase/palabra es palindromo");
			else
				printf("\n La frase/palabra no es palindromo");
			break;
			
			case 2:
			inputCadena("\n Ingresar cadena de parentesis: ", cadena, MAX);
			apertura = aperturaCorrecta(cadena);
			if(apertura == true)
				printf("\n Los parentesis abren y cierran correctamente");
			else
				printf("\n Los parentesis no abren y cierran correctamente");
			break;
			
			case 3:
			ban = 0; 
			
			
			
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



void imprimir(void *dato)
{
	printf("%c",*(char*)dato);
}


int palindromo(char* texto)
{
	
	Nodo* aux;
	Pila pila = inicializarPila(-1);	
	char textoSinEspacios [MAX];
	char arregloAux [MAX]; 
	int j = 0;
	
	
	for (int i = 0; texto[i] != '\0'; i++)
	{
		
		//hola a 
		if(texto[i] != ' ')
		{
			textoSinEspacios[j] = texto[i];
			push(&pila, &textoSinEspacios[j]);
			j++;
			
		}
		
		
	}
	
	textoSinEspacios[j] = '\0';
	
	int i ;
	for(i = 0; pilaVacia(pila) == false; i++)
	{
		aux = popN(&pila);
		arregloAux[i] =  *(char*)aux->dato;
	
	}
	
	arregloAux[i] = '\0';
	
	if(strcmpIC(textoSinEspacios, arregloAux) == 0)
		return 1;
	else 
		return 0; 
	
	
	
	
	
}


int aperturaCorrecta(char* texto)
{
	Nodo* aux;
	Pila pila = inicializarPila(-1);	
	
	
	int i, pareja;
	
	for (i = 0; texto[i] != '\0'; i++)
	{
		// si es apertura, pus a la pila
		if(texto[i] == '(' || texto[i] == '[' || texto[i] == '{')
			push(&pila, &texto[i]);
		else if(texto[i] == ')' || texto[i] == ']' || texto[i] == '}')
		{
			// si pila no esta vacia, pop
			if(pilaVacia(pila) == false)
			{
				aux = popN(&pila);
				pareja = esPar(*(char*)aux->dato, texto[i]);
				if (pareja == false)
					return false; 
				
			}
			else
				return false;
		}
		
		
		
	}
	
	if (pilaVacia(pila) == false)
		return false;
	else
		return true;
	
	
}

int esPar(char a, char b)
{
	
	if (a == '(' && b == ')')
		return 1;
	else if (a == '[' && b == ']')
		return 1;
	else if(a == '{' && b == '}')
		return 1;
	else 
		return 0;
	
	
	
}