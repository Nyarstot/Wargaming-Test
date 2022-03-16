#ifndef RING_ITERATOR_H
#define RING_ITERATOR_H

#include <iostream>

template <typename ring_buffer>
class ring_iterator
{
public:
	using valueType = typename ring_buffer::valueType;
	using iterator = typename ring_buffer::iterator;

	using pointerType = valueType*;
	using referenceType = valueType&;

public:

	ring_iterator(pointerType ptr, pointerType beg, pointerType end)
		: m_Ptr(ptr), p_Begin(beg), p_End(end)
	{
		
	}

	ring_iterator& operator++() {
		m_Ptr++;
		if (m_Ptr == p_End) {
			m_Ptr = p_Begin;
		}
		return *this;
	}
	ring_iterator operator++(int) { ring_iterator it = *this; ++(*this); return it; }
	ring_iterator& operator--() { m_Ptr--; return *this; }
	ring_iterator operator--(int) { ring_iterator it = *this; --(*this); return it; }
	ring_iterator operator+(const size_t& value) { m_Ptr += value; return *this; }

	referenceType operator[](int index) { return *(m_Ptr + index); }

	pointerType operator->() { return m_Ptr; }
	referenceType operator*() { return *m_Ptr; }

	bool operator==(const ring_iterator& it) const { return m_Ptr == it.m_Ptr; }
	bool operator!=(const ring_iterator& it) const { return !(*this == it); }

private:
	pointerType m_Ptr;

	pointerType p_Coursor;
	pointerType p_Begin;
	pointerType p_End;

};

#endif // !RING_ITERATOR_H

