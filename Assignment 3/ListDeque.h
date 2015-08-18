#ifndef LIST_DEQUE_H_INCLUDED
#define LIST_DEQUE_H_INCLUDED

#include "type.h"

/* Link structure composing one element of the linked list. */
/* Note that it is doubly-linked (hence the D) */
struct DLink {
	TYPE value;				/* value of the link */
	struct DLink* next;		/* pointer to the next link */
	struct DLink* prev;		/* pointer to the previous link */
};
typedef struct DLink DLink;

/* Linked List datastructure, composed of DLink
 * Note that we have a pointer to both head and tail,
 * this means that add/remove to the front/back in O(1) time
 */
struct ListDeque {
	int size;		/* number of links in the deque */
	DLink* head;	/* pointer to the front */
	DLink* tail;	/* pointer to the back */
};
typedef struct ListDeque ListDeque;

/* Basic Operations */
void initListDeque(ListDeque* q);
void freeListDeque(ListDeque* q);

int isEmptyListDeque(ListDeque *q);

TYPE frontListDeque(ListDeque* q);
TYPE backListDeque(ListDeque* q);

void addLinkAfterListDeque(ListDeque* q, DLink* addAfter, DLink* newLink);
void addLinkBeforeListDeque(ListDeque* q, DLink* addBefore, DLink* newLink);
DLink* removeLinkListDeque(ListDeque* q, DLink* toRemove);

/* Deque interface */
void addBackListDeque(ListDeque* q, TYPE val);
void addFrontListDeque(ListDeque* q, TYPE val);
void removeFrontListDeque(ListDeque* q);
void removeBackListDeque(ListDeque* q);

/* Bag Interface */	
int containsListDeque(ListDeque* q, TYPE val);
void removeListDeque(ListDeque* q, TYPE val);

/* Other functions */
void reverseListDeque(ListDeque* q);
void printListDeque(ListDeque* q);

#endif
