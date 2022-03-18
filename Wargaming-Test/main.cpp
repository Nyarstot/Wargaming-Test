#include <iostream>
#include <vector>
#include <deque>

#include "iseven/iseven.h"
#include "ring_buffers/ring_buffer.h"
#include "ring_buffers/dring_buffer.h"

int main()
{
	dring_buffer<int> tst(5);

	tst.push(0);
	tst.push(1);
	tst.push(2);
	tst.push(3);
	tst.push(4);
	tst.push(5);

	for (dring_buffer<int>::iterator it = tst.begin(); it != tst.end(); it++) {
		std::cout << *it << " ";
	}

	/*ring_buffer<int> tmp(5);

	tmp.set_head(0);

	tmp.push_head(0);
	tmp.push_head(1);
	tmp.push_head(2);
	tmp.push_head(3);
	tmp.push_head(4);

	tmp.push_head(8);

	std::cout << tmp.get_head() << " , " << tmp.get_tail() << "\n";

	std::cout << tmp[0] << " " << tmp[1] << " " << tmp[2] << " " << tmp[3] << " " << tmp[4] << " ";

	/*for (ring_buffer<int>::iterator it = tmp.tail(); it != tmp.head(); ++it) {
		std::cout << *it << " ";
	}*/

	return 0;
}