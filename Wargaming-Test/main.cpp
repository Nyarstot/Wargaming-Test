#include <iostream>
#include <vector>
#include <deque>

#include "iseven/iseven.h"
#include "ring_buffers/rbuffer.h"

template<typename T>
void PrintBuffer(const rbuffer<T>& buffer) {
	for (size_t i{}; i < buffer.size(); i++) {
		std::cout << buffer[i] << " ";
	}
}

int main()
{
	rbuffer<int> t(5);
	t.push_forward(2);
	t.push_forward(2);
	t.push_forward(2);
	t.push_forward(2);

	for (rbuffer<int>::iterator it = t.begin(); it != t.end(); it++)
	{
		std::cout << *it << " ";
	}



	return 0;
}