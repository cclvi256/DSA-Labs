struct Set
{
	Set* superset;

	Set();
	Set(Set* superset);
};

struct Elem
{
	int value;
	Set* master;

	const bool operator==(const Elem op2) const;
};

struct UFDS
{
	int cardinality;
	Elem* elements;
	Set* sets;
	int setNum;

	UFDS(int cardinality, Elem* elements);

	void Union(Set* root1, Set* root2);
	void Union(Elem* elem1, Elem* elem2);
	void Union(Elem& elem1, Elem& elem2);
	int Parts();
	Set* Find(Elem element);
};
