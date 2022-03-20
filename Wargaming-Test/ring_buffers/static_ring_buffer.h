#ifndef STATIC_RING_BUFFER_H
#define STATIC_RING_BUFFER_H

/*
m_Buffer[m_Head] = value;
        m_Head = (m_Head + 1) % m_Size;
*/

template<typename _Ty, unsigned _Sze>
class static_ring
{
public:
    using value_type    = _Ty;
    using size_type     = size_t;
    //using iterator      = static_ring_iterator<static_ring< _Ty, _Sze>, _Sze>;

public:
    static_ring() 
    {
        m_Size = _Sze;

        m_Tail = 0;
        m_Head = 0;
    }
    ~static_ring()
    {

    }

    void push(const _Ty& value)
    {
    }

private:
    Node* m_Head = nullptr;
    Node* m_Tail = nullptr;

    size_t m_ElemCount = 0;

    size_type m_Size = _Sze;
    size_type m_Carriage = 1;

private:
    _NODISCARD static index_type next_index(index_type index, index_type size_index) noexcept
    {
        index++;
        return index >= size_index ? 0 : index;
    }

private:
    struct Node
    {
        _Ty m_Data;
        node* p_Next;

        Node(_Ty value) : data(value), next(nullptr) {}
    };
};

#endif // !STATIC_RING_BUFFER_H

