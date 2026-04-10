template<typename E>
struct Node
{
    E val;
    Node* next;
};
template<typename E>
class deque
{
private:
    Node<E>* head;
    Node<E>* tail;

public:
    deque()
    {
        head = new Node<E>();
        head->next = nullptr;
        tail = head;
    }
    ~deque()
    {
        MakeEmpty();
        delete head;
    }

    bool isEmpty()
    {
        return head->next == nullptr;
    }
    void MakeEmpty()
    {
        if (isEmpty())
        {
            return;
        }
        Node<E>* p = head->next;
        while (p != nullptr)
        {
            Node<E>* temp = p->next;
            delete p;
            p = temp;
        }
        tail = head;
    }

    void push_front(const E& x)
    {
        if (isEmpty())
        {
            Node<E>* newnode = new Node<E>();
            newnode->val = x;
            head->next = newnode;
            tail = newnode;
            return;
        }
        Node<E>* newnode = new Node<E>();
        newnode->val = x;
        newnode->next = head->next;
        head->next = newnode;
    }
    void push_back(const E& x)
    {
        Node<E>* newnode = new Node<E>();
        newnode->val = x;
        tail->next = newnode;
        tail = newnode;
    }

    void pop_front()
    {
        if (isEmpty())
        {
            throw "queue is Empty";
        }
        Node<E>* temp = head->next;
        if (tail == temp)
        {
            tail = head;
            delete temp;
            return;
        }
        head->next = temp->next;
        delete temp;
    }
    void pop_back()
    {
        if (isEmpty())
        {
            throw "deque is Empty";
        }
        Node<E>* p = head;
        while (p->next != tail)
        {
            p = p->next;
        }
        Node<E>* temp = tail;
        tail = p;
        tail->next = nullptr;
        delete temp;
    }

    E front() const
    {
        if (isEmpty())
            throw "deque is empty";
        return head->next->val;
    }
    E back() const
    {
        if (isEmpty())
            throw "deque is empty";
        return tail->val;
    }

    E pop_front_val()
    {
        if (isEmpty())
        {
            throw "queue is Empty";
        }
        Node<E>* temp = head->next;
        if (tail == temp)
        {
            tail = head;
            E oldval = temp->val;
            delete temp;
            return oldval;
        }
        head->next = temp->next;
        E oldval = temp->val;
        delete temp;
        return oldval;
    }
    E pop_back_val()
    {
        if (isEmpty())
        {
            throw "deque is Empty";
        }
        Node<E>* p = head;
        while (p->next != tail)
        {
            p = p->next;
        }
        Node<E>* temp = tail;
        tail = p;
        E oldval = temp->val;
        delete temp;
        return oldval;
    }
};