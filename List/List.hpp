template <typename T>

struct Node
{
    T* value;
    Node<T>* next;

    Node (T* v, Node<T>* h):
        value(v),
        next(h)
    {}
};

template <typename T>

class List
{
public:
    Node<T>* head;
    Node<T>* currentIndex;

public:
    List ():
        head(nullptr),
        currentIndex(nullptr)
    {}

    void pushFront(T* pValue)
    {
        head = new Node<T>(pValue, head);
    }

    T* popFront()
    {
        assert(head);

        Node<T>* newHead = head->next;
        T* value = head->value;
        delete head;
        head = newHead;

        return value;
    }

    int length()
    {
        if (!head)
            return 0;

        int res = 0;
        Node<T>* pCurrentNode = head;

        for (;;)
        {
            res++;

            pCurrentNode = pCurrentNode->next;
            if (!pCurrentNode)
                break;
        }

        return res;
    }
};