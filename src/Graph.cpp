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

Graph Graph::Prim(int start)
{
	bool* connected = new bool[this->order];
	for (int i = 0; i < this->order; i++)
	{
		connected[i] = false;
	}
	Graph rg(this->order);
	for (int i = 0; i < this->order * this->order; i++)
	{
		rg.adjMat[i] = INFINITY;
	}

	auto done = [connected, this]() -> bool
	{
		for (int i = 0; i < this->order; i++)
		{
			if (!connected[i])
			{
				return false;
			}
		}

		return true;
	};

	auto nearest = [connected, this](int vertex) -> int
	{
		int base = vertex * this->order;
		int min = this->adjMat[base];
		int rv = 0;
		bool flag = true;

		for (int i = 0; i < this->order; i++)
		{
			if (vertex == i || connected[i])
			{
				continue;
			}

			if (flag)
			{
				rv = i;
				min = this->adjMat[base + i];
				flag = false;
			}
			else if (min > this->adjMat[base + i])
			{
				rv = i;
				min = this->adjMat[base + i];
			}

		}

		return flag ? -1 : rv;
	};

	connected[start] = true;

	while (!done())
	{
		int minV1, minV2, minW;
		bool flag = true;
		for (int i = 0; i < this->order; i++)
		{
			if (int t = nearest(i); connected[i] && t >= 0)
			{
				if (flag)
				{
					minV1 = i;
					minV2 = t;
					minW = this->adjMat[i * this->order + minV2];
				}
				else if (this->adjMat[i * this->order + t] < minW)
				{
					minV1 = i;
					minV2 = t;
					minW = this->adjMat[i * this->order + minV2];
				}
			}
		}

		connected[minV2] = true;
		rg.adjMat[minV1 * rg.order + minV2] = minW;
		rg.adjMat[minV2 * rg.order + minV1] = minW;
	}

	return rg;
}

Graph Graph::Kruskal()
{
	int len = this->order * (this->order - 1) / 2;
	int* edge = new int[len];
	int* sn = new int[len];
	Graph rg(this->order);

	for (int i = 0; i < this->order; i++)
	{
		for (int j = i + 1; j < this->order; j++)
		{
			edge[i * this->order + j] = this->adjMat[i * this->order + j];
			sn[i * this->order + j] = i * this->order + j;
		}
	}

	for (int i = 0; i < len - 1; i++)
	{
		for (int j = len - 1; j >= i; j--)
		{
			if (edge[i] > edge[i + 1])
			{
				int temp = edge[i];
				edge[i] = edge[i + 1];
				edge[i + 1] = temp;
				temp = sn[i];
				sn[i] = sn[i + 1];
				sn[i + 1] = temp;
			}
		}
	}

	// Elem* vertexes = new Elem[this->order];
	// for (int i = 0; i < this->order; i++)
	// {
	// 	vertexes[i].value = i;
	// }

	// UFDS vSet(this->order, vertexes);

	// for (int i = 0; i < len; i++)
	// {
	// 	int v1 = edge[i] / this->order;
	// 	int v2 = edge[i] % this->order;

		
	// }

	UFDS vSet(this->order);

	for (int i = 0; i < len; i++)
	{
		int v1 = sn[i] / this->order;
		int v2 = sn[i] % this->order;

		if (vSet.Find(v1) != vSet.Find(v2))
		{
			vSet.Union(v1, v2);
		}

		rg.adjMat[v1 * rg.order + v2] = edge[i];
		rg.adjMat[v2 * rg.order + v1] = edge[i];

		if (vSet.Parts() == 1)
		{
			break;
		}
	}

	return rg;
}

Graph::~Graph()
{
	delete[] this->adjMat;
}
