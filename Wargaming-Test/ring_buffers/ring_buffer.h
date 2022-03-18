#ifndef RBUFFER_H
#define RBUFFER_H

#include <initializer_list>
#include "ring_iterator.h"

template<typename T>
class ring_buffer
{
public:
	using value_type	= T;
	using iterator		= ring_iterator<ring_buffer<T>>;

public:
	ring_buffer(size_t size)
		: m_Size(size), m_Capacity(size + 1)
	{
		m_Buffer = new T[m_Capacity];
	}
	ring_buffer(size_t size, size_t index)
		: m_Size(size), m_Capacity(size + 1), m_Head(index), m_Tail(index)
	{
		m_Buffer = new T[m_Capacity];
		set_head(index);
	}
	~ring_buffer()
	{
		clear();
		::operator delete(m_Buffer, m_Capacity * sizeof(T));
	}

	void push_head(const T& value)
	{
		m_Buffer[m_Head] = std::move(value);

		++m_Head;
		if (m_Head == m_Size) {
			m_Head = 0;
		}

		if (m_Head == m_Tail) {
			m_Tail++;
			if (m_Tail == m_Size) {
				m_Tail = 0;
			}
		}
	}

	void push_tail(const T& value)
	{
		m_Buffer[m_Tail] = std::move(value);

		--m_Tail;
		if (m_Tail == 0) {
			m_Tail = m_Size - 1;
		}

		if (m_Tail == m_Head) {
			--m_Head;
			if (m_Head == 0) {
				m_Head = m_Size - 1;
			}
		}
	}

	void clear()
	{
		for (size_t i{}; i != m_Size; i++) {
			m_Buffer[i].~T();
		}

		m_Size = 0;
		m_Head = 0;
		m_Tail = 0;
	}

	void set_head(size_t index)
	{
		if (index > m_Size) {
			throw std::invalid_argument("Index must be less than ring size");
		}

		m_Head = index;
	}

	size_t get_head()
	{
		return m_Head;
	}

	void set_tail(size_t index)
	{
		if (index > m_Size) {
			throw std::invalid_argument("Index must be less than ring size");
		}

		m_Tail = index;
	}

	size_t get_tail()
	{
		return m_Tail;
	}

	bool empty()
	{
		return m_Tail == m_Head;
	}

	bool full()
	{
		return m_Head++ == m_Tail;
	}

	size_t size()
	{
		return m_Size;
	}

	size_t capacity()
	{
		return m_Capacity;
	}

	iterator head()
	{
		return iterator(m_Buffer + m_Head, m_Size,
						m_Buffer, m_Buffer + m_Size);
	}

	iterator tail()
	{
		return iterator(m_Buffer + m_Tail, m_Size,
						m_Buffer, m_Buffer + m_Size);
	}

	const T& operator[](size_t index) const
	{
		return m_Buffer[index];
	}

	T& operator[](size_t index)
	{
		return m_Buffer[index];
	}

private:
	T* m_Buffer			= nullptr;

	size_t m_Size		= 0;
	size_t m_Capacity	= 0;

	size_t m_Head		= 0;
	size_t m_Tail		= 0;

};

#endif // !RBUFFER_H


