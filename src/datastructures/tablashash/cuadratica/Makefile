cflags = -Wall -Werror -std=c99 -O2 -c
dflags = -Wall -Werror -std=c99 -g
includes = -I ../../nodo -I ../../lista -I ../../arbol
sourceNodo = ../../nodo/Nodo.o ../../lista/pila.o ../../arbol/arbol.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../../lib/libHashQ.a

build :
	gcc $(cflags) $(includes) $(source) 
	-rm -f "$(output)"
	ar rcs $(output) $(source_o) $(sourceNodo)
	@echo "Compilo Exitosamente!!!"
	
	
	
