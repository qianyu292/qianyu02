//队列链表实现
template<typename E>
struct Node
{
	E val;
	Node* next;
	Node(const E& v = E(), Node* n = nullptr) : val(v), next(n) {}
};
template<typename E>
class queue
{
private:
	Node<E>* q;
public:
	queue()
	{
		q = new Node<E>();
		q->next = nullptr;
	}
	queue(const queue<E>& q1)
	{
		// 创建带头结点的空队列
		q = new Node<E>();
		q->next = nullptr;

		// 遍历 q1 的链表，逐个复制元素
		Node<E>* current = q1.q->next;  // 跳过头结点
		Node<E>* tail = q;               // 指向新队列的尾部

		while (current != nullptr)
		{
			tail->next = new Node<E>(current->val);
			tail = tail->next;
			current = current->next;
		}
	}

	// 赋值运算符（修正版）
	queue<E>& operator=(const queue<E>& q1)
	{
		if (this == &q1) return *this;  // 防止自赋值

		// 清空当前队列
		MakeEmpty();

		// 复制新元素
		Node<E>* current = q1.q->next;
		Node<E>* tail = q;
		while (current != nullptr)
		{
			tail->next = new Node<E>(current->val);
			tail = tail->next;
			current = current->next;
		}

		return *this;
	}
	~queue()
	{
		MakeEmpty();
		delete q;
	}
	bool isEmpty()
	{
		return q->next == nullptr;
	}
	void MakeEmpty()
	{
		Node<E>* head = q->next;
		while (head != nullptr)
		{
			Node<E>* temp = head;
			head = head->next;
			delete temp;
		}
		q->next = nullptr;  // 必须置空！
	}
	void Enqueue(E x)
	{
		Node<E>* p = q;
		while (p->next != nullptr)
		{
			p = p->next;
		}
		Node<E>* newnode = new Node<E>();
		newnode->val = x;
		p->next = newnode;
	}
	E front()
	{
		if (isEmpty())
		{
			throw "queue is Empty";
		}
		return q->next->val;
	}
	void Dequeue()
	{
		if (isEmpty())
		{
			throw "queue is Empty";
		}
		Node<E>* temp = q->next;
		q->next = temp->next;
		delete temp;
	}
	E FrontandDequeue()
	{
		if (isEmpty())
		{
			throw "queue is Empty";
		}
		Node<E>* temp = q->next;
		q->next = temp->next;
		E oldval = temp->val;
		delete temp;
		return oldval;
	}
};