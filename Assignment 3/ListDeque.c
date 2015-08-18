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
    d->head = NULL;
    d->tail = NULL;
}

/*	De-allocate all links of the deque.
	Write this function in terms of a remove function, such as removeBack.
 
	param: 	d		pointer to the deque
	pre:	d is not null
	post:	All links are de-allocated
 */
void freeListDeque(ListDeque* d)
{
    /*FIXME you will write this function */
    DLink* lnk;
    lnk = d->head;
    while(lnk != NULL)
    {
        free(lnk);
        lnk = lnk->next;
    }
}

/* Check whether the deque is empty.
 
	param: 	d		pointer to the deque
	pre:	d is not null
	ret: 	1 if the deque is empty. Otherwise, 0.
 */
int isEmptyListDeque(ListDeque *d) {
    
    /*FIXME you will write this function */
    if(d->size == 0)
        return 1;
    return 0;
    
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
    assert(d != NULL);
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
    /*FIXME you will write this function */
    /*TYPE var;
     return var;*/
    assert(d != NULL);
    assert(!isEmptyListDeque(d));
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
    /*FIXME you will write this function */
    assert(d != NULL);
    if (d->head == NULL){
        newLnk->prev = NULL;
        newLnk->next = NULL;
        d->head = newLnk;
        d->tail = newLnk;
    }
    else if (d->tail == addAfter){
        newLnk->prev = addAfter;
        newLnk->next = NULL;
        addAfter->next = newLnk;
        d->tail = newLnk;
    }
    else{
        newLnk->prev = addAfter;
        newLnk->next = addAfter->next;
        addAfter->next->prev = newLnk;
        addAfter->next = newLnk;
    }
    
    d->size++;
}

/* Adds a link BEFORE another link.
	Write your other add functions in terms of addAfter and addBefore when possible.
 
	param: 	d			pointer to the deque
	param: 	addBefore	pointer to the existing link in the deque
	param: 	newLnk		pointer to the new link to add before the existing link
	pre:	d is not null
	pre: 	newLnk has been properly initialized
	pre:	addBefore is in the deque if it is not a NULL pointer
	post:	newLnk is added into the deque BEFORE the existing link
 */
void addLinkBeforeListDeque(ListDeque* d, DLink* addBefore, DLink* newLnk)
{
    /*FIXME you will write this function */
    assert(d != NULL);
    if (d->head == NULL){
        newLnk->prev = NULL;
        newLnk->next = NULL;
        d->head = newLnk;
        d->tail = newLnk;
    }
    else if (d->head == addBefore){
        newLnk->prev = NULL;
        newLnk->next = addBefore;
        d->head = newLnk;
        addBefore->prev = newLnk;
    }
    else{
        newLnk->prev = addBefore->prev;
        newLnk->next = addBefore;
        addBefore->prev->next = newLnk;
        addBefore->prev = newLnk;
    }
    d->size++;
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
    /*FIXME you will write this function */
    assert(d != NULL);
    assert(!isEmptyListDeque(d));
    assert(lnk != NULL);
    if (d->head == lnk && d->tail == lnk){
        free(lnk);
        d->head = NULL;
        d->tail = NULL;
        d->size--;
        return lnk;
    }
    else if (d->tail == lnk){
        free(lnk);
        d->tail = lnk->prev;
        lnk->prev->next = NULL;
        d->size--;
        return lnk;
    }
    else if (d->head == lnk){
        free(lnk);
        d->head = lnk->next;
        lnk->next->prev = NULL;
        d->size--;
        return lnk;
    }
    else{
        free(lnk);
        lnk->prev->next = lnk->next;
        lnk->next->prev = lnk->prev;
        d->size--;
        return lnk;
    }
    return NULL;
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
    /*FIXME you will write this function */
    DLink* newLnk = (DLink*) malloc(sizeof(DLink));
    assert(d != NULL);
    newLnk->value = val;
    addLinkAfterListDeque(d, d->tail, newLnk);
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
    /*FIXME you will write this function */
    DLink* newLnk = (DLink*) malloc(sizeof(DLink));
    assert(d != NULL);
    newLnk->value = val;
    addLinkBeforeListDeque(d, d->head, newLnk);
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
    /*FIXME you will write this function */
    assert(d != NULL);
    assert(!isEmptyListDeque(d));
    removeLinkListDeque(d,d->head);
}

/* Remove the back of the deque.
	Write this function in terms of removeLinkListDeque().
 
	param: 	d		pointer to the deque
	pre:	d is not null and q is not empty
	post:	the back is removed from the deque
 */
void removeBackListDeque(ListDeque *d)
{
    /*FIXME you will write this function */
    assert(d != NULL);
    assert(!isEmptyListDeque(d));
    removeLinkListDeque(d,d->tail);
}

/* ************************************************************************
	Bag Interface
 ************************************************************************ */
/*	Returns whether or not the given value is stored in the deque
 
	param:	d		pointer to the deque
	param:	val		value that we are looking for in the deque
	ret:	1 if val is contained in d, 0 otherwise
 */

int containsListDeque(ListDeque* d, TYPE val)
{
    /*FIXME you will write this function*/
    struct DLink *k;
    assert(d != 0);
    assert(!isEmptyListDeque(d));
    k = d->head;
    while(k != d->tail){
        if(k->value==val)
            return 1;
        k = k->next;
    }
    return 0;
}


/* Removes the first occurrence of the given value from the list.
 
	param:	d		pointer to the deque
	param:	val		value that we are looking for in the deque
	post:	first occurrence of val is removed from the list
 */
void removeListDeque(ListDeque* q, TYPE val)
{
    /*FIXME you will write this function */
    assert(q != NULL);
    assert(!isEmptyListDeque(q));
    DLink *k = q->head->next;
    assert(k != 0);
    while(k != q->tail)
    {
        
        if(k->value == val)
        {
            removeLinkListDeque(q,k);
            break;
        }
        k = k->next;
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
    /*FIXME you will write this function */
    DLink *temp1 = q->head;
    DLink *temp2 = temp1->next;
    q->head = q->tail;
    q->tail = temp1;
    while (temp1 != NULL){
        DLink *t = temp1->prev;
        temp1->prev = temp1->next;
        temp1->next = t;
        temp1 = temp2;
        if (temp2)
            temp2 = temp2->next;
    }
}

/*	Print the links in the deque from front to back
 
	param: 	d		pointer to the deque
	pre:	d is not null
	post: 	the links in the deque are printed from front to back
 */
void printListDeque(ListDeque *q)
{
    DLink* lnk;
    lnk = q->head;
    printf("Size = %d [ ", q->size);
    while(lnk != NULL)
    {
        printf("%c ", lnk->value);
        lnk = lnk->next;
    }
    printf("]\n");
}