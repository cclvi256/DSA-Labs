struct VNode
{
	int sn;
	VNode* next;

	VNode();
	VNode(int sn);
	VNode(int sn, VNode* next);
};

/// @brief The 1st vertex is numbered 0!
struct Graph
{
	/**********/
	/* Fields */
	/**********/

	int order;
	int* adjMat;	// This matrix will be horizental numbered.
	VNode* adjList;

	/****************/
	/* Constructors */
	/****************/

	/// @brief Construct graph from collections of vertexes & edges.
	Graph();

	/// @brief Construct a graph with no edges.
	/// @param order 
	Graph(int order);

	/// @brief Construct a graph with an adjacency matrix.
	/// @param order 
	/// @param adjMat 
	Graph(int order, int* adjMat);

	/// @brief Construct a graph with an adjacency list.
	/// @param order 
	/// @param adjList 
	Graph(int order, VNode* adjList);

	/**************/
	/* Destructor */
	/**************/

	virtual ~Graph();

	/***********/
	/* Methods */
	/***********/

	/// @brief Fix the fields of an object.
	/// @param mode In which mode the graph is constructed.
	// Maybe unnecessary.
	// void Init(char mode);

	/// @brief Get the degree of each vertex.
	/// @return The array of degrees of each vertex.
	int* Degree();

	/// @brief Get BFS numbering series.
	/// @param start From which node does the numbering start.
	/// @param mode From adjacency list or adjacency matrix?
	/// @return 
	int* BFS_Numbering(int start, char mode);

	/// @brief Get DFS numbering series.
	/// @param start From which node does the numbering start.
	/// @param mode From adjacency list or adjacency matrix?
	/// @return 
	int* DFS_Numbering(int start, char mode);

	/// @brief Get DFS numbering series recursively.
	/// @param start From which node does the numbering start.
	/// @param mode From adjacency list or adjacency matrix?
	/// @return 
	void DFS_R_Numbering(int start, int* arr, char mode);

	/// @brief Actually recursive function.
	/// @param start 
	/// @param arr 
	/// @param visited 
	/// @param mode From adjacency list or adjacency matrix?
	void DFS_R_Numbering(int start, int* arr, bool* visited, char mode);

	/// @brief Print the graph as vertex and edge collections.
	void Print();
};
