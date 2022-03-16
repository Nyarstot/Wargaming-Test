#include <iostream>
#include <vector>
#include <deque>

#include "iseven/iseven.h"
#include "ring_buffers/ring_buffer.h"

int main()
{
	ring_buffer<int> tmp(7);

	tmp.set_head(3);

	tmp.append(1);
	tmp.append(2);
	tmp.append(3);
	tmp.append(4);
	tmp.append(5);
	tmp.append(6);
	tmp.append(7);

	//tmp.print();

	for (ring_buffer<int>::iterator it = tmp.head(); it != tmp.tail(); it++) {
		std::cout << *it << " ";
	}

	return 0;
}