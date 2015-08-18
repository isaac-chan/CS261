default: prog 

BST.o: BST.c BST.h type.h
	gcc -Wall -ansi -c BST.c

prog: BST.o main.c
	gcc -Wall -ansi -o prog BST.o main.c

clean:
	rm BST.o

cleanall: clean
	rm prog
