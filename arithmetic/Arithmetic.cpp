#include "Arithmetic.h"

using namespace std;

// Structures

/// @brief A node in a singly linked list.
/// @tparam T The type of the value in the node.
template <typename T>
struct Node
{
	T value;
	Node<T> *next;
};

/// @brief A stack with some basic operations.
/// @tparam T The type of the value in the stack.
template <typename T>
struct Stack
{
	Node<T> *header;

	/// @brief Delete ALL NODES in the stack.
	/// @param header
	void MakeNull();

	/// @brief Get the value which is on the top of the stack.
	/// @param header
	/// @return
	T Top();

	/// @brief Delete the value which is on the top of the stack.
	/// @param header
	void Pop();

	/// @brief Add a new value to the top of the stack.
	/// @param header
	/// @param value
	void Push(T value);

	/// @brief Check if the stack is empty.
	/// @param header
	/// @return
	bool IsEmpty();

	/// @brief Print the stack from top to bottom.
	/// @param header
	void Print();
};

// Functions

string GetExpression(string path);

void ReplaceMinus(string &expression);

int Priority(char ch);

void Convert(string &expression);

double Calculate(string &expression);

bool IsNumber(char ch);

int main(int argc, char **argv)
{
	cout << "Please enter the file path: ";
	string path;
	cin >> path;

	string expression = GetExpression(path);
	cout << "Expression: " << expression << endl << endl;
	ReplaceMinus(expression);
	Convert(expression);
	cout << endl << "Converted: " << expression << endl << endl;
	double result = Calculate(expression);
	cout << endl << "Result: " << result << endl;

	return 0;
}

template <typename T>
void Stack<T>::MakeNull()
{
	while (!IsEmpty(header))
	{
		Pop(header);
	}
}

template <typename T>
T Stack<T>::Top()
{
	return header->value;
}

template <typename T>
void Stack<T>::Pop()
{
	if (!IsEmpty())
	{
		Node<T> *t = header;
		header = header->next;
		delete t;
		Print();
		return;
	}

	else
	{
		cout << "Stack is empty!" << endl;
		return;
	}
}

template <typename T>
void Stack<T>::Push(T value)
{
	Node<T> *t = new Node<T>;
	t->value = value;
	t->next = header;
	header = t;
	Print();
}

template <typename T>
bool Stack<T>::IsEmpty()
{
	return header == nullptr;
}

template <typename T>
void Stack<T>::Print()
{
	cout << "Stack: ";
	cout << "Top";
	Node<T> *t = header;
	while (t != nullptr)
	{
		cout << "\t" << t->value;
		t = t->next;
	}
	cout << "\tBottom" << endl;
	return;
}

string GetExpression(string path)
{
	ifstream fin;
	fin.open(path, ios::in);
	if (!fin.is_open())
	{
		cout << "File not found!" << endl;
		exit(0);
	}

	string rv;
	char ch;

	while ((ch = fin.get()) != '#')
		;

	while ((ch = fin.get()) != '#')
	{
		if (!isspace(ch))
		{
			rv.push_back(ch);
		}
	}

	return rv;
}

void ReplaceMinus(string &expression)
{
	if (expression.at(0) == '-')
	{
		expression.replace(0, 1, "m");
	}

	for (int i = 0; i < expression.length(); i++)
	{
		if (expression.at(i) == '-')
		{
			if (!(expression.at(i - 1) == ')' || isdigit(expression.at(i - 1))))
			{
				expression.replace(i, 1, "m");
			}
		}
	}
}

int Priority(char ch)
{
	int rv = 0;
	switch (ch)
	{
	case ')':
		rv = 0;
		break;
	case '+':
	case '-':
		rv = 1;
		break;
	case '*':
	case '/':
		rv = 2;
		break;
	case '^':
		rv = 3;
		break;
	case '(':
		rv = 4;
		break;
	}

	return rv;
}

void Convert(string &expression)
{
	Stack<char> ops;
	ops.header = nullptr;
	string rv;
	for (char ch : expression)
	{
		if (IsNumber(ch))
		{
			rv.push_back(ch);
		}

		else
		{
			rv.push_back(' ');
			if (ch == ')')
			{
				while (ops.Top() != '(')
				{
					rv.push_back(' ');
					rv.push_back(ops.Top());
					rv.push_back(' ');
					ops.Pop();
				}

				ops.Pop();
			}

			else
			{
				while (!ops.IsEmpty())
				{
					if (Priority(ch) <= Priority(ops.Top()) && ops.Top() != '(')
					{
						rv.push_back(' ');
						rv.push_back(ops.Top());
						rv.push_back(' ');
						ops.Pop();
						continue;
					}

					break;
				}
				ops.Push(ch);
			}
		}
	}

	while (!ops.IsEmpty())
	{
		rv.push_back(' ');
		rv.push_back(ops.Top());
		ops.Pop();
	}

	rv.push_back(' ');

	for (int i = 1; rv[i] != '\0'; i++)
	{
		if (rv[i] == ' ' && rv[i - 1] == ' ')
		{
			rv.replace(i--, 1, "");
		}
	}

	expression = rv;
}

double Calculate(string &expression)
{
	Stack<double> num;
	num.header = nullptr;

	double dec = 1;
	double current = 0;
	bool isN = true;
	bool negative = false;
	bool dot = false;

	for (int i = 0; i < expression.length(); i++)
	{
		char ch = expression[i];
		if (IsNumber(ch))
		{
			if (ch == '.')
			{
				dot = true;
			}

			else if (ch == 'm')
			{
				negative = true;
			}

			else
			{
				if (!dot)
				{
					current *= 10;
					current += negative ? '0' - ch : ch - '0';
				}

				else
				{
					dec /= 10;
					current += dec * (negative ? '0' - ch : ch - '0');
				}
			}
		}

		else if (isspace(ch))
		{
			if (isN)
			{
				num.Push(current);

				dec = 1;
				current = 0;
				dot = false;
				negative = false;
			}
			isN = true;
		}


		else
		{
			isN = false;
			double n1, n2, r;
			n2 = num.Top();
			num.Pop();
			n1 = num.Top();
			num.Pop();

			if (ch == '/' && n2 == 0)
			{
				cout << "Error: Divided by 0!";
				exit(0);
			}

			switch (ch)
			{
			case '+':
				r = n1 + n2; break;
			case '-':
				r = n1 - n2; break;
			case '*':
				r = n1 * n2; break;
			case '/':
				r = n1 / n2; break;
			case '^':
				r = pow(n1, n2); break;
			default:
				cout << "Unexpected symbol!"; exit(0); break;
			}

			num.Push(r);
		}
	}
	return num.Top();
}

bool IsNumber(char ch)
{
	return isdigit(ch) || ch == '.' || ch == 'm';
}
