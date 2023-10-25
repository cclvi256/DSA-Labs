#include "main.h"

int main(int argc, char** argv)
{
	// Graph constructing
	Graph g;
	g.Print();

	// Converting  adjacency list and adjacency matrix each other.
	Graph g1(g.order, g.adjList);
	Graph g2(g.order, g.adjMat);
	g1.Print();
	g2.Print();

	return 0;
}
