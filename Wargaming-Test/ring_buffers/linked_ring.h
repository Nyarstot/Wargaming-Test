#ifndef STATIC_RING_BUFFER_H
#define STATIC_RING_BUFFER_H

/*
m_Buffer[m_Head] = value;
        m_Head = (m_Head + 1) % m_Size;
*/

#include <iostream>

template<typename linked_ring>
class linked_ring_iterator
{
public:
    using value_type = typename linked_ring::value_type;
    //using node_type  = typename linked_ring::node_type;
    using iterator   = typename linked_ring::iterator;

    using pointer_type   = value_type*;
    using reference_type = value_type&;

public:
    linked_ring_iterator() {}

private:

};

template<typename _Ty>
class linked_ring
{
public:
    using value_type    = _Ty;
    using size_type     = size_t;
    using iterator      = linked_ring_iterator<linked_ring<_Ty>>;

public:
    linked_ring() 
    {
    }
    ~linked_ring()
    {
    }

    void append(const _Ty& value)
    {
        m_Size++;
        m_ElemCount++;

        Node* tmp = new Node;
        tmp->p_Next = m_Head;
        tmp->m_Data = value;

        if (m_Head) {
            m_Tail->p_Next = tmp;
            m_Tail = tmp;
        }
        else
        {
            m_Head = m_Tail = tmp;
        }
    }

    void remove_tail()
    {
        if (m_Head) {
            Node* newHead = m_Head->p_Next;

            ::operator delete(m_Head, sizeof(value_type));
            m_Head = newHead;
        }
    }

    void show() 
    {
        Node* tmp = m_Head;

        for (size_t i = m_ElemCount; i != 0; i--) {
            std::cout << tmp->m_Data << " ";
            tmp = tmp->p_Next;
        }
    }

    iterator head()
    {

    }

    iterator tail()
    {

    }


private:
    size_t m_ElemCount = 0;

    size_type m_Size = 0;
    size_type m_Carriage = 0;

private:
    struct Node
    {
    public:
        _Ty m_Data;
        Node* p_Next;

        Node() {}
        Node(_Ty value) : m_Data(value), p_Next(nullptr) {}
    };

    Node* m_Head = nullptr;
    Node* m_Tail = nullptr;
};

#endif // !STATIC_RING_BUFFER_H

