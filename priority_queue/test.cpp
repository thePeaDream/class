#include "priority_queue.hpp"
namespace yh
{
	void testFunctor()
	{
		//用仿函数定义一个对象
		yh::greater<int> functor;

		bool ret = functor(1, 2);//本质是functor.operator()(1, 2)
		cout << ret << endl;
	}
	void testPriorityQueue()
	{
		int arr[] = { 9, 7, 15, 1, 86, 47, 55 };
		//默认使用vector作为底层容器，默认传less建大堆，大的元素优先级高
		priority_queue<int, std::vector<int>, greater<int>> pq(arr, arr + sizeof(arr) / sizeof(int));
		//用一段迭代器区间构造pq

		//不断取堆顶的数，然后pop堆顶数据，从大到小输出
		while (!pq.empty())
		{
			cout << pq.top() << " ";
			pq.pop();
		}
	}
}
int main()
{
	//yh::testFunctor();
	yh::testPriorityQueue();
	return 0;
}