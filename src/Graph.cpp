#include "Graph.h"

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>

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
}

Graph::Graph(int order, int* adjMat)
{
	// Check if the adjacency matrix argument legal.
	for (int i = 0; i < order; i++)
	{
		for (int j = i; j < order; j++)
		{
			if (i == j && adjMat[i * order + j] != 0)
			{
				std::cout << "All items on the diagonal must be 0!" << std::endl;
				exit(1);
			}

			if (adjMat[i * order + j] != adjMat[j * order + i])
			{
				std::cout << "This matrix is not symmetrical!" << std::endl;
				exit(1);
			}
		}
	}

	// Direct the adjMat field.
	this->adjMat = adjMat;

	// Fill the adjList field.
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			this->adjList[i].next = new VNode(j, this->adjList[i].next);
		}
	}
}

Graph::Graph(int order, VNode* adjList)
{
	// Direct the adjList field.
	this->adjList = adjList;

	// Fill the adjMat field.
	for (int i = 0; i < order; i++)
	{
		VNode* copy = this->adjList[i].next;
		while (copy != nullptr)
		{
			copy = copy->next;
			// Unsymmetrical input, in avoid of illegal adjacency list.
			this->adjMat[i * order + copy->sn] = 1;
		}
	}

	// Check weather the adjacency list legal.
	// Considering the complexity of checking adjacency list, 
	// it maybe better to check the adjacency matrix from it.
	for (int i = 0; i < order; i++)
	{
		for (int j = i; j < order; j++)
		{
			if (i == j && this->adjMat[i * order + j] != 0)
			{
				std::cout << "All items on the diagonal must be 0!" << std::endl;
				exit(1);
			}

			if (this->adjMat[i * order + j] != this->adjMat[j * order + i])
			{
				std::cout << "This matrix is not symmetrical!" << std::endl;
				exit(1);
			}
		}
	}
}

void Graph::Reset()
{
	for (int i = 0; i < this->order; i++)
	{
		this->visited[i] = false;
	}
}

// Maybe this method is no longer necessary.
// void Graph::Init(char mode)
// {
// }

int* Graph::Degree()
{
	int* rv = new int[this->order];

	for (int i = 0; i < order; i++)
	{
		rv[i] = 0;
		VNode* copy = this->adjList[i].next;
		while (copy != nullptr)
		{
			copy = copy->next;
			rv[i]++;
		}
	}

	return rv;
}

VNode::VNode()
{
	// Avoiding of wild pointer.
	this->next = nullptr;
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
