#ifndef HASHMAP_H_INCLUDED
#define HASHMAP_H_INCLUDED 1

#include "type.h"
#include "ListDeque.h"

struct HashMap {
	/* array of linked lists used to represent a hash table with chaining. */
	ListDeque* table;
	/* The number of buckets in the hash table */
    int tableSize;
	/* The number of actual key, value pairs stored in the hash tables*/
	int numItems;
	/*	An integer used in the _hash function to pick which hash funciton to use
		This is not usually a parameter of a typical HashMap because they usually
		only use 1 function, but we would like to test several functions in this assignment
	*/
	int hashChoice;
};
typedef struct HashMap HashMap;

void initHashMap(HashMap* hm, int tableSize, int hashChoice);
void freeHashMap(HashMap* hm);

void insertHashMap(HashMap* hm, TYPE toAdd);
MapElement* atHashMap(HashMap* hm, KeyType key);

void removeHashMap(HashMap* hm, KeyType key);

int longestChain(HashMap* hm);
int emptyBuckets(HashMap* hm);
int numCollisions(HashMap* hm);

void printHashMap(HashMap* hm, int showBuckets);

#endif
