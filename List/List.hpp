#include <cassert>

template <typename T>

struct Node
{
    T value;
    Node<T>* next;

    Node (T v, Node<T>* h):
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

    void pushFront(T pValue)
    {
        head = new Node<T>(pValue, head);
    }

    T popFront()
    {
        assert(head);

        Node<T>* newHead = head->next;
        T value = head->value;
        delete head;
        head = newHead;

        return value;
    }

    int len()
    {
        if (!head)
            return 0;

        int res = 0;
        Node<T>* pCurrentNode = head;

        while(true)
        {
            res++;

            pCurrentNode = pCurrentNode->next;
            if (!pCurrentNode)
                break;
        }

        return res;
    }

	T removeByIndex(const int index)
	{
		Node<T>* pointer = head;
		for (int i = 0; i < index - 1; ++i)
		{
			assert(pointer);
			pointer = pointer->next;
		}
		Node<T>* newHead = pointer->next->next;
		T newList = pointer->next->value;
		delete pointer->next;
		pointer->next = newHead;
		return newList;
	}


	T insert(int index)
	{
		Node<T>* pointer = head;
		for (int i = 0; i < index; ++i)
		{
			assert(head);
			pointer = head->next;
		}
		T newList = pointer->value;
		return newList;
	}

	void erase()
    {
        for (int i = this->len(); i > 0; i--)
        {
            Node<T>* pointer = head;

        	for (int j = 1; j < i; j++)
        	{
            	p_res = p_res->next;
			}			
			
			delete this->p_res;
        }
        
        head = nullptr;
    }

	List append(List<T> list)
	{
		List<T> newList;
		Node<T>* pointer = head;
		while(pointer)
		{
			newList.pushFront(pointer->value);
			pointer = pointer->next;
		}
		pointer = list.head;
		while (pointer)
		{
			newList.pushFront(pointer->value);
			pointer = pointer->next;
		}
		return newList;
	}

	void operator += (List<T> list)
	{
		Node<T>* pointer = head;
		while (pointer)
		{
			pointer = pointer->next;
		}
		pointer = list.head;
		while (pointer)
		{
			this->pushFront(pointer->value);
			pointer = pointer->next;
		}
	}
};