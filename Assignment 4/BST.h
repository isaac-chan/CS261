#ifndef BINARY_SEARCH_TREE_INCLUDED
#define BINARY_SEARCH_TREE_INCLUDED 1
#include "type.h"

struct Node {
	TYPE val;
	struct Node* left;
	struct Node* right;
};
typedef struct Node Node;

struct BinarySearchTree {
	Node* root;
	int size;
};
typedef struct BinarySearchTree BinarySearchTree;
typedef BinarySearchTree BST;

/* Basic Operations */
void initBST(BST* tree);
BST* newBST();

void freeBST(BST* tree);
void deleteBST(BST* tree);

int heightBST(BST* tree);

void printBST(BST* tree);

/* Bag Interface */
void addBST(BST* tree, TYPE val);
void removeBST(BST* tree, TYPE val);
int containsBST(BST* tree, TYPE val);

# endif
