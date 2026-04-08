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
	//ÏÂÃæµÄL¼´head¡£
public:
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
};