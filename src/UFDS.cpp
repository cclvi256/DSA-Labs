#include "UFDS.h"

UFDS::UFDS(int cardinality, Elem* elements)
{
	this->cardinality = cardinality;
	this->elements = elements;
	Set* sets = new Set[cardinality];
	this->sets = sets;

	for (int i = 0; i < cardinality; i++)
	{
		sets[i].superset = nullptr;
		this->elements[i].set = this->sets + i;
	}
}

void UFDS::Union(Set* root1, Set* root2)
{
	root2->superset = root1;
}

Set* UFDS::Find(Elem element)
{
	int position;
	for (position = 0; position < this->cardinality; position++)
	{
		if (this->elements[position] == element)
		{
			break;
		}
	}

	Set* root = elements[position].set;

	while (root->superset != nullptr)
	{
		root = root->superset;
	}
		// TODO: 在此处插入 return 语句
	return root;
}

Set::Set()
{
	this->superset = nullptr;
}

Set::Set(Set* superset)
{
	this->superset = nullptr;
}

const bool Elem::operator==(const Elem op2) const
{
	return this->value == op2.value;
}
