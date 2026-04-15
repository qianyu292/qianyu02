//À­Á´·¨
#include<vector>
#include<list>
#include<functional>
#include<algorithm>
template<typename key,typename val>
class HashTable
{
private:
	using Pair = std::pair<key, val>;
	std::vector<std::list<Pair>>thelists;
	int tablesize;

	int hash(const key& key)const
	{
		return std::hash<key>{}(key) % tablesize;
	}
public:
	HashTable(int size):tablesize(size),thelists(size){}
	~HashTable()
	{
		MakeEmpty();
	}
	void insert(const key& key,const val&val)
	{
		auto &temp = thelists[hash(key)];
		for (auto& pair : temp)
		{
			if (pair.first == key)
			{
				pair.second = val;
				return;
			}
		}
		temp.push_back({ key,val });
	}
	bool Find(const key& key,val&val)const
	{
		const auto&temp= thelists[hash(key)];
		for (auto& pair : temp)
		{
			if (pair.first == key)
			{
				val = pair.second;
				return true;
			}
		}
		return false;
	}
	val* find(const key& key)
	{
		const auto&temp = thelists[hash(key)];
		for (auto& pair : temp)
		{
			if (pair.first == key)
			{
				return &pair.second;
			}
		}
		return nullptr;
	}
	void remove( key& key)
	{
		auto&temp = thelists[hash(key)];
		temp.remove_if([&key](const Pair& pair)
			{
				return pair.first == key;
			});
	}
	void MakeEmpty()
	{
		for (std::list<Pair>temp : thelists)
		{
			temp.clear();
		}
	}
};