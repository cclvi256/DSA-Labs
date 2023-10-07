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

	static BT* Initialise(int Position);
	void PreorderTraverse();
	void InorderTraverse();
	void PostorderTraverse();
	void LevelOrderTraverse();
	void RPreorderTraverse();
	void RInorderTraverse();
	void RPostorderTraverse();
	int Width();
	bool IsComplete();
};

int main(int argc, char** argv)
{
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

	if (IsEmpty())
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

BT* BT::Initialise(int position)
{
	BT bt = BT();
	BT* l = nullptr, * r = nullptr;

	cout << "Please enter the node at " << position;
	char ch;
	cin >> ch;
	bt.root->value = ch;

	char YorN;

	cout << "Do you want to create " << position << "'s left sub node? (Y/N): ";
	cin >> YorN;
	if (YorN == 'y' || YorN == 'Y')
	{
		l = Initialise(2 * position);
		bt.root->l = l->root;
	}

	cout << "Do you want to create " << position << "'s right sub node? (Y/N): ";
	cin >> YorN;
	if (YorN == 'y' || YorN == 'Y')
	{
		r = Initialise(2 * position + 1);
		bt.root->r = r->root;
	}

	return &bt;
}

void BT::PreorderTraverse()
{
	Stack<N*> s;
	s.Push(root);
	N* ptr = nullptr;

	while (!s.IsEmpty())
	{
		ptr = s.top->value;

		cout << s.top->value->value << '\t';
		s.Pop();

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

void BT::InorderTraverse()
{
	Stack<N*> s;
	s.Push(root);
	N* ptr = nullptr;

	while (!s.IsEmpty())
	{
		ptr = s.top->value;
	}
}

void BT::PostorderTraverse()
{
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
	cout << root->value;

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

	cout << root->value;

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

	cout << root->value;
}

int BT::Width()
{
	return 0;
}

bool BT::IsComplete()
{
	return false;
}
