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
		this->elements[i].master = this->sets + i;
	}

	setNum = cardinality;
}

void UFDS::Union(Set* root1, Set* root2)
{
	root2->superset = root1;
}

void UFDS::Union(Elem* elem1, Elem* elem2)
{
	Find(*elem2)->superset = Find(*elem1);
	if (Find(*elem1) != Find(*elem2))
	{
		this->setNum--;
	}
}

void UFDS::Union(Elem& elem1, Elem& elem2)
{
	Find(elem2)->superset = Find(elem1);
	if (Find(elem1) != Find(elem2))
	{
		this->setNum--;
	}
}

int UFDS::Parts()
{
	return this->setNum;
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

	Set* root = elements[position].master;

	while (root->superset != nullptr)
	{
		root = root->superset;
	}

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
