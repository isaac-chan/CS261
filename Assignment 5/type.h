/*	type.h
	
	Defines the type to be stored in the data structure.  These macros
	are for convenience to avoid having to search and replace/dup code
	when you want to build a structure of doubles as opposed to ints
	for example.
*/

#ifndef __TYPE_H
#define __TYPE_H

#include <string.h>

#define KeyType char*
#define ValType int

struct MapElement {
	KeyType key;
	ValType value;
};
typedef struct MapElement MapElement;

# ifndef TYPE
# define TYPE     MapElement 
# define TYPE_SIZE sizeof(MapElement)
# endif

# ifndef EQ
# define EQ(A, B) (strcmp(A.key, B.key) == 0)
# endif

#endif
