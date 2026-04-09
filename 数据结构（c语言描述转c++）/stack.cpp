//栈的链表实现
template<typename E>
struct Node
{
	E val;
	Node* next;
	Node(const E& v = E(), Node* n = nullptr) : val(v), next(n) {}
};
template<typename E>
class stack
{
private:
	Node<E>* stk;
public:
	stack()
	{
		stk = new Node<E>();
		stk->next = nullptr;
	}
	~stack()
	{
		MakeEmpty();
		delete stk;
	}
	bool IsEmpty()
	{
		return stk->next == nullptr;
	}
	void MakeEmpty()
	{
		while(!IsEmpty())
		{
			pop();
		}
	}
	void push(E x)
	{
		Node<E>* newnode = new Node<E>();
		newnode->val = x;

		Node<E>* temp = stk->next;
		stk->next = newnode;
		newnode->next = temp;
	}
	E Top()
	{
		if (IsEmpty())
		{
			throw "stk is empty";
		}
		return stk->next->val;
	}
	void pop()
	{
		if (IsEmpty())
		{
			throw  "stk is empty";
		}
		else
		{
			Node<E>* temp = stk->next;
			stk->next = temp->next;
			delete temp;
		}
	}
};