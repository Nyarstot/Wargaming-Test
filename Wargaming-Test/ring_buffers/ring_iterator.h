#ifndef RING_ITERATOR_H
#define RING_ITERATOR_H

template <typename ring_buffer>
class ring_iterator
{
public:
	using valueType = typename ring_buffer::valueType;
	using iterator = typename ring_buffer::iterator;

	using pointerType = valueType*;
	using referenceType = valueType&;

public:

	ring_iterator(pointerType ptr, size_t bufferSize, pointerType beg, pointerType end)
		: m_Ptr(ptr), m_BufferSize(bufferSize), p_Begin(beg), p_End(end)
	{
	}

	ring_iterator& operator++() {
		m_Ptr++;
		if (m_Ptr == p_End) {
			m_Ptr = p_Begin;
		}

		return *this;
	}

	ring_iterator operator++(int) { 
		ring_iterator it = *this; 
		++(*this); return it; 
	}

	ring_iterator& operator--() { 
		m_Ptr--; 
		if (m_Ptr == p_Begin) {
			m_Ptr = p_End;
		}

		return *this; 
	}

	ring_iterator operator--(int) { 
		ring_iterator it = *this; 
		--(*this); return it; 
	}

	ring_iterator operator+(const int& value) { 
		int newPosition = (value + std::distance(p_Begin, m_Ptr)) % m_BufferSize;
		m_Ptr = p_Begin + newPosition;

		return *this; 
	}

	ring_iterator operator-(const int& value) {
		int l_Distance = static_cast<int>(std::distance(p_Begin, m_Ptr)) - value;

		if (l_Distance < 0) {
			int newPosition = l_Distance - m_BufferSize * (-abs(l_Distance / static_cast<int>(m_BufferSize)) - 1);
			m_Ptr = p_Begin + newPosition;

			return *this;
		}

		m_Ptr = p_Begin + l_Distance;
		return *this;
	}

	referenceType operator[](int index) { return *(m_Ptr + index); }

	pointerType operator->() { return m_Ptr; }
	referenceType operator*() { return *m_Ptr; }

	bool operator==(const ring_iterator& it) const { return m_Ptr == it.m_Ptr; }
	bool operator!=(const ring_iterator& it) const { return !(*this == it); }
	bool operator<(const ring_iterator& it) const { return m_Ptr < it.m_Ptr; }

private:
	pointerType m_Ptr;

	size_t m_BufferSize = 0;

	pointerType p_Begin = 0;
	pointerType p_End = 0;

};

#endif // !RING_ITERATOR_H

