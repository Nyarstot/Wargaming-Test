#pragma once

#include <utility>

template <typename rbuffer>
class ring_iterator
{
public:
	using valueType		= typename rbuffer::valueType;
	using pointerType	= valueType*;
	using referenceType = valueType&;

public:

	ring_iterator(pointerType ptr) : m_Ptr(ptr)
	{
	}

	ring_iterator& operator++() { m_Ptr++; return *this; }
	ring_iterator operator++(int) { ring_iterator it = *this; ++(*this); return it; }
	ring_iterator& operator--() { m_Ptr--; return *this; }
	ring_iterator operator--(int) { ring_iterator it = *this; --(*this); return it; }

	referenceType operator[](int index) { return *(m_Ptr + index); }

	pointerType operator->() { return m_Ptr; }
	referenceType operator*() { return *m_Ptr; }

	bool operator==(const ring_iterator& it) const { return m_Ptr == it.m_Ptr; }
	bool operator!=(const ring_iterator& it) const { return !(*this == it); }

private:
	pointerType m_Ptr;

};

template<typename T>
class rbuffer
{
public:
	using valueType = T;
	using iterator	= ring_iterator<rbuffer<T>>;

public:
	rbuffer() {}
	rbuffer(size_t size) : m_Size(size) 
	{
		m_Capacity = m_Size + m_Size / 2;
		m_Buffer = new T[m_Capacity];
	};
	~rbuffer()
	{
		clear();
		::operator delete(m_Buffer, m_Capacity * sizeof(T));
	}

	iterator begin()
	{
		return iterator(m_Buffer);
	}

	iterator end()
	{
		return iterator(m_Buffer + m_Size) ;
	}

	void push_forward(const T& value)
	{
		m_IndexPointer++;
		if (m_IndexPointer == m_Size) {
			m_IndexPointer = 0;
		}

		m_Buffer[m_IndexPointer] = value;
	}

	void push_forward(T&& value) {
		m_IndexPointer++;
		if (m_IndexPointer == m_Size) {
			m_IndexPointer = 0;
		}

		m_Buffer[m_IndexPointer] = std::move(value);
	}

	void push_backward(const T& value) 
	{
		if (m_IndexPointer == 0) {
			m_IndexPointer = m_Size;
		}

		m_IndexPointer--;
		m_Buffer[m_IndexPointer] = value;
	}

	void clear()
	{
		for (size_t i{}; i < m_Size; i++) {
			m_Buffer[i].~T();
		}

		m_Size = 0;
	}

	void set_index_ptr(size_t newIndex) { m_IndexPointer = newIndex; }

	const T& operator[](size_t index) const
	{
		return m_Buffer[index];
	}

	T& operator[](size_t index)
	{
		return m_Buffer[index];
	}

	size_t size() const { return m_Size; }
	size_t index_ptr() const { return m_IndexPointer; }

private:
	T* m_Buffer = nullptr;

	size_t m_Size = 0;
	size_t m_Capacity = 0;
	size_t m_IndexPointer = 0;

	void reallocate(size_t newCapacity)
	{
		T* newBuffer = (T*)::operator new(newCapacity * sizeof(T));

		if (newCapacity < m_Size) {
			m_Size = newCapacity;
		}

		for (size_t i{}; i < m_Size; i++) {
			newBuffer[i] = std::move(m_Buffer[i]);
		}

		for (size_t i{}; i < m_Size; i++) {
			m_Buffer[i].~T();
		}

		::operator delete(m_Buffer, m_Capacity * sizeof(T));
		m_Buffer = newBuffer;
		m_Capacity = newCapacity;
	}
};