#include<iostream>
#include "list.hpp"
namespace yh
{
	void testMyList6()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);

		list<int>::reverse_iterator rit = lt.rbegin();
		while (rit != lt.rend())
		{
			std::cout << *rit << " ";
			++rit;
		}
	}
}

int main()
{
	yh::testMyList6();
	return 0;
}