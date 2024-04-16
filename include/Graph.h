#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <cstdlib>
#include "UFDS.h"
#define INFINITY 65536

struct Graph
{
	/* Fields */

	int order;
	int* adjMat;

	/* Constructors */

	Graph();
	Graph(std::string fileName);
	Graph(int order);

	/* Functions */
	
	Graph Prim(int start);
	Graph Kruskal();
	void Print();
};
