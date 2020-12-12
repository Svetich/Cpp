#include <cassert>
#include <iostream>

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

	List(const List<T>& list)
	{
		head = NULL;
		Node<T>* pointer = list.head;
		while (pointer)
		{
			this->pushFront(pointer->value);
			pointer = pointer->next;
		}
	}

	~List()
	{
		Node<T>* pointer = head;
		while (pointer)
		{
			Node<T>* newPointer = pointer->next;
			delete pointer;
			pointer = newPointer;
		}
	}

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
		if (pointer->next != nullptr)
		{
			Node<T>* newHead = pointer->next->next; 
			T newList = pointer->next->value; 
			delete pointer->next;
			pointer->next = newHead;
			return newList;		
		}
		else
		{
			Node<T>* newHead = NULL;
			T newList = NULL; 
			delete pointer->next;
			pointer->next = newHead;
			return newList;
		}			
	}

	T insert(int index)
	{
		Node<T>* pointer = head;
		for (int i = 0; i < index; ++i)
		{
			assert(head);
			pointer = pointer->next;
		}
		T newList = pointer->value;
		return newList;
	}

	void erase()
    {
        while(true)
		{
			popFront();
		}
    }

	List operator + (List<T> list)
	{
		List<T> newList;
		Node<T>* pointer = head;
		while(pointer)
		{
			newList.pushFront(pointer->value);
			pointer = pointer->next;
		}
		pointer = list.head;
		while(pointer)
		{
			newList.pushFront(pointer->value);
			pointer = pointer->next;
		}
		return newList;
	}

	void operator += (List<T> list)
	{
		Node<T>* pointer = head;
		while(pointer)
		{
			pointer = pointer->next;
		}
		pointer = list.head;
		while(pointer)
		{
			this->pushFront(pointer->value);
			pointer = pointer->next;
		}
	}
};