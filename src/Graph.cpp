#include "Graph.h"

#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stack>
#include <queue>

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

		std::cout << "WARNING: You are constructing a zero graph" << std::endl;
	}

	// Allocating memory and initialise.
	else
	{
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

	std::cout << "Graph successfully constructed." << std::endl;
}

Graph::Graph(int order)
{
	this->order = order;

	// Avoiding unexcepted visit to empty graphs.
	if (order == 0)
	{
		this->adjList = nullptr;
		this->adjMat = nullptr;
	}

	// Allocating memory and initialise.
	else
	{
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
	}
}

Graph::Graph(int order, int* adjMat)
{
	this->order = order;

	// Initialise
	this->adjList = new VNode[this->order];
	for (int i = 0; i < this->order; i++)
	{
		this->adjList[i].next = nullptr;
	}

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
			VNode* copy = this->adjList[i].next;
			this->adjList[i].next = new VNode(j, copy);
		}
	}
}

Graph::Graph(int order, VNode* adjList)
{
	this->order = order;

	// Direct the adjList field.
	this->adjList = adjList;

	// Initialise
	this->adjMat = new int[this->order * this->order];
	for (int i = 0; i < this->order * this->order; i++)
	{
		this->adjMat[i] = 0;
	}

	// Fill the adjMat field.
	for (int i = 0; i < order; i++)
	{
		VNode* copy = this->adjList[i].next;
		while (copy != nullptr)
		{
			// Unsymmetrical input, in avoid of illegal adjacency list.
			this->adjMat[i * order + copy->sn] = 1;
			copy = copy->next;
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

Graph::~Graph()
{
}

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

int* Graph::BFS_Numbering(int start, char mode)
{
	std::queue<int> q;

	// Optimise: one bit for a true or false.
	bool* visited = new bool[this->order];
	int* rv = new int[this->order];

	// Initialise array.
	for (int i = 0; i < this->order; i++)
	{
		visited[i] = false;
		rv[i] = 0;
	}

	q.push(start);
	int counter = 0;

	while (!q.empty())
	{
		if (mode = 'm')
		{
			VNode* copy = this->adjList[q.front()].next;
			while (copy != nullptr)
			{
				q.push(copy->sn);
				visited[copy->sn] = true;
				copy = copy->next;
			}
		}
		else if (mode = 'l')
		{
			for (int i = 0; i < this->order; i++)
			{
				int base = this->order * q.front();
				if (base + i == 1)
				{
					q.push(i);
					visited[i] = true;
				}
			}
		}

		counter++;
		rv[q.front()] = counter;
		q.pop();
	}

	return rv;
}

int* Graph::DFS_Numbering(int start, char mode)
{
	std::stack<int> s;

	// Optimise: one bit for a true or false.
	bool* visited = new bool[this->order];
	int* rv = new int[this->order];

	// Initialise array.
	for (int i = 0; i < this->order; i++)
	{
		visited[i] = false;
		rv[i] = 0;
	}

	s.push(start);
	int counter = 0;

	while (!s.empty())
	{
		if (mode = 'm')
		{
			VNode* copy = this->adjList[s.top()].next;
			while (copy != nullptr)
			{
				s.push(copy->sn);
				visited[copy->sn] = true;
				copy = copy->next;
			}
		}
		else if (mode = 'l')
		{
			for (int i = 0; i < this->order; i++)
			{
				int base = this->order * s.top();
				if (base + i == 1)
				{
					s.push(i);
					visited[i] = true;
				}
			}
		}

		counter++;
		rv[s.top()] = counter;
		s.pop();
	}

	return rv;
}

void Graph::DFS_R_Numbering(int start, int* arr, char mode)
{
	bool* visited = new bool[this->order];
	for (int i = 0; i < this->order; i++)
	{
		arr[i] = 0;
		visited[i] = false;
	}

	DFS_R_Numbering(start, arr, visited, mode);
}

void Graph::DFS_R_Numbering(int start, int* arr, bool* visited, char mode)
{


	if (mode = 'm')
	{
		VNode* copy = this->adjList[start].next;
		visited[start] = true;

		while (copy != nullptr)
		{
			if (!visited[copy->sn])
			{
				DFS_R_Numbering(copy->sn, arr, visited, mode);
			}
			copy = copy->next;
		}
	}
	else if (mode = 'l')
	{
		int base = this->order * start;
		visited[start] = true;

		for (int i = 0; i < this->order; i++)
		{
			if (!visited[i])
			{
				DFS_R_Numbering(i, arr, visited, mode);
			}
		}
	}

}

void Graph::Print()
{
	bool first = true;
	std::cout << "V = {";
	for (int i = 0; i < this->order; i++)
	{
		if (first)
		{
			first = false;
		}
		else
		{
			std::cout << ", ";
		}
		std::cout << i;
	}
	std::cout << "};" << std::endl;

	first = true;
	std::cout << "E = {";
	for (int i = 0; i < this->order; i++)
	{
		for (int j = i + 1; j < this->order; j++)
		{
			if (this->adjMat[i * order + j] == 1)
			{
				if (first)
				{
					first = false;
				}
				else
				{
					std::cout << ", ";
				}
				std::cout << "(" << i << ", " << j << ")";
			}
		}
	}
	std::cout << "}" << std::endl;
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
