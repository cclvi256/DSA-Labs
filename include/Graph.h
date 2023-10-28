#include <iostream>
#include <cctype>
#define INFINITY 65536

struct Graph
{
	/* Fields */

	int order;
	int* adjMat;

	/* Constructors */

	Graph();
	Graph(int order);

	/* Functions */
	
	Graph Prim(int start);
	Graph Kruskal();

	/* Destructors */
	virtual ~Graph();
};