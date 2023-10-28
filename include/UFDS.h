struct Set
{
	Set* superset;

	Set();
	Set(Set* superset);
};

struct Elem
{
	int value;
	Set* set;

	const bool operator==(const Elem op2) const;
};

struct UFDS
{
	int cardinality;
	Elem* elements;
	Set* sets;

	UFDS(int cardinality, Elem* elements);

	void Union(Set* root1, Set* root2);
	Set* Find(Elem element);
};
