default: prog 

ListDeque.o: ListDeque.c ListDeque.h type.h
	gcc -Wall -ansi -c ListDeque.c

graph.o: graph.h graph.c ListDeque.o
	gcc -Wall -ansi -c graph.c

prog: graph.o ListDeque.o main.c
	gcc -Wall -ansi -o prog graph.o ListDeque.o main.c

clean:
	rm ListDeque.o
	rm graph.o

cleanall: clean
	rm prog 