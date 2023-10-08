#include <iostream>

using namespace std;

struct N
{
	char value;
	N* l;
	N* r;
};

template <class T>
struct L
{
	T value;
	L<T>* next;
};

template <class T>
struct Stack
{
	L<T>* top;

	Stack();

	void Push(T value);
	void Push(T* value);
	void Pop();
	bool IsEmpty();
	void Clear();
	void Print();
};

template <class T>
struct Queue
{
	L<T>* front;
	L<T>* rear;

	Queue();

	void Push(T value);
	void Push(T* value);
	void Pop();
	bool IsEmpty();
	void Clear();
	void Print();
};

struct BT
{
	N* root;

	BT();
	BT(N* sub);
	BT(char value);

	// TODO: Exit every traversing function when the binary tree is empty.

	static N* Initialise(int position);
	void PreorderTraverse();
	void InorderTraverse();
	void PostorderTraverse();
	void LevelOrderTraverse();
	void RPreorderTraverse();
	void RInorderTraverse();
	void RPostorderTraverse();
	int Height();
	int Width();
	bool IsComplete();
	void HeightDetector(int position, int worstLen, int* positionArr);
	void HeightDetector(int position, int& deepest);
	void WidthDetector(int position, int height, int* temp);
};

int main(int argc, char** argv)
{
	N* root = BT::Initialise(1);
	BT bt = BT(root);

	cout << "Preorder traversal:" << endl;
	cout << "\tNon-recursive:\t";
	bt.PreorderTraverse();
	cout << "\n\t    Recursive:\t";
	bt.RPreorderTraverse();

	cout << "\nInorder traversal:" << endl;
	cout << "\tNon-recursive:\t";
	bt.InorderTraverse();
	cout << "\n\t    Recursive:\t";
	bt.RInorderTraverse();

	cout << "\nPostorder traversal:" << endl;
	cout << "\tNon-recursive:\t";
	bt.PostorderTraverse();
	cout << "\n\t    Recursive:\t";
	bt.RPostorderTraverse();

	cout << "\nLevel-order traversal:" << endl;
	cout << "\tNon-recursive:\t";
	bt.LevelOrderTraverse();

	cout << "\nThis binary tree is ";
	if (!(bt.IsComplete()))
	{
		cout << "not ";
	}
	cout << "a complete binary tree. " << endl;

	cout << "The tree's width is " << bt.Width() << ". " << endl;

	return 0;
}

template<class T>
Stack<T>::Stack()
{
	top = nullptr;
}

template<class T>
void Stack<T>::Push(T value)
{
	L<T>* newElem = new L<T>;
	newElem->value = value;
	newElem->next = top;
	top = newElem;
}

template<class T>
void Stack<T>::Push(T* value)
{
	L<T>* newElem = new L<T>;
	newElem->value = *value;
	newElem->next = top;
	top = newElem;
}

template<class T>
void Stack<T>::Pop()
{
	if (!IsEmpty())
	{
		L<T>* temp = top;
		top = top->next;
		delete temp;
	}
	else
	{
		cout << "Invalid operation: Poping an empty stack. " << endl;
	}
}

template<class T>
bool Stack<T>::IsEmpty()
{
	return top == nullptr;
}

template<class T>
void Stack<T>::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

template<class T>
void Stack<T>::Print()
{
	L<T>* temp = top;

	cout << "Stack: Top\t";
	while (temp != nullptr)
	{
		cout << temp->value << '\t';
	}
	cout << "Bottom" << endl;
}

template<class T>
Queue<T>::Queue()
{
	front = nullptr;
	rear = nullptr;
}

template<class T>
void Queue<T>::Push(T value)
{
	L<T>* newElem = new L<T>;
	newElem->value = value;
	newElem->next = nullptr;

	if (!IsEmpty())
	{
		rear->next = newElem;
	}
	else
	{
		front = newElem;
	}

	rear = newElem;
}

template<class T>
void Queue<T>::Push(T* value)
{
	L<T>* newElem = new L<T>;
	newElem->value = *value;
	newElem->next = nullptr;

	if (!IsEmpty())
	{
		rear->next = newElem;
	}
	else
	{
		front = newElem;
	}

	rear = newElem;
}

template<class T>
void Queue<T>::Pop()
{
	if (!IsEmpty())
	{
		L<T>* temp = front;
		front = front->next;
		delete temp;
	}
	else
	{
		cout << "Invalid operation: Poping an empty queue. " << endl;
	}

	if (front == nullptr)
	{
		rear = nullptr;
	}
}

template<class T>
bool Queue<T>::IsEmpty()
{
	return front == nullptr && rear == nullptr;
}

template<class T>
void Queue<T>::Clear()
{
	while (!IsEmpty())
	{
		Pop();
	}
}

template<class T>
void Queue<T>::Print()
{
	L<T>* temp = front;

	cout << "Queue: Front\t";
	while (temp != nullptr)
	{
		cout << temp->value << '\t';
	}
	cout << "Rear" << endl;
}

BT::BT()
{
	root = nullptr;
}

BT::BT(N* sub)
{
	root = sub;
}

BT::BT(char value)
{
	root = new N;
	root->l = root->r = nullptr;
	root->value = value;
}

N* BT::Initialise(int position)
{
	N* n = new N;
	n->l = nullptr;
	n->r = nullptr;

	cout << "Please enter the value at position " << position << " : ";
	char ch;
	cin >> ch;

	n->value = ch;

	char lyorn, ryorn;

	cout << "Do you want a left sub node for node " << position << "? (Y/N): ";
	cin >> lyorn;
	if (lyorn == 'y' || lyorn == 'Y')
	{
		n->l = Initialise(2 * position);
	}

	cout << "Do you want a right sub node for node " << position << "? (Y/N): ";
	cin >> ryorn;
	if (ryorn == 'y' || ryorn == 'Y')
	{
		n->r = Initialise(2 * position + 1);
	}

	return n;
}

void BT::PreorderTraverse()
{
	if (root == nullptr)
	{
		return;
	}

	Stack<N*> s;
	N* ptr = root;

	while ((!s.IsEmpty()) || ptr != nullptr)
	{
		if (ptr != nullptr)
		{
			cout << ptr->value << '\t';
			s.Push(ptr);
			ptr = ptr->l;
		}
		else
		{
			ptr = s.top->value;
			s.Pop();
			ptr = ptr->r;
		}
	}
}

void BT::InorderTraverse()
{
	if (root == nullptr)
	{
		return;
	}

	Stack<N*> s;
	N* ptr = root;

	while ((!s.IsEmpty()) || ptr != nullptr)
	{
		if (ptr != nullptr)
		{
			s.Push(ptr);
			ptr = ptr->l;
		}
		else
		{
			ptr = s.top->value;
			cout << ptr->value << '\t';
			s.Pop();
			ptr = ptr->r;
		}
	}
}


void BT::PostorderTraverse()
{
	if (root == nullptr)
	{
		return;
	}

	Stack<N*> s;
	s.Push(root);
	N* ptr = nullptr;
	N* last = nullptr;

	while (!s.IsEmpty())
	{
		ptr = s.top->value;

		if (ptr->l == nullptr && ptr->r == nullptr)
		{
			cout << s.top->value->value << '\t';
			s.Pop();
			last = ptr;
		}
		else if (last == ptr->l || last == ptr->r)
		{
			cout << s.top->value->value << '\t';
			s.Pop();
			last = ptr;
		}
		else
		{
			if (ptr->r != nullptr)
			{
				s.Push(ptr->r);
			}

			if (ptr->l != nullptr)
			{
				s.Push(ptr->l);
			}
		}
	}
}

void BT::LevelOrderTraverse()
{
	if (root == nullptr)
	{
		return;
	}

	Queue<N*> q;
	q.Push(root);
	N* ptr = nullptr;

	while (!q.IsEmpty())
	{
		ptr = q.front->value;

		if (ptr->l != nullptr)
		{
			q.Push(ptr->l);
		}

		if (ptr->r != nullptr)
		{
			q.Push(ptr->r);
		}

		cout << q.front->value->value << '\t';
		q.Pop();
	}
}

void BT::RPreorderTraverse()
{
	cout << root->value << '\t';

	if (root->l != nullptr)
	{
		BT newBT = BT(root->l);
		newBT.RPreorderTraverse();
	}

	if (root->r != nullptr)
	{
		BT newBT = BT(root->r);
		newBT.RPreorderTraverse();
	}
}

void BT::RInorderTraverse()
{
	if (root->l != nullptr)
	{
		BT newBT = BT(root->l);
		newBT.RInorderTraverse();
	}

	cout << root->value << '\t';

	if (root->r != nullptr)
	{
		BT newBT = BT(root->r);
		newBT.RInorderTraverse();
	}
}

void BT::RPostorderTraverse()
{
	if (root->l != nullptr)
	{
		BT newBT = BT(root->l);
		newBT.RPostorderTraverse();
	}

	if (root->r != nullptr)
	{
		BT newBT = BT(root->r);
		newBT.RPostorderTraverse();
	}

	cout << root->value << '\t';
}

int BT::Height()
{
	int deepest = 1, h = 0;
	HeightDetector(1, deepest);
	while (deepest)
	{
		deepest /= 2;
		h++;
	}
	return h;
}

int BT::Width()
{
	int h = Height();
	int* arr = new int[h];
	WidthDetector(1, h, arr);

	int res = 0;

	for (int i = 0; i < h; i++)
	{
		res = res > arr[i] ? res : arr[i];
	}

	return res;
}

bool BT::IsComplete()
{
	int biggest;
	HeightDetector(1, biggest);
	int* arr = new int[biggest + 1];
	HeightDetector(1, biggest + 1, arr);

	for (int i = 1; i < biggest + 1; i++)
	{
		if (i - arr[i])
		{
			delete[] arr;
			return false;
		}
	}

	delete[] arr;

	return true;
}

void BT::HeightDetector(int position, int worstLen, int* positionArr)
{
	positionArr[position] = position;

	if (root->l != nullptr)
	{
		BT newBT = BT(root->l);
		newBT.HeightDetector(position * 2, worstLen, positionArr);
	}

	if (root->r != nullptr)
	{
		BT newBT = BT(root->r);
		newBT.HeightDetector(position * 2 + 1, worstLen, positionArr);
	}
}

void BT::HeightDetector(int position, int& deepest)
{
	deepest = position > deepest ? position : deepest;

	if (root->l != nullptr)
	{
		BT newBT = BT(root->l);
		newBT.HeightDetector(position * 2, deepest);
	}

	if (root->r != nullptr)
	{
		BT newBT = BT(root->r);
		newBT.HeightDetector(position * 2 + 1, deepest);
	}
}

void BT::WidthDetector(int position, int height, int* temp)
{
	int positionCopy = position;
	int depth = -1;
	while (positionCopy)
	{
		positionCopy /= 2;
		depth++;
	}
	temp[depth]++;

	if (root->l != nullptr)
	{
		BT newBT = BT(root->l);
		newBT.WidthDetector(position * 2, height, temp);
	}

	if (root->r != nullptr)
	{
		BT newBT = BT(root->r);
		newBT.WidthDetector(position * 2 + 1, height, temp);
	}
}
