default: prog 

dynArray.o: dynArray.c dynArray.h type.h 
	gcc -Wall -ansi -c dynArray.c

prog: dynArray.o
	gcc -Wall -ansi -o prog dynArray.o unitTests.c

clean:
	rm dynArray.o

cleanall: clean
	rm prog 