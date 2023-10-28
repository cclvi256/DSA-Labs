#include "Graph.h"

Graph::Graph()
{
	using namespace std;

	cout << "Please enter the order of your graph: ";
	cin >> this->order;

	this->adjMat = new int[this->order * this->order];

	cout << "Please enter each edges and weight, ";
	cout << "Notice: number over 65535 will be \"INFINITY\"!";
	cout << endl << "Example: \"1 3 6\" refers to ";
	cout << "an edge between 1 and 3, with weight 6." << endl;
	cout << "Input of edges ends with a '#'. " << endl;

	for (int i = 0; i < this->order * this->order; i++)
	{
		this->adjMat[i] = INFINITY;
	}

	bool flag = true;

	while (flag)
	{
		char ch;
		while (isspace(ch = cin.get()));

		if (ch == '#')
		{
			flag = false;
		}
		else
		{
			int v1, v2, weight;
			cin >> v1 >> v2 >> weight;

			this->adjMat[v1 * this->order + v2] = weight;
			this->adjMat[v2 * this->order + v1] = weight;
		}
	}
}

Graph::Graph(int order)
{
	this->order = order;
	this->adjMat = new int[order * order];
}

Graph::~Graph()
{
	delete[] this->adjMat;
}
