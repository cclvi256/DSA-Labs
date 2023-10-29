#include <iostream>
#include <cctype>
#include "UFDS.h"
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