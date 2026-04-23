#include<vector>
#include<iostream>
//并查集原始版本
class Union_find
{
private:
	std::vector<int>parent;
public:
	Union_find(int capacity)
	{
		parent = std::vector<int>(capacity);
		for (int i = 0; i < capacity; ++i)
		{
			parent[i] = i;
		}
	}
	void setunion(int root1,int root2)
	{
		int x = find(root1);
		int y = find(root2);
		if (x == y)return;
		parent[root2] = root1;
	}
	int find(int x)
	{
		if (parent[x] == x)
		{
			return x;
		}
		else
		{
			return find(parent[x]);
		}
	}
};
//路径压缩版本
class Union_Find
{
private:
	std::vector<int>parent;
	std::vector<int>rank;
public:
	Union_Find(int capacity)
	{
		parent = std::vector<int>(capacity);
		rank = std::vector<int>(capacity,0);
		for (int i = 0; i < capacity; ++i)
		{
			parent[i] = i;
		}
	}
	int Find(int x)
	{
		if (parent[x] == x)
		{
			return x;
		}
		else
		{
			parent[x] = Find(parent[x]);
		}
	}
	bool conenected(int root1, int root2)
	{
		return Find(root1) == Find(root2);
	}
	void Union(int root1,int root2)
	{
		if (Find(root1) == Find(root2))
		{
			return;
		}

		if (rank[root1] > rank[root2])
		{
			parent[root2] = root1;
		}
		else if (rank[root1] < rank[root2])
		{
			parent[root1] = root2;
		}
		else
		{
			parent[root2] = root1;
			rank[root1]++;
		}
	}
	int count()
	{
		int cnt = 0;
		for (int i = 0; i < parent.size(); ++i)
		{
			if (parent[i] == i)
			{
				cnt++;
			}
		}
		return cnt;
	}
};