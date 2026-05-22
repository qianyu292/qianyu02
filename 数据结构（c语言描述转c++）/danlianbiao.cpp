#include<vector>
template<typename E>
struct Node
{
	E val;
	Node* next;
};
template<typename E>
class List
{
private:
	Node<E>* Head;
	//下面的L即head。
public:
	List() :Head(nullptr) {};
	List(const List<E>& list)
	{
		// 1. 创建新头结点
		Head = new Node<E>();
		Head->next = nullptr;

		// 2. 遍历原链表，逐个复制节点
		Node<E>* current = list.Head->next;  // 原链表第一个实际节点
		Node<E>* tail = Head;                 // 新链表的尾部节点

		while (current != nullptr)
		{
			// 创建新节点，完整复制所有数据
			Node<E>* newNode = new Node<E>(current->val);
			newNode->deleted = current->deleted;  // 复制懒惰删除标记
			newNode->next = nullptr;

			// 链接到新链表尾部
			tail->next = newNode;
			tail = newNode;  // 更新尾部指针

			// 移动到原链表下一个节点
			current = current->next;
		}
	}

	// 赋值运算符
	List<E>& operator=(const List<E>& list)
	{
		if (this == &list) return *this;  // 防止自赋值

		// 1. 清空当前链表的所有节点
		Node<E>* p = Head->next;
		while (p != nullptr)
		{
			Node<E>* temp = p;
			p = p->next;
			delete temp;
		}
		Head->next = nullptr;

		// 2. 深拷贝原链表
		Node<E>* current = list.Head->next;
		Node<E>* tail = Head;

		while (current != nullptr)
		{
			Node<E>* newNode = new Node<E>(current->val);
			newNode->deleted = current->deleted;
			newNode->next = nullptr;

			tail->next = newNode;
			tail = newNode;
			current = current->next;
		}

		return *this;
	}
	~List()
	{
		delete Head;
		this->Head = nullptr;
	}
	Node<E>* MakeEmpty(Node<E>* L);
	bool isEmpty(Node<E>* L)
	{
		return L->next == nullptr;
	}
	bool isLast(Node<E>* L)
	{
		return L->next == nullptr;
	}
	Node<E>* Find(E x, Node<E>* L)
	{
		Node<E>* p;
		p = L->next;
		while (p != nullptr && p->val != x)
		{
			p = p->next;
		}
		return p;
	}
	void Delete(E x, Node<E>* L)
	{
		Node<E>* p = Findprevious(x, L);
		if (p == nullptr||p->next==nullptr)
		{
			return;
		}
		else
		{
			Node<E>* temp = p->next;
			p->next = p->next->next;
			delete temp;
		}
	}
	Node<E>* Findprevious(E x, Node<E>* L)
	{
		Node<E>* p=L;
		while (p->next != nullptr && p->next->val != x)
		{
			p = p->next;
		}
		return p;
	}
	void insert(E x, Node<E>* L)
	{
		Node<E>* temp;
		temp = new Node<E>();
		temp->val = x;
		temp->next = L->next;
		L->next = temp;
	}
	void DeleteList(Node<E>* L)
	{
		Node<E>* p;
		Node<E>* temp;
		p = L->next;
		while (p != nullptr)
		{
			temp = p->next;
			delete p;
			p = temp;
		}
		L->next = nullptr;
	}
	Node<E>* Header(Node<E>* L)
	{
		return Head;
	}
	Node<E>* First(Node<E>* L)
	{
		return Head->next;
	}
	Node<E>* Advance(Node<E>* L)
	{
		return L->next;
	}
	E Retrieve(Node<E>* P)
	{
		return P->val;
	}
	std::vector<E> PrintList()
	{
		std::vector<E>res;
		Node<E>* p = Head->next;
		while (p != nullptr)
		{
			res.push_back(p->val);
			p = p->next;
		}
		return res;
	}
	void swap(Node<E>* L, Node<E>* R)
	{
		if (!L || !R || L == R)return;
		Node<E>* temp = Findprevious(L);
		Node<E>* temp2 = R->next;
		temp->next = R;
		R->next = L;
		L->next = temp2;
	}
	void ReverseList(Node<E>* head)
	{
		Node<E>* pre = nullptr, cur = head, nxt = head->next;
		while (cur != nullptr)
		{
			cur->next = pre;
			pre = cur;
			cur = nxt;
			if (nxt->next != nullptr)
			{
				nxt = nxt->next;
			}
		}
		return pre;
	}
};