template<typename E>
struct StackNode
{
	int capacity;
	int Topofstack;
	E* Array;
};
template<typename E>
class Stack
{
private:
	StackNode<E>* stk;
public:
	Stack(int MaxElements)
	{
		stk = new StackNode<E>();
		stk->Topofstack = -1;
		stk->capacity = MaxElements;
		stk->Array = new E[stk->capacity];
	}
	~Stack()
	{
		delete[]stk->Array;
		delete stk;
	}
	Stack(const Stack&) = delete;
	Stack& operator=(const Stack&) = delete;
	bool isEmpty()const
	{
		return stk->Topofstack == -1;
	}
	bool isFull()const
	{
		return stk->Topofstack == stk->capacity - 1;
	}
	void MakeEmpty()
	{
		stk->Topofstack = -1;
	}
	void push(const E& x)
	{
		if (isFull())
		{
			throw "stack is Full";
		}
		else
		{
			stk->Topofstack++;
			stk->Array[stk->Topofstack] = x;
		}
	}
	E& top()
	{
		if (isEmpty())
		{
			throw "stack is Empty";
		}
		else
		{
			return stk->Array[stk->Topofstack];
		}
	}
	const E& top() const  // const°æ±¾
	{
		if (isEmpty())
		{
			throw "stack is Empty";
		}
		else
		{
			return stk->Array[stk->Topofstack];
		}
	}
	void pop()
	{
		if (isEmpty())
		{
			throw "stack is Empty";
		}
		else
		{
			stk->Topofstack--;
		}
	}
	E Topandpop()
	{
		if (stk->Topofstack == -1)
		{
			throw "stack is Empty";
		}
		else
		{
			E val = stk->Array[stk->Topofstack];
			stk->Topofstack--;
			return val;
		}
	}
};