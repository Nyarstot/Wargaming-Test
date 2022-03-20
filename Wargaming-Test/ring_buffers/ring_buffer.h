#ifndef RBUFFER_H
#define RBUFFER_H

#include <xmemory>

template<typename ring_buffer>
class ring_iterator
{
public:
	using value_type	= typename ring_buffer::value_type;
	using iterator		= typename ring_buffer::iterator;

	using pointer_type		= value_type*;
	using reference_type	= value_type&;

public:
	ring_iterator() noexcept {}
	ring_iterator(pointer_type ptr, pointer_type begin, pointer_type end) noexcept
		: m_Ptr(ptr), m_Begin(begin), m_End(end)
	{
	}

	ring_iterator& operator++()
	{
		m_Ptr++;
		if (m_Ptr >= m_End) {
			m_Ptr = m_Begin;
		}
		return *this;
	}

	ring_iterator& operator++(int)
	{
		ring_iterator it = *this;
		++(*this);
		return it;
	}

	ring_iterator& operator--()
	{
		m_Ptr--;
		if (m_Ptr <= m_Begin) {
			m_Ptr = m_End;
		}
		return *this;
	}

	ring_iterator& operator--(int)
	{
		ring_iterator it = *this;
		--(*this);
		return it;
	}

	reference_type operator[](size_t index) { return *(m_Ptr + index); }

	pointer_type operator->() { return m_Ptr; }
	reference_type operator*() { return *m_Ptr; }

	bool operator==(const ring_iterator& it) const { return m_Ptr == it.m_Ptr; }
	bool operator!=(const ring_iterator& it) const { return !(*this == it); }

private:
	pointer_type m_Ptr = nullptr;

	pointer_type m_Begin = nullptr;
	pointer_type m_End = nullptr;
};

template<typename _Ty, class _Alloc = std::allocator<_Ty>>
class ring_buffer
{
public:
	using value_type = _Ty;
	using index_type = size_t;

	using _Alty = _Alloc;
	using _Alty_traits = std::allocator_traits<_Alty>;

	using iterator = ring_iterator<ring_buffer<_Ty,_Alty>>;

public:
	ring_buffer() noexcept
	{
		m_Buffer = nullptr;

		m_Size = 0;
		m_Capacity = 0;

		m_Head = 0;
		m_Tail = 0;

		m_Alloc = _Alty;
	}

	explicit ring_buffer(size_t size, const _Alty& allocator = _Alty())
	{
		m_Head = 0;
		m_Tail = 0;

		m_Size = size;
		m_Capacity = size + 1;

		m_Alloc = allocator;

		m_Buffer = m_Alloc.allocate(m_Capacity);
		set_to_null(m_Buffer, m_Size);
	}

	~ring_buffer()
	{
		clear();
		m_Alloc.deallocate(m_Buffer, m_Capacity);
	}

	void push(const value_type& value)
	{
		if (full()) {
			throw std::logic_error("Buffer is full now");
		}

		m_Counter++;
		m_Buffer[m_Head] = std::move(value);
		m_Head = next_index(m_Head, m_Size);
	}

	template <typename... _Va>
	void emplace(_Va&&... args)
	{
		if (full()) {
			throw std::logic_error("Buffer is full now");
		}

		m_Counter++;
		_Alty_traits::construct(m_Alloc, m_Buffer + m_Head, std::forward<_Va>(args)...);
		m_Head = next_index(m_Head, m_Size);
	}

	void pop()
	{
		if (empty()) {
			throw std::logic_error("Biffer is empty now");
		}

		m_Counter--;
		m_Buffer[m_Tail] = 0;
		m_Tail = next_index(m_Tail, m_Size);
	}

	value_type pop_return()
	{
		if (empty()) {
			throw std::logic_error("Biffer is empty now");
		}

		value_type tmp = std::move(m_Buffer[m_Tail]);

		m_Counter--;
		m_Buffer[m_Tail] = 0;
		m_Tail = next_index(m_Tail, m_Size);

		return tmp;
	}

	void clear()
	{
		if (m_Buffer == nullptr) { return; }

		for (size_t i{}; i < m_Size; i++) {
			_Alty_traits::destroy(m_Alloc, m_Buffer + i);
		}

		m_Head = 0;
		m_Tail = 0;

		m_Counter = 0;
		m_Size = 0;
	}

	void resize(size_t new_size)
	{
		if (new_size == m_Size) {
			return;
		}

		value_type* new_Buffer = m_Alloc.allocate(new_size + 1);
		set_to_null(new_Buffer, new_size);

		for (size_t i = m_Tail, c{}; c != m_Size; i = next_index(i, m_Size), c++) {
			new_Buffer[c] = m_Buffer[i];
		}

		if (m_Buffer != nullptr) {
			for (size_t i{}; i < m_Size; i++) {
				_Alty_traits::destroy(m_Alloc, m_Buffer + i);
			}
			m_Alloc.deallocate(m_Buffer, m_Size);
		}

		m_Buffer = new_Buffer;

		m_Size = new_size;
		m_Capacity = new_size + 1;

		m_Head = m_Counter;
		m_Tail = 0;
	}

	void insert(iterator lhead ,iterator ltail, iterator rhead)
	{
		for (ltail; ltail != lhead; ltail++) {
			*rhead = *ltail;
			rhead++;
		}
	}

	iterator head()
	{
		return iterator(m_Buffer + m_Head, 
				m_Buffer, m_Buffer + m_Size);
	}

	iterator tail()
	{
		return iterator(m_Buffer + m_Tail, 
				m_Buffer, m_Buffer + m_Size);
	}

	bool empty() const { return m_Counter == 0; }
	bool full() const { return m_Counter == m_Size; }

	size_t size() const { return m_Size; }
	size_t capacity() const { return m_Capacity; }
	size_t get_head() const { return m_Head; }
	size_t get_tail() const { return m_Tail; }

	const value_type& operator[](index_type index) const { return m_Buffer[index]; }
	value_type& operator[](index_type index) { return m_Buffer[index]; }

private:
	value_type* m_Buffer	= nullptr;

	size_t m_Size			= 0;
	size_t m_Capacity		= 0;
	size_t m_Counter		= 0;

	index_type m_Head		= 0;
	index_type m_Tail		= 0;

	_Alty m_Alloc;

private:
	_NODISCARD static index_type next_index(index_type index, index_type size_index) noexcept
	{
		index++;
		return index >= size_index ? 0 : index;
	}

	_NODISCARD static index_type prev_index(index_type index, index_type size_index) noexcept
	{
		return index == 0 ? (size_index - 1) : index--;
	}

	void set_to_null(value_type* buffer, size_t sze) noexcept
	{
		for (size_t i{}; i < sze; i++) {
			buffer[i] = NULL;
		}
	}
};

#endif // !RBUFFER_H


