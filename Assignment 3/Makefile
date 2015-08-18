default: prog 

ListDeque.o: ListDeque.c ListDeque.h type.h 
	gcc -Wall -ansi -c ListDeque.c

prog: ListDeque.o main.c
	gcc -Wall -ansi -o prog ListDeque.o main.c

clean:
	rm ListDeque.o

cleanall: clean
	rm prog
