/*
* This is the class of deque based ring buffer
*/
#ifndef QRING_BUFFER_H
#define QRING_BUFFER_H

#include <deque>

template<typename T>
class dring_buffer
{
public:
	typedef typename std::deque<T>::iterator iterator;

public:
	dring_buffer() {}
	dring_buffer(size_t size) {
		buffer.resize(size);
	}

	void push(const T& value)
	{
		buffer[car] = std::move(value);

		car++;
		if (car == buffer.size()) {
			car = 0;
		}
	}

	void set_carriage(size_t index)
	{
		if (index >= size) {
			throw std::invalid_argument("Index must be less than ring size")
		}

		car = index;
	}

	size_t get_carriage()
	{
		return car;
	}

	bool empty()
	{
		return buffer.empty();
	}

	size_t size()
	{
		return buffer.size();
	}

	iterator begin()
	{
		return buffer.begin();
	}

	iterator end()
	{
		return buffer.end();
	}

	T& operator[](size_t index) { return buffer[index]; }

private:
	std::deque<T> buffer;

	size_t car = 0;
};

#endif // !QRING_BUFFER_H

