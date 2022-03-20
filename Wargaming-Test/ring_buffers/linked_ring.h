#ifndef STATIC_RING_BUFFER_H
#define STATIC_RING_BUFFER_H

template<typename _Ty>
class linked_ring
{
public:
    using value_type = _Ty;
    using size_type = size_t;

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

public:
    class iterator
    {
    public:
        iterator(Node* node) : m_Node(node) {}

        void operator++() 
        {
            if (m_Node) {
                m_Node = m_Node->p_Next;
            }
        }


        bool operator==(const iterator& it) const
        {
            if (this == &it) {
                return true;
            }

            return m_Node == it.m_Node;
        }

        bool operator!=(const iterator& it) const
        {
            return !(*this == it);
        }

        _Ty operator*() const
        {
            if (m_Node) {
                return m_Node->m_Data;
            }
            return _Ty();
        }


    private:
        Node* m_Node;
    };

    iterator head()
    {
        return iterator(m_Head);
    }

    iterator tail()
    {
        return iterator(m_Tail);
    }

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
};

#endif // !STATIC_RING_BUFFER_H