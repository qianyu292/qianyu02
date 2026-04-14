// 二叉堆(最小堆)
// 插入时上滤，删除时下滤
#include<vector>
#include <functional>
#include <stdexcept>
template<typename E>
struct Heapstruct
{
    int capacity;
    int size;
    E* Elements;

    Heapstruct(int cap) : capacity(cap), size(0)
    {
        Elements = new E[cap + 1];  // 索引从1开始
    }

    ~Heapstruct()
    {
        delete[] Elements;
    }
};

template<typename E>
class PriorityQueue
{
private:
    Heapstruct<E>* table;

public:
    PriorityQueue() : table(nullptr) {}

    PriorityQueue(int InitCapacity)
    {
        table = new Heapstruct<E>(InitCapacity);
    }

    ~PriorityQueue()
    {
        MakeEmpty();
    }

    void MakeEmpty()
    {
        if (table != nullptr)
        {
            delete table;
            table = nullptr;
        }
    }

    void Insert(E x)
    {
        int i;
        if (isFull())
        {
            throw "PriorityQueue is Full";
        }
        // 上滤：从底部向上找合适位置
        for (i = ++table->size; i > 1 && x < table->Elements[i / 2]; i /= 2)
        {
            table->Elements[i] = table->Elements[i / 2];
        }
        table->Elements[i] = x;
    }

    E DeleteMin()
    {
        int i, child;
        E MinElement, LastElement;

        if (isEmpty())
        {
            throw "PriorityQueue is Empty";
        }

        MinElement = table->Elements[1];
        LastElement = table->Elements[table->size--];

        // 下滤
        for (i = 1; i * 2 <= table->size; i = child)
        {
            child = i * 2;
            // 找较小的子节点
            if (child != table->size &&
                table->Elements[child + 1] < table->Elements[child])
            {
                child++;
            }
            // 如果LastElement大于子节点，子节点上移
            if (LastElement > table->Elements[child])
            {
                table->Elements[i] = table->Elements[child];
            }
            else
            {
                break;
            }
        }
        table->Elements[i] = LastElement;
        return MinElement;
    }

    E FindMin()
    {
        if (isEmpty())
        {
            throw "PriorityQueue is Empty";
        }
        return table->Elements[1];
    }

    bool isEmpty() const
    {
        return table == nullptr || table->size == 0;
    }

    bool isFull() const
    {
        return table != nullptr && table->capacity == table->size;
    }
};
//用标准库和泛型
template<typename E>
class MyPriorityQueue
{
private:
    std::vector<E>heap;

    int size;

    std::function<bool(const E&, const E&)> comparator;

    int parent(int node)
    {
        return (node - 1) / 2;
    }
    int left(int node)
    {
        return node * 2 + 1;
    }
    int right(int node)
    {
        return node * 2 + 2;
    }
    void swap(int i, int j)
    {
        swap(heap[i], heap[j]);
    }
    void resize(int newsize)
    {
        if (newsize > size)
        {
            heap.resize(newsize);
        }
    }
    void swim(int node)
    {
        while (node > 0 && comparator(heap[parent[node]], heap[node]))
        {
            swap(parent[node], node);
            node = parent[node];
        }
    }
    void sink(int node)
    {
        while (left(node) < size || right(node) < size)
        {
            int min = node;
            if (left(node) < size && comparator(heap[min], heap[left(node)]))
            {
                min=left(node);
            }
            if (right(node) < size && comparator(heap[min], heap[right(node)]))
            {
                min=right(node);
            }
            if (min == node)
            {
                break;
            }
            swap(node, min);
            node = min;
        }
    }
public:
    MyPriorityQueue(int capacity, std::function<bool(const E&, const E&)> comparator)
        : heap(capacity), size(0), comparator(move(comparator)) {
    }
    int getSize() const
    {
        return size;
    }
    bool isEmpty() const
    {
        return size == 0;
    }
    const E& peek() const
    {
        if (isEmpty())
        {
            throw "PriorityQueue is Empty";
        }
        return heap[0];
    }
    void push(const E& x)
    {
        if (size == heap.size()) {
            resize(2 * heap.size());
        }
        heap[size] = x;
        swim(size);
        size++;
    }
    E pop()
    {
        if (isEmpty()) {
            throw "Priority queue underflow";
        }
        E res = heap[0];

        swap(0, size - 1);
        size--;
        sink(0);

        if (size > 0 && size == heap.size() / 4) {
            resize(heap.size() / 2);
        }
        return res;
    }
};
