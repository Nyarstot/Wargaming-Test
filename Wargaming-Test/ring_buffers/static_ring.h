#ifndef STATIC_RING_H
#define STATIC_RING_H

#include <stdexcept>


/////////////////////////////////////
/// STATIC_RING_ITERATOR
/////////////////////////////////////

template<typename static_ring, unsigned _Sze>
class static_ring_iterator
{
public:
    using value_type    = typename static_ring::value_type;
    using iterator      = typename static_ring::iterator;

    using pointer_type   = value_type*;
    using reference_type = value_type&;

public:
    static_ring_iterator() noexcept {}

    static_ring_iterator(size_t count)
        : m_Count(count)
    {
    }

    static_ring_iterator(pointer_type ptr, size_t& count, pointer_type begin, pointer_type end)
        : m_Ptr(ptr), m_Count(count), m_Begin(begin), m_End(end)
    {
    }

    static_ring_iterator& operator++()
    {
        ++m_Ptr;
        ++m_Count;

        if (m_Ptr == m_End) {
            m_Ptr = m_Begin;
        }

        return *this;
    }

    static_ring_iterator& operator++(int)
    {
        static_ring_iterator it = *this;
        ++(*this);
        return it;
    }

    pointer_type operator->() { return *m_Ptr;; }
    reference_type operator*() { return *m_Ptr; }

    bool operator==(const static_ring_iterator& it) const { return m_Count == it.m_Count; }
    bool operator!=(const static_ring_iterator& it) const { return !(*this == it); }

private:
    pointer_type m_Ptr = nullptr;

    size_t m_Count = 0;

    pointer_type m_Begin = nullptr;
    pointer_type m_End = nullptr;
};

/////////////////////////////////////
/// STATIC_RING
/////////////////////////////////////

/*
* static_ring is the ring buffer class with constant size.
* Unlike its dynamic counterpart, static_ring don't throw
* an exception when the ring buffer is full, it just starts
* overwriting data above already exists in the ring buffer.
* 
* Like ring_buffer, the size of static_ring is size + 1 to
* get data from the buffer without losing the last byte.
* 
* for example:
* 
* t         h        h t
* 0 1 2 3 4 5  ->  0 1 2 3 4 5
* 1 2 3 4 5 x      6 7 4 5 6 x
* 
*/

template<typename _Ty, unsigned _Sze>
class static_ring
{
public:
    using value_type = _Ty;
    using iterator = static_ring_iterator<static_ring<_Ty, _Sze>, _Sze>;

public:
    static_ring() {}
    ~static_ring()
    {
        clear();
    }

    void push_back(const _Ty& value)
    {
        m_Buffer[m_Head] = std::move(value);
        m_Head = next_index(m_Head, _Sze);
        
        if (full()) { m_Tail = next_index(m_Tail, _Sze); }
        if (m_Counter < _Sze) { m_Counter++; }
    }

    template<typename _Va>
    void emplace_back(_Va&& args)
    {
        m_Counter++;
        m_Buffer[m_Head] = std::forward<_Va>(args);
        m_Head = next_index(m_Head, _Sze);

        if (full()) { m_Tail = next_index(m_Tail, _Sze); }
        if (m_Counter < _Sze) { m_Counter++; }
    }

    void pop()
    {
        m_Tail = (m_Tail + 1) % _Sze;
        m_Counter--;
    }

    _Ty pop_return() 
    {
        _Ty tmp = m_Buffer[m_Tail];
        pop();

        return tmp;
    }

    void clear()
    {
        if (m_Counter == 0) { return; }

        for (size_t i{}; i < _Sze; i++) {
            m_Buffer[i].~_Ty();
        }

        m_Counter = 0;
        m_Head = m_Tail = 0;
    }

    iterator begin()
    {
        return iterator(m_Buffer + m_Tail, m_Car, m_Buffer, m_Buffer + _Sze);
    }

    iterator last_element()
    {
        return iterator(m_Counter);
    }

    bool empty() const { return m_Counter == 0; }
    bool full() const { return m_Counter == _Sze; }
    size_t size() const { return _Sze; }

    const _Ty& operator[](size_t index) const { return m_Buffer[index]; }
    _Ty& operator[](size_t index) { return m_Buffer[index]; }

private:
    _Ty m_Buffer[_Sze + 1];

    size_t m_Car = 0;
    size_t m_Counter = 0;

    size_t m_Head = 0;
    size_t m_Tail = 0;

private:
    _NODISCARD static size_t next_index(size_t curr_index, size_t size) noexcept
    {
        return (curr_index + 1) % size;
    }

};

#endif // !STATIC_RING_H

