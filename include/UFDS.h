struct Set
{
	Set* superset;

	Set();
	Set(Set* superset);
};

struct UFDS
{
	int cardinality;
	int setNum;
	Set* sets;

	UFDS(int cardinality);

	void Union(Set* root1, Set* root2);
	void Union(int elem1, int elem2);
	int Parts();
	Set* Find(int element) const;
};
