struct ENode
{
	int v1;
	int v2;
	int weight;
	ENode* next;

	ENode(int v1, int v2,int weight);
	ENode(int v1, int v2, int weight, ENode* base);

	const bool operator<(const ENode op2) const;
};

struct ESet
{
	ENode* start;

	inline void MergeSort()
	{
		MergeSort(1);
	}
	void MergeSort(int mergeSize);
	void Add(int v1, int v2, int weight);
};
