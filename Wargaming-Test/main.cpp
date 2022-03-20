#include <iostream>
#include <vector>
#include <deque>

#include "iseven/iseven.h"
#include "ring_buffers/ring_buffer.h"
#include "ring_buffers/linked_ring.h"

int main()
{
	linked_ring<int> a;

	a.append(1);
	a.append(2);
	a.append(3);
	a.append(4);

	for (auto it = a.head(); it != a.tail(); ++it) {
		std::cout << *it << " ";
	}

	return 0;
}