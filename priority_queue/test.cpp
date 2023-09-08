#include "priority_queue.hpp"
namespace yh
{
	void testFunctor()
	{
		//�÷º�������һ������
		yh::greater<int> functor;

		bool ret = functor(1, 2);//������functor.operator()(1, 2)
		cout << ret << endl;
	}
	void testPriorityQueue()
	{
		int arr[] = { 9, 7, 15, 1, 86, 47, 55 };
		//Ĭ��ʹ��vector��Ϊ�ײ�������Ĭ�ϴ�less����ѣ����Ԫ�����ȼ���
		priority_queue<int, std::vector<int>, greater<int>> pq(arr, arr + sizeof(arr) / sizeof(int));
		//��һ�ε��������乹��pq

		//����ȡ�Ѷ�������Ȼ��pop�Ѷ����ݣ��Ӵ�С���
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