#include <iostream>
#include <vector>
#include <deque>

#include "iseven/iseven.h"
#include "ring_buffers/ring_buffer.h"

int main()
{
	ring_buffer<int> tmp(5);

	tmp.set_head(1);

	/*
	
	  |
	0 1 2 3 4
	5 1 2 3 4

	*/

	tmp.append(0);
	tmp.append(1);
	tmp.append(2);
	tmp.append(3);

	//tmp.print();

	for (ring_buffer<int>::iterator it = tmp.tail(); it != tmp.head(); ++it) {
		std::cout << *it << " ";
	}

	return 0;
}