#include <iostream>
#include <vector>
#include <deque>

#include "iseven/iseven.h"
#include "ring_buffers/ring_buffer.h"
#include "ring_buffers/static_ring.h"

int main()
{
	static_ring<int, 5> a;

	a.push_back(1);
	a.push_back(2);
	a.push_back(3);
	a.push_back(4);
	a.push_back(5);

	/*
	
	t h 
	0 1 2 3 4 5
	x 7 8 x x x

	*/
	for (auto it = a.begin(); it != a.last_element(); ++it) {
		std::cout << *it << " ";
	}

	return 0;
}