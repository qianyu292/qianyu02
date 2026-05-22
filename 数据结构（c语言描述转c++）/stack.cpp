#include<vector>
using namespace std;
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
	stack(const stack<E>& stack1)
	{
		// 1. 创建新头结点
		stk = new Node<E>();
		stk->next = nullptr;

		// 2. 遍历原栈的数据节点（跳过原头结点）
		Node<E>* current = stack1.stk->next;  // 第一个实际数据节点

		// 由于栈是 LIFO，直接复制会逆序，需要特殊处理
		// 方法：用临时数组或递归，这里用简单方法——两次遍历

		// 方法1：先复制到数组，再重新入栈（保持顺序）
		std::vector<E> temp;
		while (current != nullptr)
		{
			temp.push_back(current->val);
			current = current->next;
		}

		// 从后往前入栈，保持原顺序
		for (int i = temp.size() - 1; i >= 0; i--)
		{
			push(temp[i]);
		}
	}

	stack<E>& operator=(const stack<E>& stack1)
	{
		if (this != &stack1)  // 检查自我赋值
		{
			// 清空当前栈的内容
			MakeEmpty();

			// 创建新头结点
			stk = new Node<E>();
			stk->next = nullptr;

			// 遍历原栈的数据节点（跳过原头结点）
			Node<E>* current = stack1.stk->next;  // 第一个实际数据节点

			// 由于栈是 LIFO，直接复制会逆序，需要特殊处理
			// 方法：用临时数组或递归，这里用简单方法——两次遍历

			// 方法1：先复制到数组，再重新入栈（保持顺序）
			std::vector<E> temp;
			while (current != nullptr)
			{
				temp.push_back(current->val);
				current = current->next;
			}

			// 从后往前入栈，保持原顺序
			for (int i = temp.size() - 1; i >= 0; i--)
			{
				push(temp[i]);
			}
		}
		return *this;
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