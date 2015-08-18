#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ListDeque.h"

/*	Create a link for a value.
	Use this function in your add operations to make it easier to allocate links

	param: 	val		the value to store in the newy created link
	pre:	none
	post:	a link is allocated on the heap, storing the argument value
	ret:	the newly allocated link
*/
DLink* _createLink(TYPE val)
{
	DLink* lnk = (DLink*) malloc(sizeof(DLink));
   	assert(lnk != 0);
	
	lnk->value = val;
	return lnk;
}

/* ************************************************************************
	Basic Operations
************************************************************************ */

/* Initializes a deque.

	param: 	d		pointer to the deque
	pre:	d is not null
	post:	size, head, and tail are initialized
*/
void initListDeque(ListDeque* d)
{
	d->size = 0;
	d->head = 0;
	d->tail = 0;
}

/*	De-allocate all links of the deque.
	Write this function in terms of a remove function, such as removeBack.

	param: 	d		pointer to the deque
	pre:	d is not null
	post:	All links are de-allocated
*/
void freeListDeque(ListDeque* d)
{
	while(!isEmptyListDeque(d)) 
		removeBackListDeque(d);		
}

/* Check whether the deque is empty.

	param: 	d		pointer to the deque
	pre:	d is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
*/
int isEmptyListDeque(ListDeque *d) 
{
	return d->size == 0;
}

/* Get the value stored in the link at the front of the deque

	param: 	d		pointer to the deque
	pre:	d is not null 
	pre:	d is not empty
	post:	none
	ret: 	value of the front of the deque
*/
TYPE frontListDeque (ListDeque *d) 
{
	assert(!isEmptyListDeque(d));
	return d->head->value;
}

/* Get the value stored in the link at the back of the deque

	param: 	d		pointer to the deque
	pre:	d is not null
	pre:	d is not empty
	post:	none
	ret: 	value of the back of the deque
*/
TYPE backListDeque(ListDeque *d)
{
	return d->tail->value;
}

/*	Adds a link AFTER another link. 
	Write your other add functions in terms of addAfter and addBefore when possible.

	param: 	d			pointer to the deque
	param: 	addAfter	pointer to the existing link in the deque
	param: 	newLnk		pointer to the new link to add after the existing link
	pre:	d is not null
	pre: 	newLnk has been properly initialized
	pre:	addAfter is in the deque if it is not a NULL pointer
	post:	newLnk is added into the deque AFTER the existing link
*/
void addLinkAfterListDeque(ListDeque* d, DLink* addAfter, DLink* newLnk)
{
	d->size++;
	if(!addAfter)
	{
	  	newLnk->next = 0;
		newLnk->prev = 0;
		d->head = newLnk;
		d->tail = newLnk;
		return;	
	}
	
  	newLnk->next = addAfter->next;
	newLnk->prev = addAfter;
	addAfter->next = newLnk;
	if(addAfter != d->tail)
		newLnk->next->prev = newLnk;
	else
		d->tail = newLnk;
}

/* Adds a link BEFORE another link. 
	Write your other add functions in terms of addAfter and addBefore when possible.

	param: 	d			pointer to the deque
	param: 	addBefore	pointer to the existing link in the deque
	param: 	newLnk		pointer to the new link to add before the existing link
	pre:	d is not null
	pre: 	newLnk has been properly initialized
	pre:	addBefore is in the deque if it is not a NULL pointer
	post:	newLnk is added into the deque AFTER the existing link
*/
void addLinkBeforeListDeque(ListDeque* d, DLink* addBefore, DLink* newLnk)
{	
	d->size++;
	if(!addBefore)
	{
		newLnk->next = 0;
		newLnk->prev = 0;
		d->tail = newLnk;
		d->head = newLnk;
		return;
	}
	
  	newLnk->next = addBefore;
	newLnk->prev = addBefore->prev;
	addBefore->prev = newLnk;
	if(addBefore != d->head)
		newLnk->prev->next = newLnk;
	else
		d->head = newLnk;
}

/*	Remove a link from the deque.
	Write our other remove functions in terms of this function when possible.
	Be careful not to use a pointer that you have already freed when returning.

	param: 	d		pointer to the deque
	param: 	lnk		pointer to the link to be removed
	pre:	d is not null 
	pre:	d is not empty
	pre:	lnk is in the deque 
	post:	lnk is removed from the deque
	ret:	The pointer which follows lnk
*/
DLink* removeLinkListDeque(ListDeque *d, DLink *lnk)
{
	DLink* returnVal = lnk->next;
  	if (d->size == 1)
	{
	  	d->tail = 0;
		d->head = 0;
	} else {
		if(lnk == d->tail)
			d->tail = lnk->prev;
		else
			lnk->next->prev = lnk->prev;
		
		if(lnk == d->head)
			d->head = lnk->next;
		else
			lnk->prev->next = lnk->next;
	}
	
	free(lnk);
	d->size--;
	return returnVal;
}

/* ************************************************************************
	Deque Interface
************************************************************************ */

/*	Adds a link to the back of the deque.
	Write this function in terms of addLinkAfter() when possible.

	param: 	d		pointer to the deque
	param: 	val		value for the link to be added
	pre:	d is not null
	post:	a link storing val is added to the back of the deque
*/
void addBackListDeque (ListDeque *d, TYPE val) 
{
	addLinkAfterListDeque(d, d->tail, _createLink(val));
}

/*	Adds a link to the front of the deque.
	Write this function in terms of addLinkBefore when possible.

	param: 	d		pointer to the deque
	param: 	val		value for the link to be added
	pre:	d is not null
	post:	a link storing val is added to the front of the deque
*/
void addFrontListDeque(ListDeque *d, TYPE val)
{
	addLinkBeforeListDeque(d, d->head, _createLink(val));
}

/*	Remove the front of the deque.
	Write this function in terms of removeLinkListDeque().

	param: 	d		pointer to the deque
	pre:	d is not null
	pre:	d is not empty
	post:	the front is removed from the deque
*/
void removeFrontListDeque (ListDeque *d)
{
	assert(!isEmptyListDeque(d));  	
	removeLinkListDeque(d, d->head);
}

/* Remove the back of the deque.
	Write this function in terms of removeLinkListDeque().

	param: 	d		pointer to the deque
	pre:	d is not null and q is not empty
	post:	the back is removed from the deque
*/
void removeBackListDeque(ListDeque *d)
{
	removeLinkListDeque(d, d->tail);	
}

/* ************************************************************************
	Bag Interface
************************************************************************ */
/*	Returns whether or not the given value is stored in the deque

	param:	d		pointer to the deque
	param:	val		value that we are looking for in the deque
	ret:	1 if val is contained in d, 0 otherwise
*/
DLink* containsListDeque(ListDeque* d, TYPE val)
{
	DLink* lnk = d->head;
	while(lnk != NULL)
	{
		if(EQ(val, lnk->value))
			return lnk;
		lnk = lnk->next;
	}
	return NULL;
}

/* Removes the first occurrence of the given value from the list.

	param:	d		pointer to the deque
	param:	val		value that we are looking for in the deque
	post:	first occurrence of val is removed from the list
*/
void removeListDeque(ListDeque* q, TYPE val)
{
	DLink* lnk = q->head;
	while(lnk != NULL)
	{
		if(EQ(val, lnk->value))
			lnk = removeLinkListDeque(q, lnk);
		else
			lnk = lnk->next;
	}
}

/* Reverse the deque.  Note that careful swapping of the pointers inside each link
	(next and prev) will cause a reverse, provided head and tail are updated properly.

    param:  d       pointer to the deque
    pre:    d is not null
    post:   the deque is reversed
*/
void reverseListDeque(ListDeque *q)
{
	DLink *realNext, *temp, *current = q->head;
	assert(!isEmptyListDeque(q));
    while(current != NULL)
	{
        realNext = current->next;

        /* swap prev and next of the current link */
        temp = current->prev;
        current->prev = realNext;
        current->next = temp;
		
		current = realNext;
	}

	/* swap the head and the tail */
	temp = q->head;
	q->head = q->tail;
	q->tail = temp;
}

/*	Print the links in the deque from front to back

	param: 	d		pointer to the deque
	pre:	d is not null
	post: 	the links in the deque are printed from front to back
*/
void printListDeque(ListDeque *q)
{
	DLink* lnk = q->head;
	printf("Size = %d [ ", q->size);
	while (lnk != NULL)
	{
		printf("%c, ", lnk->value->label);
		lnk = lnk->next;
	}
	printf("]\n");
}
