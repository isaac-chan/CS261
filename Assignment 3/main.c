#include <stdio.h>
#include <stdlib.h>
#include "ListDeque.h"

int main (int argc, const char * argv[])
{
	ListDeque testDeque;
	TYPE val1 = 'A';
	TYPE val2 = 'B';
	TYPE val3 = 'C';
	int i;

	initListDeque(&testDeque);
	printListDeque(&testDeque);
	
	addBackListDeque(&testDeque, val1); printListDeque(&testDeque);	
	addBackListDeque(&testDeque, val2); printListDeque(&testDeque);
	addBackListDeque(&testDeque, val3); printListDeque(&testDeque);
	
	printf("contains('A') = %d, contains('D') = %d\n", containsListDeque(&testDeque, 'A'), containsListDeque(&testDeque, 'D'));
	printf("front() = %c, back() = %c\n", frontListDeque(&testDeque), backListDeque(&testDeque));
	
	removeBackListDeque(&testDeque); printListDeque(&testDeque);
	removeBackListDeque(&testDeque); printListDeque(&testDeque);
	removeBackListDeque(&testDeque); printListDeque(&testDeque);

	for(i = 0; i < 2; ++i)
	{
		addFrontListDeque(&testDeque, val3); printListDeque(&testDeque);
		addFrontListDeque(&testDeque, val2); printListDeque(&testDeque);
		addFrontListDeque(&testDeque, val1); printListDeque(&testDeque);
	}
	
	printf("contains('B') = %d, contains('R') = %d\n", containsListDeque(&testDeque, 'B'), containsListDeque(&testDeque, 'R'));
	printf("front() = %c, back() = %c\n", frontListDeque(&testDeque), backListDeque(&testDeque));
	
	reverseListDeque(&testDeque); printListDeque(&testDeque);
	
	removeListDeque(&testDeque, 'B'); printListDeque(&testDeque);
	removeListDeque(&testDeque, 'D'); printListDeque(&testDeque);
	
	removeFrontListDeque(&testDeque); printListDeque(&testDeque);
	removeFrontListDeque(&testDeque); printListDeque(&testDeque);
	removeFrontListDeque(&testDeque); printListDeque(&testDeque);
	removeFrontListDeque(&testDeque); printListDeque(&testDeque);
	
	freeListDeque(&testDeque);
	
	return 0;
}
