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
    List() :head(nullptr), tail(nullptr) {};

    // 析构函数
    ~List();

    // 清空链表
    Node<E>* MakeEmpty(Node<E>* L)
    {
        
    }

    // 判断是否为空
    bool isEmpty(Node<E>* L)
    {
        return L->next == nullptr;
    }

    // 判断是否为最后一个节点
    bool isLast(Node<E>* L)
    {
        return L->next == nullptr;
    }

    // 查找值为x的节点
    Node<E>* Find(E x, Node<E>* L);

    // 删除值为x的节点
    void Delete(E x, Node<E>* L);

    // 查找值为x的节点的前驱
    Node<E>* Findprevious(E x, Node<E>* L);

    // 在指定位置后插入节点
    void insert(E x, Node<E>* L);

    // 在链表头部插入
    void insertFront(E x);

    // 在链表尾部插入
    void insertBack(E x);

    // 删除指定节点
    void DeleteNode(Node<E>* p);

    // 删除整个链表
    void DeleteList(Node<E>* L);

    // 获取头节点
    Node<E>* Header(Node<E>* L);

    // 获取第一个节点
    Node<E>* First(Node<E>* L);

    // 获取最后一个节点
    Node<E>* Last();

    // 前进到下一个节点
    Node<E>* Advance(Node<E>* L);

    // 后退到前一个节点
    Node<E>* Retreat(Node<E>* L);

    // 获取节点的值
    E Retrieve(Node<E>* P);

    // 获取头指针
    Node<E>* getHead() const;

    // 获取尾指针
    Node<E>* getTail() const;

    // 获取链表长度
    int size() const;
};