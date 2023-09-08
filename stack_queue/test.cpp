#include "stack.hpp"
#include "queue.hpp"
#include <iostream>
#include <vector>
#include <list>
using namespace std;

void myStackTest()
{
	lyh::stack<int, vector<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
}

void myQueueTest()
{
	lyh::queue<int, list<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
}

int main()
{
	myStackTest();
	myQueueTest();
	return 0;
}