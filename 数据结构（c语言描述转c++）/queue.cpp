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
	Node<E>* queue;
public:
	queue()
	{
		queue = new Node<E>();
		queue->next = nullptr;
	}
	~queue()
	{
		MakeEmpty();
		delete queue;
	}
	bool isEmpty()
	{
		return queue->next == nullptr;
	}
	void MakeEmpty()
	{
		Node<E>* head = queue;
		while (head->next != nullptr)
		{
			Node<E>* temp = head->next;
			head->next = temp->next;
			delete temp;
		}
	}
	void Enqueue(E x)
	{
		Node<E>* p = queue;
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
		return queue->next->val;
	}
	void Dequeue()
	{
		if (isEmpty())
		{
			throw "queue is Empty";
		}
		Node<E>* temp = queue->next;
		queue->next = temp->next;
		delete temp;
	}
	E FrontandDequeue()
	{
		if (isEmpty())
		{
			throw "queue is Empty";
		}
		Node<E>* temp = queue->next;
		queue->next = temp->next;
		E oldval = temp->val;
		delete temp;
		return oldval;
	}
};