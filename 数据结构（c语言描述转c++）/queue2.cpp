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