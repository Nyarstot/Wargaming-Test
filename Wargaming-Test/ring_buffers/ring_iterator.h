#ifndef RING_ITERATOR_H
#define RING_ITERATOR_H

template<typename ring_buffer>
class ring_iterator
{
public:
	using value_type = typename ring_buffer::value_type;
	using iterator = typename ring_buffer::iterator;

	using pointer_type = value_type*;
	using reference_type = value_type&;

public:
	ring_iterator(pointer_type ptr, size_t buffer_size, pointer_type begin, pointer_type end)
		: p_Ptr(ptr), m_buffer_size(buffer_size), p_Begin(begin), p_End(end)
	{
	}

	ring_iterator& operator++()
	{
		p_Ptr++;
		if (p_Ptr == p_End) {
			p_Ptr = p_Begin;
		}

		return *this;
	}

	ring_iterator operator++(int)
	{
		ring_iterator it = *this;
		++(*this);

		return it;
	}

	ring_iterator& operator--()
	{
		p_Ptr--;
		if (p_Ptr == p_Begin) {
			p_Ptr = p_End;
		}

		return *this;
	}

	ring_iterator operator--(int)
	{
		ring_iterator it = *this;
		--(*this);

		return it;
	}

	ring_iterator operator+(const int& value)
	{
		int newPosition = (value + std::distance(p_Begin, p_Ptr)) % m_buffer_size;
		p_Ptr = p_Begin + newPosition;

		return *this;
	}

	ring_iterator operator-(const int& value)
	{
		int l_Distance = std::distance(p_Begin, p_Ptr) - value;

		if (l_Distance < 0) {
			int newPosition = l_Distance - m_buffer_size * (-abs(l_Distance / m_buffer_size) - 1);
			p_Ptr = p_Begin + newPosition;

			return *this;
		}

		p_Ptr = p_Begin + l_Distance;
		return *this;
	}

	reference_type operator[](int index) { return *(p_Ptr + index); }

	pointer_type operator->() { return p_Ptr; }
	reference_type operator*() { return *p_Ptr; }

	bool operator==(const ring_iterator& it) const { return p_Ptr == it.p_Ptr; }
	bool operator!=(const ring_iterator& it) const { return !(*this == it); }

private:
	size_t m_buffer_size	= 0;

	pointer_type p_Ptr		= nullptr;
	pointer_type p_Begin	= nullptr;
	pointer_type p_End		= nullptr;

};

#endif // !RING_ITERATOR_H
