//链表的懒惰实现
#include <vector>

template<typename E>
struct Node
{
    E val;
    Node* next;
    bool deleted;   // 【新增】懒惰删除标记位，默认未删除

    // 【新增】构造函数初始化列表，确保成员正确初始化
    Node() : next(nullptr), deleted(false) {}
    Node(const E& x) : val(x), next(nullptr), deleted(false) {}
};

template<typename E>
class List
{
private:
    Node<E>* Head;
    //下面的L即head。

public:
    // 【新增】构造函数，初始化头结点
    List() {
        Head = new Node<E>();
    }

    // 【新增】析构函数，确保内存不泄露
    ~List() {
        MakeEmpty(Head);
        delete Head;
    }

    Node<E>* MakeEmpty(Node<E>* L);

    // 【修改】判断是否为空链表（忽略已删除节点）
    bool isEmpty(Node<E>* L)
    {
        Node<E>* p = L->next;
        // 跳过所有标记为删除的节点
        while (p!=nullptr&&p->deleted)
        {
            p = p->next;
        }
        return p == nullptr;
    }

    // 【修改】判断是否为最后一个逻辑节点（忽略后面的已删除节点）
    bool isLast(Node<E>* L)
    {
        // 如果当前节点已删除，永远不应被视为最后一个逻辑节点
        if (L->deleted) return false;

        Node<E>* p = L->next;
        while (p != nullptr && p->deleted) {
            p = p->next;
        }
        return p == nullptr;
    }

    // 【修改】查找：遇到已删除节点直接跳过，不视为匹配
    Node<E>* Find(E x, Node<E>* L)
    {
        if (isEmpty(L))
        {
            throw "List is Empty";
        }
        Node<E>* p = L->next;
        while (p != nullptr)
        {
            if (!p->deleted && p->val == x)
            {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    // 【新增】懒惰删除：仅打标记，不释放内存
    void LazyDelete(E x, Node<E>* L)
    {
        Node<E>* p = Find(x, L);
        if (p != nullptr&&!p->deleted)
        {
            p->deleted = true;
        }
    }

    // 【原物理删除】保留但改为私有或注释掉，建议使用 LazyDelete 替代
    /*
    void Delete(E x, Node<E>* L)
    {
        Node<E>* p = Findprevious(x, L);
        if (p == nullptr || p->next == nullptr)
        {
            return;
        }
        else
        {
            Node<E>* temp = p->next;
            p->next = p->next->next;
            delete temp;
        }
    }
    */

    Node<E>* Findprevious(E x, Node<E>* L)
    {
        Node<E>* p = L;
        while (p->next != nullptr)
        {
            if (p->next->val==x && !p->next->deleted)
            {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    void insert(E x, Node<E>* L)
    {
        Node<E>* temp = new Node<E>(x);
        temp->next = L->next;
        L->next = temp;
    }

    // 【新增】物理清理函数：遍历链表，真正释放所有 deleted == true 的节点
    void PurgeDeleted(Node<E>* L)
    {
        Node<E>* prev = L;
        Node<E>* curr = L->next;
        while (curr != nullptr)
        {
            if (curr->deleted)
            {
                prev->next = curr->next;
                delete curr;
                curr = prev->next;
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    // 【原 DeleteList】保留作为全量删除
    void DeleteList(Node<E>* L)
    {
        Node<E>* p = L->next;
        Node<E>* temp;
        while (p != nullptr)
        {
            temp = p->next;
            delete p;
            p = temp;
        }
        L->next = nullptr;
    }

    Node<E>* Header(Node<E>* L)
    { 
        return Head;
    }

    // 【修改】返回第一个未删除的节点
    Node<E>* First(Node<E>* L)
    {
        Node<E>* p = L->next;
        while (p != nullptr)
        {
            if (!p->deleted)
            {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    // 【修改】返回下一个未删除的节点
    Node<E>* Advance(Node<E>* L)
    {
        if (L == nullptr) return nullptr;
        Node<E>* p = L->next;
        while (p != nullptr && p->deleted) {
            p = p->next;
        }
        return p;
    }

    E Retrieve(Node<E>* P)
    {
        return P->val;
    }

    // 【修改】打印函数：只输出未被删除的节点
    std::vector<E> PrintList()
    {
        std::vector<E>res;
        Node<E>* p = Head->next;
        while (p != nullptr)
        {
            if (p->deleted)
            {
                p = p->next;
            }
            else
            {
                res.push_back(p->val);
                p = p->next;
            }
        }
        return res;
    }

    // 【新增】获取逻辑长度（不计入已删除节点）
    int GetLogicalSize()
    {
        int size = 0;
        Node<E>* p = Head->next;
        while (p != nullptr)
        {
            if (p->deleted)
            {
                p = p->next;
           }
            else
            {
                size++;
                p = p->next;
            }
        }
        return size;
    }

    // 【新增】获取物理长度（包含已删除节点）
    int GetPhysicalSize()
    {
        int size = 0;
        Node<E>* p = Head->next;
        while (p != nullptr)
        {
            size++;
            p = p->next;
        }
        return size;
    }
};

// 【实现 MakeEmpty】需要清理头结点之后的所有节点
template<typename E>
Node<E>* List<E>::MakeEmpty(Node<E>* L)
{
    DeleteList(L);
    return L;
}