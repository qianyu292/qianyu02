template<typename E>
struct Node
{
    E val;
    Node* next; 
    Node* prev;  // 新增前驱指针
};

template<typename E>
class List
{
private:
    Node<E>* Head;
    Node<E>* Tail;  // 新增尾指针

public:
    // 构造函数
    List()  
    {
        Head = new Node<E>();
        Tail = new Node<E>();
        Head->next = Tail;
        Head->prev = nullptr;
        Tail->prev = Head;
        Tail->next = nullptr; 
    }

    // 析构函数
    ~List()
    {
        DeleteList(Head);
        delete Head;
        delete Tail;
    }

    // 清空链表
    void MakeEmpty()
    {
        Node<E>* p=Head->next;
        Node<E>* temp;
        while (p != Tail)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
        Head->next = Tail;
        Tail->prev = Head;
    }

    // 判断是否为空
    bool isEmpty()const
    {
        return Head->next == Tail;
    }

    // 判断是否为最后一个节点
    bool isLast(Node<E>*L)const
    {
        return L->next == Tail;
    }

    // 查找值为x的节点
    Node<E>* Find(E x)
    {
        Node<E>* p = Head->next;
        while (p != Tail && p->val != x)
        {
            p = p->next;
        }
        return (p != Tail) ? p : nullptr;
    }

    // 删除值为x的节点
    void Delete(E x)
    {
        Node<E>* p = Find(x);
        if (p == nullptr)
        {
            return;
        }
        if (p->prev != nullptr)
        {
            p->prev->next = p->next;
        }
        if (p->next != nullptr)
        {
            p->next->prev = p->prev;
        }
        /*if (p == Tail)
        {
            Tail = p->prev;
        }*/
        delete p;
    }

    // 查找值为x的节点的前驱
    Node<E>* Findprevious(E x)
    {
        Node<E>* p = Find(x);
        if (p != nullptr)
        {
            return p->prev;
        }
        else
        {
            return nullptr;
        }
    }

    // 在指定位置后插入节点
    void insert(E x, Node<E>* L)
    {
        if (L == nullptr)return;
        Node<E>* temp = new Node<E>();
        temp->val = x;

        Node<E>* temp2 = L->next;

        L->next = temp;
        temp->prev = L;

        temp->next = temp2;
        if (temp2 != nullptr)
        {
            temp2->prev = temp;
        }
    }

    // 在链表头部插入
    void insertFront(E x)
    {
        Node<E>* newnode = new Node<E>();
        newnode->val = x;

        Node<E>* temp = Head->next;

        newnode->prev = Head;
        Head->next = newnode;

        newnode->next = temp;
        if (temp != nullptr)
        {
            temp->prev = newnode;
        }
    }

    // 在链表尾部插入
    void insertBack(E x)
    {
        Node<E>* newnode = new Node<E>();
        newnode->val = x;

        Node<E>* temp = Tail->prev;
        
        newnode->next = Tail;
        Tail->prev = newnode;

        newnode->prev = temp;
        if (temp != nullptr)
        {
            temp->next = newnode;
        }
        else
        {
            Head->next = newnode;
        }
    }

    // 删除指定节点
    void DeleteNode(Node<E>* p)
    {
        if (p == nullptr)return;
        if (p->prev != nullptr)
        {
            p->prev->next = p->next;
        }
        if (p->next != nullptr)
        {
            p->next->prev = p->prev;
        }
        delete p;
    }

    // 删除整个链表
    void DeleteList(Node<E>* L)
    {
        Node<E>* p=L->next;
        Node<E>* temp;
        while (p != Tail)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
        L->next = Tail;
        Tail->prev = L;
    }

    // 获取头节点
    Node<E>* Header()const
    {
        return Head;
    }

    // 获取第一个节点
    Node<E>* First()const
    {
        return (Head->next != Tail) ? Head->next : nullptr;
    }

    // 获取最后一个节点
    Node<E>* Last()const
    {
        return (Tail->prev != Head) ? Tail->prev : nullptr;
    }

    // 前进到下一个节点
    Node<E>* Advance(Node<E>* L)const
    {
        return (L!=nullptr&&L->next!=Tail)?L->next:nullptr;
    }

    // 后退到前一个节点
    Node<E>* Retreat(Node<E>* L)const
    {
        return (L != nullptr && L->prev!=Head)?L->prev:nullptr;
    }

    // 获取节点的值
    E Retrieve(Node<E>* P)const
    {
        return P->val;
    }

    // 获取头指针
    Node<E>* getHead() const
    {
        return Head;
    }

    // 获取尾指针
    Node<E>* getTail() const
    {
        return Tail;
    }

    // 获取链表长度
    int size() const
    {
        Node<E>* p = Head->next;
        int step = 0;
        while (p != Tail)
        {
            p = p->next;
            step++;
        }
        return step;
    }
};