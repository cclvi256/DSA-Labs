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
	bool* visited;
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

	/// @brief Reset the record of field Graph::visited.
	void Reset();

	/// @brief Fix the fields of an object.
	/// @param mode In which mode the graph is constructed.
	// Maybe unnecessary.
	// void Init(char mode);

	/// @brief Get the degree of each vertex.
	/// @return The array of degrees of each vertex.
	int* Degree();

	/// @brief Print BFS traversal seires.
	/// @param start From which node does the traversal start.
	void BFS(int start);

	/// @brief Get BFS numbering series.
	/// @param start From which node does the numbering start.
	/// @return 
	int* BFS_Numbering(int start);

	/// @brief Span a tree from the graph with BFS.
	/// @param start From which node to span the tree.
	/// @return 
	int* BF_SpanTree(int start);

	/// @brief Print DFS traversal seires.
	/// @param start From which node does the traversal start.
	void DFS(int start);

	/// @brief Get DFS numbering series.
	/// @param start From which node does the numbering start.
	/// @return 
	int* DFS_Numbering(int start);

	/// @brief Span a tree from the graph with DFS.
	/// @param start From which node to span the tree.
	/// @return 
	int* DF_SpanTree(int start);

	/// @brief Print DFS traversal seires recursively.
	/// @param start From which node does the traversal start.
	void DFS_R(int start);

	/// @brief Get DFS numbering series recursively.
	/// @param start From which node does the numbering start.
	/// @return 
	int* DFS_R_Numbering(int start);

	/// @brief Span a tree from the graph with recursive DFS.
	/// @param start From which node to span the tree.
	/// @return 
	int* DF_R_SpanTree(int start);
};
