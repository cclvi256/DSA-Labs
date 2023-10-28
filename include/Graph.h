struct Graph
{
	/* Fields */

	int order;
	int* adjMat;

	/* Constructors */

	Graph();
	Graph(int order);

	/* Functions */
	
	Graph RmEdges();
	Graph Prim();
	Graph Kruskal();
};