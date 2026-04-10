#include<vector>
using namespace std;
class selfAdjustingArray
{
private:
	vector<int>data;
	int capacity;
public:
	selfAdjustingArray(int cap = 100) :capacity(cap) {};
	bool find(int x)
	{
		for (size_t i = 0; i < data.size(); ++i)
		{
			if (data[i] == x)
			{
				for (size_t j = i; j > 0; j--)
				{
					data[j] = data[j - 1];
				}
				data[0] = x;
				return true;
			}
		}
		return false;
	}
	void insert(int x)
	{
		if (data.size() >= capacity)
		{
			return;  // 或者抛出异常
		}
		for (int i = 0; i < data.size(); ++i)
		{
			if (data[i] == x)
			{
				for (int j = i; j + 1 < data.size(); ++j)
				{
					data[j] = data[j + 1];
				}
				data.pop_back();
				break;
			}
		}
		data.insert(data.begin(),x);
	}
	bool remove(int x)
	{
		for (int i = 0; i < data.size(); ++i)
		{
			if (data[i] == x)
			{
				for (int j = i; j + 1 < data.size(); ++j)
				{
					data[j] = data[j + 1];
				}
				data.pop_back();
				return true;
			}
		}
		return false;
	}
};
struct Node
{
	int val;
	Node* next;
	Node(int val):val(val),next(nullptr){}
};
class SelfAdjustingList
{
private:
	Node* head;

	Node* Findprev(int x)
	{
		if (!head || head->val == x)return nullptr;
		Node* p = head;
		while (p->next != nullptr && p->next->val != x)
		{
			p = p->next;
		}
		return (p->next && p->next->val == x) ? p : nullptr;
	}
public:
	SelfAdjustingList():head(nullptr){}
	bool Find(int x)
	{
		if (!head)return false;
		if (head->val == x)return true;

		Node* prev = Findprev(x);
		if (!prev)return false;

		Node* target = prev->next;
		prev->next = target->next;

		target->next = head;
		head = target;

		return true;
	}
	void insert(int x)
	{
		if (head && head->val == x)
		{
			return;
		}
		Node* prev = Findprev(x);
		if (prev)
		{
			Node* target = prev->next;
			prev->next = target->next;
			delete target;
		}
		Node* newnode = new Node(x);
		newnode->next = head;
		head = newnode;
	}
	bool remove(int x)
	{
		if (!head)return false;
		if (head->val == x)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
			return true;
		}
		Node* prev = Findprev(x);
		if (!prev)return false;
		Node* target = prev->next;
		prev->next = target->next;
		delete target;
		return true;
	}
};