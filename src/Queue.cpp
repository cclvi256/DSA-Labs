#include "Queue.h"
#include <iostream>
#include <cstdlib>

template<class T>
QNode<T>::QNode()
{
	this->next = nullptr;
}

template<class T>
QNode<T>::QNode(T value)
{
	this->value = value;
	this->next = nullptr;
}

template<class T>
QNode<T>::QNode(T value, QNode* next)
{
	this->value = value;
	this->next = next;
}

template<class T>
void Queue<T>::Push(T value)
{
	if (this->IsEmpty())
	{
		this->front = new QNode<T>(value);
		this->back = new QNode<T>(value);
	}
	else
	{
		this->back->next = new QNode<T>(value);
		this->back = this->back->next;
	}
}

template<class T>
void Queue<T>::Pop()
{
	if (this->IsEmpty())
	{
		std::cout << "Invalid operation: Poping an empty queue!" << std::endl;
		exit(1);
	}
	else
	{
		QNode<T>* copy = this->front;
		this->front = this->front->next;
		delete copy;

		if (IsEmpty())
		{
			this->back = nullptr;
		}
	}
}

template<class T>
void Queue<T>::Destroy()
{
	while (!IsEmpty())
	{
		this->Pop();
	}
}
