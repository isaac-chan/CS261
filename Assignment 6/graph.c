/*Assignment 6, written by Isaac Chan and Xilun Guo*/

#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

#include "ListDeque.h"

/**************************************************************
	Creating various graphs
 **************************************************************/
void createGraph1(Graph* g)
{
    g->numVertices = 3;
    setupVertices(g);
    
    g->numEdges = 3;
    setupEdge(g, &g->vertexSet[0], &g->vertexSet[1]);
    setupEdge(g, &g->vertexSet[1], &g->vertexSet[2]);
    setupEdge(g, &g->vertexSet[2], &g->vertexSet[0]);
}

void createGraph2(Graph* g)
{
    g->numVertices = 4;
    setupVertices(g);
    
    g->numEdges = 2;
    setupEdge(g, &g->vertexSet[0], &g->vertexSet[2]);
    setupEdge(g, &g->vertexSet[1], &g->vertexSet[3]);
}

void createGraph3(Graph* g)
{
    int i;
    int numbers[20] =  {6, 14, 6, 9, 1, 2, 5, 12, 6, 1, 12, 14, 14, 10, 2, 12, 6, 7, 8, 14 };
    
    g->numVertices = 15;
    setupVertices(g);
    
    g->numEdges = 10;
    for(i = 0; i < g->numEdges; ++i)
        setupEdge(g, &g->vertexSet[numbers[i*2]], &g->vertexSet[numbers[i*2+1]]);
}

void createGraph4(Graph* g)
{
    int i;
    int numbers[56] = {	3, 13, 17, 25, 18, 9, 7, 1, 3, 7, 25, 10, 6, 18, 4,
        7, 19, 14, 11, 19, 4, 16, 23, 14, 24, 6, 22, 8, 21,
        7, 12, 7, 13, 16, 22, 4, 15, 16, 0, 19, 15, 8, 25,
        23, 11, 3, 24, 1, 10, 18, 10, 16, 1, 19, 15, 8};
    
    g->numVertices = 26;
    setupVertices(g);
    
    g->numEdges = 28;
    for(i = 0; i < g->numEdges; ++i)
        setupEdge(g, &g->vertexSet[numbers[i*2]], &g->vertexSet[numbers[i*2+1]]);
}

void createGraph5(Graph* g)
{
    int i, j;
    
    g->numVertices = 20;
    setupVertices(g);
    
    g->numEdges = 400;
    for(i = 0; i < g->numVertices; ++i)
        for(j = i + 1; j < g->numVertices; ++j)
            setupEdge(g, &g->vertexSet[i], &g->vertexSet[j]);
}

/**************************************************************
	Graph functions
 **************************************************************/

/* Initializes all information for the vertices in the graph
 * param: g		Graph whose vertices will be initialized
 * pre: numVertices has been initialized
 */
void setupVertices(Graph* g)
{
    int i;
    g->vertexSet = (Vertex*) malloc(g->numVertices * sizeof(Vertex));
    for(i = 0; i < g->numVertices; ++i)
    {
        g->vertexSet[i].label = 'A' + i;
        g->vertexSet[i].isVisited = 0;
        g->vertexSet[i].neighbors = (Vertex**)malloc(sizeof(Vertex*));
        g->vertexSet[i].numNeighbors = 0;
    }
}

/* Creates all the links necessary to form an edge between the two argument vertices.
 * param: g		Graph in which the vertices reside
 * param: first	Vertex from which the edge will originate
 * param: second	Vertex at which the edge terminates
 * post: all links necessary to form an edge between first and second have been completed.
 */
void setupEdge(Graph* g, Vertex* first, Vertex* second)
{
    first->numNeighbors++;
    second->numNeighbors++;
    first->neighbors = (Vertex**)realloc(first->neighbors, first->numNeighbors * sizeof(Vertex*));
    second->neighbors = (Vertex**)realloc(second->neighbors, second->numNeighbors * sizeof(Vertex*));
    
    first->neighbors[first->numNeighbors - 1] = second;
    second->neighbors[second->numNeighbors - 1] = first;
}

/* This function prints the graph in adjancency list format.
 * param: g		Graph to print
 * post: the graph is printed to the console
 */
void printGraph(Graph* g)
{
    int i, j;
    Vertex* currVert;
    printf("*****\t\t This graph has %d Vertices and %d Edges\n", g->numVertices, g->numEdges);
    
    /* print the vertex set */
    for(i = 0; i < g->numVertices; ++i)
    {
        currVert = &g->vertexSet[i];
        printf("%c: ", currVert->label);
        for(j = 0; j < currVert->numNeighbors - 1; ++j)
            printf("%c, ", currVert->neighbors[j]->label);
        if(currVert->numNeighbors > 0)
            printf("%c\n", currVert->neighbors[j]->label);
        else printf("\n");
    }
}

/* This function clears all the search flags in the graph
 * param: g		Graph to have its flags cleared
 * post: All vertices in the graph should have their search flags turned off
 */
void clearVisited(Graph* g)
{
    int i;
    for(i = 0; i < g->numVertices; ++i)
        g->vertexSet[i].isVisited = 0;
}

/* these two functions provide a recursive version of the depth first search.
 * feel free to use this to check your answers
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int DFSRecursiveHelper(Graph* g, Vertex* currVert, Vertex* destination)
{
    int i;
    
    currVert->isVisited = 1;
    if(currVert == destination)
        return 1;
    for(i = 0; i < currVert->numNeighbors; ++i)
        if(!currVert->neighbors[i]->isVisited)
            if(DFSRecursiveHelper(g, currVert->neighbors[i], destination))
                return 1;
    return 0;
}
int DFSRecursive(Graph* g, Vertex* source, Vertex* destination)
{
    clearVisited(g);
    return DFSRecursiveHelper(g, source, destination);
}

/* This function should return a boolean (encoded as an int) indicating
 * whether or not a path exists between the argument vertices.
 * You may want to start by clearing the visited flags for the whole graph.
 
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int DFS(Graph* g, Vertex* source, Vertex* destination)
{
    /* FIXME you will write this function */
    struct ListDeque stack;
    initListDeque(&stack);
    clearVisited(g);
    addFrontListDeque(&stack, source);
    Vertex *curr = source;
    source->isVisited = 1;
    while (!isEmptyListDeque(&stack)){
        curr = frontListDeque(&stack);
        removeFrontListDeque(&stack);
        if (curr == destination)
            return 1;
        int i;
        for (i = 0; i < curr->numNeighbors; ++i){
            if (!curr->neighbors[i]->isVisited ){
                curr->neighbors[i]->isVisited = 1;
                addFrontListDeque(&stack, curr->neighbors[i]);
            }
        }
            
    }
    return 0;
}

/* This function should return a boolean (encoded as an int) indicating
 * whether or not a path exists between the argument vertices.
 * param: g			Graph to perform the search in
 * param: source	Vertex to originate the search from
 * param: destination Vertex to stop the search from (if it is found)
 * ret: boolean indicating whether or not a path exists
 */
int BFS(Graph* g, Vertex* source, Vertex* destination)
{
    /* FIXME you will write this function */
    struct ListDeque Deque;
    initListDeque(&Deque);
    clearVisited(g);
    addFrontListDeque(&Deque, source);
    Vertex *curr = source;
    source->isVisited = 1;
    while (!isEmptyListDeque(&Deque)){
        curr = backListDeque(&Deque);
        removeBackListDeque(&Deque);
        if (curr == destination)
            return 1;
        int i;
        for (i = 0; i < curr->numNeighbors; ++i){
            if (!curr->neighbors[i]->isVisited ){
                curr->neighbors[i]->isVisited = 1;
                addFrontListDeque(&Deque, curr->neighbors[i]);
            }
        }
        
    }
    return 0;
}

/* This function prints a matrix to the console.
	The matrix is assumed to be NxN, where
	N is the number of vertices in the graph.
	
	param: g		Graph associated with the argument matrix
	param: matrix	square matrix to print to the console
	post: the matrix is printed to the console with some labelling
 */
void _printMatrix(Graph* g, int** matrix)
{
    int i, j;
    /* print the matrix */
    printf("    ");
    for(i = 0; i < g->numVertices; ++i)
        printf("%c ", g->vertexSet[i].label);
    printf("\n   ");
    for(i = 0; i < g->numVertices; ++i)
        printf("--");
    printf("\n");
    for(i = 0; i < g->numVertices; ++i)
    {
        printf("%c | ", g->vertexSet[i].label);
        for(j = 0; j < g->numVertices; ++j) /* we could just do the upper diagonal of the matrix */
            if(matrix[i][j])
                printf("%d ", matrix[i][j]);
            else
                printf("0 ");
        printf("\n");
    }
}

/* This function computes an adjacency matrix for the given graph.
	A reachability matrix is an NxN binary matrix where N = numVertices
	and matrix[i][j] = 1 if an edge exists from vertex i to vertex j,
 and 0 otherwise.
 
	Note that since we are using undirected graphs,
 matrix[i][j] == matrix[j][i].
	
	param:	g			Graph within which to construct the adjacency mat
	post:	the matrix is printed to the console using the
 _printMatrix function.
 */
void computeAdjacencyMatrix(Graph* g)
{
    /* FIXME you will write this function */
    /* allocated two d array, init all 0.  outloop 0 - numvetic-1, inloop 0 - numneighbor
     edge exists put 1.*/
    Vertex* v;
    int** matrix = (int**)calloc(g->numVertices, sizeof(int*));
    int i, j, index;
    for(i = 0; i < g->numVertices; ++i){
        matrix[i] = (int*)calloc(g->numVertices, sizeof(int));
    }
    for(i = 0; i < g->numVertices; ++i){
        v = &g->vertexSet[i];
        for(j = 0; j < v->numNeighbors; ++j){
            index = v->neighbors[j]->label - 'A';
            matrix[i][index] = 1;
            matrix[index][i] = 1;
        }
    }
    _printMatrix(g, matrix);
}

/* This function computes a reachability matrix for the given graph.
	A reachability matrix is an NxN binary matrix where N = numVertices
	and matrix[i][j] = 1 if a path exists from vertex i to vertex j,
 and 0 otherwise.
 
	Note that since we are using undirected graphs,
 matrix[i][j] == matrix[j][i].
	
	param:	g			Graph within which to perform DFS/BFS
	param:	useDFS		if 1, then use DFS to compute the matrix
 if 0, then use BFS to compute the matrix
	post:	the matrix is printed to the console using the
 _printMatrix function.
 */
void computeReachabilityMatrix(Graph* g, int useDFS)
{
    /* FIXME you will write this function */
    /* outloop and inloop are 0 - numvetic-1, 
     path exists put 1*/
    int** matrix = (int**)calloc(g->numVertices, sizeof(int*));
    int i, j;
    for(i = 0; i < g->numVertices; ++i){
        matrix[i] = (int*)calloc(g->numVertices, sizeof(int));
    }
    for (i = 0; i < g->numVertices; ++i) {
        for (j = 0; j < g->numVertices; j++)
            if (useDFS)
                matrix[i][j] = DFS(g, &g->vertexSet[i], &g->vertexSet[j]);
            else
                matrix[i][j] = BFS(g, &g->vertexSet[i], &g->vertexSet[j]);
        
    }
    _printMatrix(g, matrix);
    
    

}