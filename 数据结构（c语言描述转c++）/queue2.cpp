template<typename E>
struct QueueNode
{
	int capacity;
	int Front;
	int Rear;
	int size;
	E* Array;
};
template<typename E>
class Queue
{
private:
	QueueNode<E>* q;
public:
	Queue(int MaxCapacity)
	{
		q = new QueueNode<E>();
		q->size = 0;
		q->Front = 0;
		q->Rear = -1;
		q->capacity = MaxCapacity;
		q->Array = new E[MaxCapacity];
	}
	Queue(const Queue<E>& q1)
	{
		q = new QueueNode<E>();

		this->q->size = q1->q->size;
		this->q->Front = q1->q->Front;
		this->q->Rear = q1->q->Rear;
		this->q->capacity = q1->q->capacity;

		q->Array = new E[q->capacity];
		for (int i = 0; i < q->capacity; i++) {
			q->Array[i] = q1.q->Array[i];
		}
	}
	Queue<E>& operator=(const Queue<E>& q1)
	{
		if (this == &q1) return *this;  // 防止自赋值

		// 释放旧资源
		delete[] q->Array;

		// 复制新数据
		q->size = q1.q->size;
		q->Front = q1.q->Front;
		q->Rear = q1.q->Rear;
		q->capacity = q1.q->capacity;

		// 深拷贝数组
		q->Array = new E[q->capacity];
		for (int i = 0; i < q->capacity; i++) {
			q->Array[i] = q1.q->Array[i];
		}

		return *this;
	}
	~Queue()
	{
		MakeEmpty();
		delete[]q->Array;
		delete q;
	}
		bool isEmpty()const
	{
		return q->size == 0;
	}
	bool isFull()const
	{
		return q->size == q->capacity;
	}
	void MakeEmpty()
	{
		if (q->size == 0)
		{
			throw "queue is Empty";
		}
		q->Front = q->size = 0;
		q->Rear = -1;
	}
	void Enqueue(E x)
	{
		if (isFull())
		{
			throw "queue is Full";
		}
		q->Rear++;
		q->Array[q->Rear] = x;
		q->size++;
	}
	E Front()
	{
		return q->Array[q->Front];
	}
	void Dequeue()
	{
		if (q->size == 0 && q->Front == q->Rear)
		{
			throw "queue is Empty";
		}
		q->Front++;
		q->size--;
	}
	E FrontandDequeue()
	{
		if (q->size == 0 && q->Front == q->Rear)
		{
			throw "queue is Empty";
		}
		int temp = q->Front;
		q->Front++;
		E oldval= q->Array[temp];
		delete q->Array[temp];
		q->size--;
		return oldval;
	}
};