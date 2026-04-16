#include<vector>
using namespace std;
class UF
{
private:
	int _size;

	vector<int>parent;
public:
	UF(int n)
	{
		this->_size = n;
		parent.resize(n);
		for (int i = 0; i < n; ++i)
		{
			parent[i] = i;
		}
	}
	void _union(int p, int q)
	{
		int rootp = find(p);
		int rootq = find(q);
		if (rootp == rootq)
		{
			return;
		}
		parent[rootp] = rootq;
		_size--;
	}
	int find(int x)
	{
		if (parent[x] != x)
		{
			parent[x] = find(parent[x]);
		}
		return parent[x];
	}
	bool connected(int p, int q)
	{
		int rootp = find(p);
		int rootq = find(q);
		return rootp == rootq;
	}
	int count()
	{
		return _size;
	}
};