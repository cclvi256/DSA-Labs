#include "main.h"

int main(int argc, char** argv)
{
	// Graph constructing
	Graph g;
	std::cout << "Graph g is: " << std::endl;
	g.Print();

	// Converting  adjacency list and adjacency matrix each other.
	Graph g1(g.order, g.adjList);
	std::cout << "Graph g1(converted from adjacency list)";
	std::cout << " is: " << std::endl;
	g1.Print();
	Graph g2(g.order, g.adjMat);
	std::cout << "Graph g2(converted from adjacency matrix)";
	std::cout << " is: " << std::endl;
	g2.Print();

	/* All the functions above is debugged. */

	int* arr = nullptr;

	std::cout << "BFS numbering results: " << std::endl;

	arr = g.BFS_Numbering(0, 'm');
	std::cout << "\tfrom adjacency matrix: ";
	PrintArray(arr, g.order);

	arr = g.BFS_Numbering(0, 'l');
	std::cout << "\tfrom adjacency list: ";
	PrintArray(arr, g.order);

	std::cout << std::endl << "Non-recursive DFS numbering results: " << std::endl;

	arr = g.DFS_Numbering(0, 'm');
	std::cout << "DFS numbering result(from adjacency matrix): ";
	PrintArray(arr, g.order);

	arr = g.DFS_Numbering(0, 'l');
	std::cout << "DFS numbering result(from adjacency list): ";
	PrintArray(arr, g.order);

	std::cout << std::endl << "Recursive DFS numbering results: " << std::endl;

	g.DFS_R_Numbering(0, arr, 'm');
	std::cout << "DFS numbering result(from adjacency matrix): ";
	PrintArray(arr, g.order);

	g.DFS_R_Numbering(0, arr, 'l');
	std::cout << "DFS numbering result(from adjacency list): ";
	PrintArray(arr, g.order);

	std::cout << std::endl << "Degree: ";
	arr = g.Degree();
	PrintArray(arr, g.order);

	return 0;
}

void PrintArray(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		std::cout << ' ' << arr[i];
	}

	std::cout << std::endl;
}
