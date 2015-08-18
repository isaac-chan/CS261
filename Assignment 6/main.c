#include <stdio.h>
#include "graph.h"

int main () 
{
	/* change this number to generate different graphs */
	int graphTestNumber = 1; /* permissible values are 1-5 */
	/* switch this to 0 to use BFS */
	int useDFS = 1;
	
	Graph g;
	
	/* set up the graph */
	if(graphTestNumber == 1)
		createGraph1(&g);
	else if(graphTestNumber == 2)
		createGraph2(&g);
	else if(graphTestNumber == 3)
		createGraph3(&g);
	else if(graphTestNumber == 4)
		createGraph4(&g);
	else if(graphTestNumber == 5)
		createGraph5(&g);
	else
	{
		printf("Invalid test number... Quitting");
		return 1;
	}
	
	
	printGraph(&g);
	
	computeAdjacencyMatrix(&g);
	
	computeReachabilityMatrix(&g, useDFS);
	
	return 0;
}