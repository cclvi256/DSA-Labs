#include "Graph.h"

#include <iostream>
#include <string>
#include <cctype>

Graph::Graph()
{
	std::cout << "Please enter the order of your graph: ";
	int order;
	std::cin >> order;

	this->order = order;

	// Avoiding unexcepted visit to empty graphs.
	if (order == 0)
	{
		this->adjList = nullptr;
		this->adjMat = nullptr;
		this->visited = nullptr;
	}

	// Allocating memory and initialise.
	else
	{
		this->visited = new bool[order];
		this->adjList = new VNode[order];
		this->adjMat = new int[order * order];

		for (int i = 0; i < order; i++)
		{
			this->adjList[i].sn = i;
			this->adjList[i].next = nullptr;
		}

		for (int i = 0; i < order * order; i++)
		{
			this->adjMat[i] = 0;
		}

		this->Reset();
	}

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

		// Add an edge into adjacency list and adjacency matrix.
		this->adjMat[vertex1 * this->order + vertex2] = 1;
		this->adjMat[vertex2 * this->order + vertex1] = 1;
		this->adjList[vertex1].next = new VNode(vertex2, this->adjList[vertex1].next);
		this->adjList[vertex2].next = new VNode(vertex1, this->adjList[vertex2].next);

		// Aftercare, avoiding unexpected user input.
		while (isspace(std::cin.peek()))
		{
			std::cin.get();
		}

		if (std::cin.peek() == ',')
		{
			std::cin.get();
		}
		else if (std::cin.peek() != '#')
		{
			std::cout << "Invalid input, Please check your input." << std::endl;
		}
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

void Graph::Reset()
{
	for (int i = 0; i < this->order; i++)
	{
		this->visited[i] = false;
	}
}

VNode::VNode()
{
}

VNode::VNode(int sn)
{
	this->sn = sn;
	this->next = nullptr;
}

VNode::VNode(int sn, VNode* next)
{
	this->sn = sn;
	this->next = next;
}
