default: prog 

ListDeque.o: ListDeque.c ListDeque.h type.h
	gcc -Wall -ansi -c ListDeque.c

HashMap.o: HashMap.c HashMap.h
	gcc -Wall -ansi -c HashMap.c

prog: HashMap.o ListDeque.o main.c
	gcc -Wall -ansi -o prog HashMap.o ListDeque.o main.c

prog2: HashMap.o ListDeque.o main.c
	gcc -Wall -ansi -o prog HashMap.o ListDeque.o main2.c

clean:
	rm HashMap.o
	rm ListDeque.o

cleanall: clean
	rm prog
