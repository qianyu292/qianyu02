//线性探查法
#include <vector>
#include <list>
#include <stdexcept>
template<typename K,typename V>
class HashMap2
{
private:
	struct KVNode
	{
		K key;
		V val;
		KVNode(K key, V val) :key(key), val(val) {};
	};
	std::vector<KVNode*> table;
	int size_;
	static const int INIT_CAP = 4;
	int hash(K key) {
		return (std::hash<K>()(key) & 0x7fffffff) % table.size();
	}
	int getKeyIndex(K key)
	{
		int index;
		for (index = hash(key); table[index] != nullptr; index = (index + 1) % table.size())
		{
			if (table[index]->key == key)
			{
				return index;
			}
		}
		return index;
	}
	void resize(int newCap)
	{
		HashMap2<K, V>newMap(newCap);
		for (KVNode* cur : table)
		{
			if (cur != nullptr)
			{
				newMap.put(cur->key, cur->val);
			}
		}
		table = std::move(newMap.table);
	}
public:
	HashMap2():HashMap2(INIT_CAP){}
	HashMap2(int initcapacity):size_(0){
		table.resize(initcapacity, nullptr);
	}
	~HashMap2()
	{
		for (KVNode* node : table)
		{
			delete node;
		}
	}
	void put(K key, V val)
	{
		if (size_ >= table.size() * 0.75)
		{
			resize(table.size() * 2);
		}
		int index = getKeyIndex(key);
		if (table[index] != nullptr)
		{
			table[index]->val = val;
			return;
		}
		table[index] = new KVNode(key, val);
		size_++;
		return;
	}
	void remove(K key)
	{
		if (size_ <= table.size() / 8)
		{
			resize(table.size() / 4);
		}
		int index = getKeyIndex(key);
		if (table[index] == nullptr)
		{
			return;
		}
		delete table[index];
		table[index] = nullptr;
		size_--;
		
		//rehash
		index = (index + 1) % table.size();
		while (table[index] != nullptr)
		{
			KVNode* entry = table[index];
			table[index] = nullptr;
			size_--;
			put(entry->key, entry->val);
			delete entry;
			index = (index + 1) % table.size();
		}
	}
	V get(K key)
	{
		int index = getKeyIndex(key);
		if (table[index] == nullptr)
		{
			return V();
		}
		return table[index]->val;
	}
	std::list<K> keys()
	{
		std::list<K>res;
		for (KVNode* entry : table)
		{
			if (entry != nullptr)
			{
				res.push_back(entry->key);
			}
		}
		return res;
	}
	int size() const
	{
		return size_;
	}
};