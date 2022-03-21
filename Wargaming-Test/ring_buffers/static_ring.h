#ifndef STATIC_RING_H
#define STATIC_RING_H

#include <initializer_list>
#include <stdexcept>

template<typename _Ty, unsigned _Sze>
class static_ring
{
public:
    static_ring() {}
    ~static_ring() 
    {
       
    }

    void push_back(const _Ty& value)
    {
        m_Buffer[m_Head] = sdt::move(value);
        m_Head = (m_Head + 1) % _Sze;

        m_Counter++;
    }

    template<typename _Va>
    void emplace_back(_Va&& args)
    {
        m_Counter++;
        m_Buffer[m_Head] = std::forward<_Va>(args);
        m_Head = (m_Head + 1) % _Sze;
    }

    void pop()
    {
        m_Tail = (m_Tail + 1) % _Sze;
        m_Counter--;
    }

    const _Ty& operator[](size_t index) const { return m_Buffer[index]; }
    _Ty& operator[](size_t index) { return m_Buffer[index]; }

private:
    _Ty m_Buffer[_Sze + 1];

    size_t m_Counter = 0;

    size_t m_Head = 0;
    size_t m_Tail = 0;
};

#endif // !STATIC_RING_H

