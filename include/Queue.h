template <class T>
struct QNode
{
	T value;
	QNode* next;

	QNode();
	QNode(T value);
	QNode(T value, QNode* next);
};

template <class T>
struct Queue
{
	QNode<T>* front;
	QNode<T>* back;

	Queue();

	void Push(T value);
	void Pop();
	void Destroy();

	inline bool IsEmpty()
	{
		return this->front == nullptr || this->back == nullptr;
	}
};

