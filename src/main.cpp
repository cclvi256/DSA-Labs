#include "main.h"

int main(int argc, char** argv)
{
	std::string path;
	std::cout << "Please enter the file path: ";
	std::cin >> path;

	Graph g(path);
	g.Print();

	Graph PrimMin(g.Prim(0));
	PrimMin.Print();

	Graph KruskalMin(g.Kruskal());
	KruskalMin.Print();
}
