#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "BST.h"

int main (int argc, const char * argv[])
{
    int i;
    int ary[20] = { 54, 78, 19, 86, 53, 44, 58, 79, 15, 11, 10, 43, 57, 95, 64, 49, 77, 17, 55, 84};
    
    BST* t = newBST();
    
	Task firstTask, secondTask, thirdTask, fourthTask;
    firstTask.name = "blarg";
    firstTask.priority = 11;
    
    secondTask.name = "foo";
    secondTask.priority = 34;
    
    thirdTask.name = "bar";
    thirdTask.priority = 23;
    
    fourthTask.name = "scraz";
    fourthTask.priority = 37;

    addBST(t, thirdTask);	printBST(t);
    printf("contains(34) = %d\n", containsBST(t, secondTask));
    addBST(t, secondTask);	printBST(t);
    printf("contains(34) = %d\n", containsBST(t, secondTask));
    addBST(t, firstTask);	printBST(t);
    printf("contains(37) = %d\n", containsBST(t, fourthTask));
    addBST(t, fourthTask);	printBST(t);
    printf("contains(37) = %d\n", containsBST(t, fourthTask));
    removeBST(t, thirdTask); printBST(t);
    removeBST(t, secondTask); printBST(t);
    removeBST(t, fourthTask); printBST(t);
    removeBST(t, firstTask); printBST(t);
    
    for(i = 0; i < 20; ++i)
    {
        firstTask.priority = ary[i];
        addBST(t, firstTask);
    }
    printBST(t);
    printf("\n");
   
    return 0;
}