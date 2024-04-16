#include "UFDS.h"

UFDS::UFDS(int cardinality)
{
	this->cardinality = cardinality;
	Set* sets = new Set[cardinality];
	this->sets = sets;

	for (int i = 0; i < cardinality; i++)
	{
		sets[i].superset = nullptr;
	}

	setNum = cardinality;
}

void UFDS::Union(Set* root1, Set* root2)
{
	if (root2->superset == nullptr)
	{
		this->setNum--;
	}
	root2->superset = root1;
}

void UFDS::Union(int elem1, int elem2)
{
	if (Find(elem1) != Find(elem2))
	{
		this->setNum--;
		Find(elem2)->superset = Find(elem1);
	}
}

int UFDS::Parts()
{
	return this->setNum;
}

Set* UFDS::Find(int element) const
{
	Set* root = this->sets + element;

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
