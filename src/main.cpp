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

	int* arr = new int[g.order];

	arr = g.BFS_Numbering(0, 'm');
	std::cout << "BFS numbering result(from adjacency matrix): ";
	std::cout << std::endl;

	arr = g.BFS_Numbering(0, 'l');
	std::cout << "BFS numbering result(from adjacency list): ";
	std::cout << std::endl;

	arr = g.DFS_Numbering(0, 'm');
	std::cout << "DFS numbering result(from adjacency matrix): ";
	std::cout << std::endl;

	arr = g.DFS_Numbering(0, 'l');
	std::cout << "DFS numbering result(from adjacency list): ";
	std::cout << std::endl;

	g.DFS_R_Numbering(0, arr, 'm');
	std::cout << "DFS numbering result(from adjacency matrix): ";
	std::cout << std::endl;

	g.DFS_R_Numbering(0, arr, 'l');
	std::cout << "DFS numbering result(from adjacency list): ";
	std::cout << std::endl;

	arr = g.Degree();

	return 0;
}
