#ifndef RBUFFER_H
#define RBUFFER_H

#include "ring_iterator.h"

template<typename T>
class ring_buffer
{
public:
	using valueType = T;
	using iterator	= ring_iterator<ring_buffer<T>>;

public:
	ring_buffer() {}
	ring_buffer(size_t size)
	{
		m_Size = size;
		m_Capacity = size + (size / 2);

		m_Buffer = new T[m_Capacity];
	}
	ring_buffer(size_t size, size_t start_index)
	{
		ring_buffer(size);
		set_head(start_index);
	}
	~ring_buffer()
	{
		clear();
		::operator delete(m_Buffer, m_Capacity * sizeof(T));
	}

	void append(const T& value)
	{
		m_Buffer[p_Head] = std::move(value);

		p_Head++;
		if (p_Head == m_Size) { p_Head = 0; }
	}

	void print()
	{
		/*std::cout << m_Buffer[p_Tail] << " ";
		for (auto ptr = &m_Buffer[p_Tail + 1]; ptr != &m_Buffer[p_Head]; ptr++) {
			if (ptr == &m_Buffer[m_Size]) { ptr = m_Buffer; }
			std::cout << *ptr << " ";
		}*/
	}

	void set_head(size_t index)
	{
		if (index > m_Size) {
			throw std::invalid_argument("Index must be less than ring size!");
		}
		p_Head = index;
	}

	void clear()
	{
		for (size_t i{}; i != m_Size; i++) {
			m_Buffer[i].~T();
		}

		m_Size = 0;
		p_Head = 0;
	}

	iterator head()
	{
		T* l_Coursor = m_Buffer + p_Head;
		T* l_Beg = m_Buffer;
		T* l_End = m_Buffer + (m_Size + 1);

		if (p_Head == 0) {
			return iterator(m_Buffer + p_Head,
				m_Buffer,
				m_Buffer + (m_Size + 1));
		}

		return iterator(m_Buffer + p_Head,
						m_Buffer,
						m_Buffer + m_Size);
	}

	iterator tail()
	{
		if (p_Head == 0) { 
			return iterator(m_Buffer + m_Size,
							m_Buffer,
							m_Buffer + (m_Size + 1));
		}

		return iterator(m_Buffer + (p_Head - 1),
						m_Buffer,
						m_Buffer + m_Size);
	}

	const T& operator[](size_t index) const { return m_Buffer[index]; }
	T& operator[](size_t index) { return m_Buffer[index]; }

	size_t getHead() const { return p_Head; }
	size_t size() const { return m_Size; }

private:
	T* m_Buffer = nullptr;

	size_t m_Size		= 0;
	size_t m_Capacity	= 0;

	size_t p_Head = 0;
};

#endif // !RBUFFER_H