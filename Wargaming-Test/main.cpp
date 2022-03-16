#include <iostream>
#include <vector>
#include <deque>

#include "iseven/iseven.h"
#include "ring_buffers/rbuffer.h"

int main()
{
	rbuffer<int> t(5);
	t.push_forward(2);
	t.push_forward(2);
	t.push_forward(2);
	t.push_forward(2);

	for (rbuffer<int>::iterator it = t.begin() + 2; it != t.end(); it++)
	{
		std::cout << *it << " ";
	}



	return 0;
}