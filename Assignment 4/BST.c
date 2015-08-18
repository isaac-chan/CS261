/*Program 4: written by Isaac Chan and Xilun Guo */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "assert.h"
#include "type.h"
#include "BST.h"

/* ************************************************************************
	Helper Functions
 ************************************************************************ */
/* This function allocates a node on the heap for use in the tree datastructure.
 
	param: val		value to store in the newly created node
	post:	the newly created node is allocated, initialized, and returned.
	ret: a Node, allocated on the heap, storing the argument value
 */
Node* _createNode(TYPE val)
{
    /* FIXME you will write this function */
    Node* newnode = (Node*) malloc(sizeof(Node));
   	assert(newnode != 0);
    newnode->right = NULL;
    newnode->left = NULL;
    
    newnode->val = val;
    return newnode;
}

/* This function compares two tasks.  Note that this function does NOT use
	TYPE.  This is because if we change TYPE, we will get a compile error on the
	_compare function, making us remember to write a new one for that type.
	
	param: left, right		Items to be compared
	ret:	-1 if left < right
 1 if left > right
 0 otherwise
 */
int _compare(Task left, Task right)
{
    if(left.priority < right.priority)
        return -1;
    else if(left.priority > right.priority)
        return 1;
    return 0;
}

/* ************************************************************************
	Binary Search Tree Basic Functions
 ************************************************************************ */
/* This function can be used to initialize the data fields in the tree.
	
	param: tree		The tree to be initialized
	post: tree's datafields are all initialized.
 */
void initBST(BST* tree)
{
    tree->root = NULL;
    tree->size = 0;
}

/* Allocate and initialize a binary search tree.
 
	post: the newly created tree is allocated, initialized, and returned
	ret:	a newly created tree, allocated on the heap.
 */
BST* newBST()
{
    BST* tree = (BST*)malloc(sizeof(BST));
    assert(tree);
    
    initBST(tree);
    return tree;
}

/* Helper function used to free a subtree of the BST rooted at a particular node.
 
	param: root		Root of the subtree to be freed
	pre:	root is in the tree
	post:	all memory in the underlying tree structure is freed
 */
void _freeSubTreeBST(Node* root)
{
    if(!root)
        return;
    _freeSubTreeBST(root->left);
    _freeSubTreeBST(root->right);
    free(root);
}

/* This function will free all the nodes in the argument tree.  To be used with init.
 
	param: tree		Tree to have its nodes freed
	post:	tree has had its nodes freed
	post:	tree has had its datafields cleared
 */
void freeBST(BST* tree)
{
    _freeSubTreeBST(tree->root);
    tree->size = 0;
    tree->root = 0;
}

/* This function will free all the nodes in the argument tree IN ADDITION to freeing the
	datastructure pointer provided as well.
	
	param: tree		Tree to have its nodes freed and be freed
	post:	tree has had its nodes freed
	post:	tree has had its datafields cleared
	post:	tree has been freed
 */
void deleteBST(BST* tree)
{
    freeBST(tree);
    free(tree);
}

/* Helper function used to compute the height of a subtree rooted at a particular node.
	
	param: root		Root of the subtree to compute the height of
	ret:	The height of the subtree rooted at root
 */
int _heightOfSubTree(Node* root)
{
    /* FIXME you will write this function */
    if(!root)
        return -1;
    int leftheight = _heightOfSubTree(root->left) + 1;
    
    int rightheight = _heightOfSubTree(root->right) + 1;
    
    if(leftheight > rightheight)
        return leftheight;
    return rightheight;
    
}

/* This function computes the height of an argument BST
 
	param:	tree	BST to have its height computed
	ret:	the height of the argument tree
 */
int heightBST(BST* tree)
{
    return _heightOfSubTree(tree->root);
}

/* Helper function which stores a subtree rooted at root into the argument array.
 
	param: root		Root of the subtree to be stored in the array
	param: index	Index where the root should reside in the argument array
	param: levelOrder	Array where the tree is to be stored
	post: levelOrder has the subtree rooted at root stored inside it.
 */
void _storeInArray(Node* root, int index, Node** levelOrder)
{
    if (!root)
        return;
    
    levelOrder[index] = root;
    _storeInArray(root->left, 2*index + 1, levelOrder);
    _storeInArray(root->right, 2*index + 2, levelOrder);
}

/* Prints a BST to the console using a nice formatting.
 
	param: tree		Tree to be printed to the console
	post:	tree has been printed to the console
	
	IMPORTANT NOTE! some input to this function pay cause exponential memory to be consumed
	as a result of the tree in array storage scheme.
 */
void printBST(BST* tree)
{
    int height = heightBST(tree);
    int levelOrderSize = pow(2, height+1)-1;
    int i, j, depth, lastDepth;
    int leftSpace;
    
    Node** levelOrder = (Node**)malloc(levelOrderSize*sizeof(Node*));
    for(i = 0; i < levelOrderSize; ++i)
        levelOrder[i] = NULL;
    _storeInArray(tree->root, 0, levelOrder);
    
    printf("***[ Size: %d Height: %d ]", tree->size, heightBST(tree));
    
    lastDepth = -1;
    leftSpace = 0;
    for(i = 0; i <= height; ++i)
        leftSpace = leftSpace * 2 + 1;
    for(i = 0; i < levelOrderSize; ++i)
    {
        depth = log(i+1)/log(2);
        if(lastDepth != depth)
        {
            leftSpace /= 2;
            printf("\n");
            for(j = 0; j < leftSpace; ++j)
                printf("  ");
        }
        else
            for(j = 0; j < leftSpace * 2 + 1; ++j)
                printf("  ");
        
        if(levelOrder[i])
            printf("%d", levelOrder[i]->val.priority);
        else
            printf("??");
        lastDepth = depth;
    }
    printf("\n");
    free(levelOrder);
}

/* ************************************************************************
	Bag Interface Functions (and Helpers)
 ************************************************************************ */
/* Add a node to the subtree rooted at the argument node
 
	param: curr		Root of the subtree where the node should be added.
	param: val		value to store in the new node when it is added
	post: a node is allocated storing val, which has been added to the tree
	ret: the node where we currently reside in the tree.  Note that
 this function is recursive, so as the function returns, we will
 connect the tree together.
 */
Node* _addNodeToSubtree(Node* curr, TYPE val)
{
    /* FIXME you will write this function */
    if(curr == NULL)
        return _createNode(val);
    else if (_compare(curr->val, val) == 1){
        curr->left = _addNodeToSubtree(curr->left, val);
    }
    else if(_compare(curr->val, val) == -1){
        curr->right = _addNodeToSubtree(curr->right, val);
    }
    return curr;
}

/* Adds a node to the BST
 
	param: tree		BST to have a node added to it
	param: val		value to store in the new node
	post: a node, allocated on the heap, has been added to the BST storing val
 */
void addBST(BST* tree, TYPE val)
{
    tree->root = _addNodeToSubtree(tree->root, val);
    tree->size++;
}

/* Helper function which can be used to determine if a particular value is
	present in the subtree rooted at the argument node.
	
	param: curr		Root of the subtree to search for the value
	param: val		value for which to search the the subtree
	ret: 1 if the value is in the subtree, 0 otherwise
 */
int _containsSubTree(Node* curr, TYPE val)
{
    /* FIXME you will write this function */
    if(!curr)
        return 0;
    
    else if(_compare(curr->val, val) == 1)
        return _containsSubTree(curr->left, val);
    
    else if(_compare(curr->val, val) == -1)
        return _containsSubTree(curr->right, val);
    
    else if(_compare(curr->val, val) == 0)
        return 1;
    return 0;
}

/* This function can be used to determine if a particular value is present in the BST.
 
	param: tree		BST to search for the argument value
	param: val		Value to search for in the BST
	ret: 1 if the value is in the BST, 0 otherwise
 */
int containsBST(BST* tree, TYPE val)
{
    return _containsSubTree(tree->root, val);
}

/* This function is used to remove and deallocate the leftmost descendent of the argument node
 
	param: curr		The node whose leftmost descendent we wish to find
	param: parent	curr's parent, included to make the operation easier to perform
	param: origAncestor		the node on which the original leftmost call was given
	post:	the leftmost descendent of curr is removed from the tree and freed
	ret:	the value stored in the leftmost descendent of curr
 */
TYPE _removeLeftMost(Node* curr, Node* parent, Node* origAncestor)
{
    /* FIXME you will write this function */
    TYPE removeThisVar;
    if(curr->left == NULL){
        removeThisVar = curr->val;
        if(parent == origAncestor)
            parent->right = curr->right;
        else
            parent->left = curr->right;
        free(curr);
        return removeThisVar;
    }
    else
        return _removeLeftMost(curr->left, curr, origAncestor);
}

/* This function is used to remove a node from a subtree of the BST
 
	param: curr		The root of the subtree we are currently examining for the value
	param: val		The value to be removed from the subtree
	post: a node containing val has been removed from the tree and freed
	ret: the node where we currently reside in the tree.
 Note that this function uses recursion to put the tree back together as stack
 frames are removed.
 */
Node* _removeNodeFromSubtree(Node* curr, TYPE val)
{
    /* FIXME you will write this function */
    if(_compare(val, curr->val) == -1)
        curr->left = _removeNodeFromSubtree(curr->left, val);
    else if(_compare(val, curr->val) == 1)
        curr->right = _removeNodeFromSubtree(curr->right, val);
    else{
        if(curr->right == NULL){
            struct Node* temp = curr->left;
            free(curr);
            return temp;
        }
        else
            curr->val = _removeLeftMost(curr->right, curr, curr);
        
    }
        
    return curr;
}

/* This function is used to remove a node from the BST, if present.
 
	param: tree		The tree to search for the argument value
	param: val		the value to be removed from the tree.
	post: if val is present in any of the nodes, it has been removed.
 if not, nothing has happened
 */
void removeBST(BST* tree, TYPE val)
{
    if(containsBST(tree, val))
    {
        tree->root = _removeNodeFromSubtree(tree->root, val);
        tree->size--;
    }
}