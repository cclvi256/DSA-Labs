#include "Graph.h"

#include <iostream>
#include <string>

Graph::Graph()
{
	std::cout << "Please enter the order of your graph: ";
	int order;
	std::cin >> order;

	this->order = order;
	this->visited = new bool[order];
	this->adjList = new VNode[order];
	this->adjMat = new int[order * order];

	// TODO: Initialise 3 arrays.

	std::cout << "Please enter each edges of your graph. ";
	std::cout << std::endl;
	std::cout << "Use commas to split edges, and end with a '#'. ";
	std::cout << std::endl;
	std::cout << "Example: 1 3, 4 6, 2 3, 3 6#";
	std::cout << std::endl;

	while (std::cin.peek() != '#')
	{
		int vertex1, vertex2;
		std::cin >> vertex1 >> vertex2;

		// TODO: Add an edge in both adjacency list and adjacency matrix.
	}
}

Graph::Graph(int order)
{
}

Graph::Graph(int order, int* adjMat)
{
}

Graph::Graph(VNode* adjList)
{
}

Graph::Graph(int order, VNode* adjList)
{
}
