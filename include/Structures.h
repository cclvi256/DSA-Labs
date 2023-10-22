struct VNode
{
	int sn;
	VNode* next;
};

struct Graph
{
	int vertexNum;
	int* adjMat;
	VNode* adjList;

	Graph();
	Graph(int vertexNum, int* adjMat);
	Graph(VNode* adjList);
	Graph(int vertecNum, VNode* adjList);

	void Print();
	void BFS(char mode, int vertexNum, int* adjMat);
	void BFS(char mode, int vertexNum, VNode* adjList);
	void BFS(char mode, VNode* adjList);
	void DFS(char mode, int vertexNum, int* adjMat);
	void DFS(char mode, int vertexNum, VNode* adjList);
	void DFS(char mode, VNode* adjList);
	void DFS_R(char mode, int vertexNum, int* adjMat);
	void DFS_R(char mode, int vertexNum, VNode* adjList);
	void DFS_R(char mode, VNode* adjList);
	int* Degree(char mode, int vertexNum, VNode* adjList);
	int* Degree(char mode, VNode* adjList);

	int CountVertex(VNode* adjList);
};
