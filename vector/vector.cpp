#include "vector.h"
using namespace std;
/*class ListNode
{
public:
	ListNode(int val = 0)
		:_next(nullptr)
		,_val(val)
	{}
	void* operator new(size_t n)
	{
		cout << "�����ص�operator new" << endl;
		void* ret = _alloc.allocate(1);//���ڴ��������һ������ڴ�
		return ret;
	}

	void operator delete(void* block)
	{
		cout << "�����ص�operator delete" << endl;
		//�ͷ��ڴ滹���ڴ��
		_alloc.deallocate((ListNode*)block, 1);
	}
private:
	ListNode* _next;
	int _val;
	static allocator<ListNode> _alloc;//�ø�������ж�����һ���ڴ�ء�������
};
//����
allocator<ListNode> ListNode::_alloc;

void test1()
{
	ListNode* n1 = new ListNode(1);
	ListNode* n2 = new ListNode(2);
	ListNode* n3 = new ListNode(3);
	delete n1;
	delete n2;
	delete n3;
}*/
namespace std
{
	void test2()
	{
		//��ʽʵ��������ʽ��ģ�����T��ָ��Ҫ�洢����������
		vector<int> v1;
		vector<double> v2;

		//���ó�Ա����push_back(),β������
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		v2.push_back(1.1);
		v2.push_back(2.2);
		v2.push_back(3.3);

		//vector������operator[ ]������������һ�����ʶ�Ӧλ�õ�ֵ
		for (int i = 0; i < v1.size(); ++i)
		{
			cout << v1[i] << " ";
		}
		cout << endl;
		for (int i = 0; i < v2.size(); ++i)
		{
			cout << v2[i] << " ";
		}
	}

	void test3()
	{
		int a = int();
		double b = double();
		
		//����ʹ��
		vector<int> v1(3, 1);//��3��1��ʼ��v1

		vector<int> v2(3);//��3��Ĭ�ϵ�int��ʼ��v2����0
		vector<int*> v3(3);//��3��Ĭ�ϵ�int*��ʼ��v3����nullptr
	}
	void test4()
	{
		string s1("abcdef");
		
		//char���ͻ���ʽ����ת����int������������string::iterator
		vector<int> v1(s1.begin(), s1.end());

		//����������vector<int>::iterator
		vector<int> v2(v1.begin(), v1.end());

		cout << "����v1��" << endl;
		for (size_t i = 0; i < v1.size(); ++i)
			cout << v1[i] << "  ";
		cout << endl;

		cout << "����v2��" << endl;
		for (size_t i = 0; i < v2.size(); ++i)
			cout << v2[i] << "  ";
		cout << endl;
	}
	void test5()
	{
		vector<int> v1(3, 1);

		//Ч����ͬ,�ڲ�ʵ�����
		vector<int> v2 = v1;
		vector<int> v3(v1);
	}

	
	void test6()
	{
		vector<int> v(3, 2);
		vector<int>::iterator it = v.begin();
		//����ҿ�
		while (it != v.end())
		{
			cout << *it << "  ";
			++it;
		}
	}

	//����vs2022��vector���ݻ���
	void test7()
	{
		vector<int> v;
		cout << "��ʼ������" << v.capacity() << endl;
		size_t curCapacity = v.capacity();
		size_t maxNum = 1000;
		for (size_t i = 0; i < maxNum; ++i)
		{
			v.push_back(i);
			//����������������
			if (curCapacity != v.capacity())
			{
				curCapacity = v.capacity();
				cout << "�����ݣ�" << curCapacity << endl;
			}
		}
	}

	void test8()
	{
		vector<int> v1;
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(2);
		vector<int>::iterator it = find(v1.begin(), v1.end(), 2);
		//ֱ���޸�
		if (it != v1.end())
		{
			//�ҵ����޸�
			*it = 4;
			for (auto x : v1)
				cout << x << " ";
		}
		else
			cout << "δ�ҵ�" << endl;
	}
	void test9()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		//���ҵ�3��λ��
		vector<int>::iterator pos1 = find(v.begin(), v.end(), 3);
		if (pos1 != v.end())
		{
			//�ҵ�������5
			v.insert(pos1, 5);
			for (auto x : v)
				cout << x << " ";
		}
		cout << endl << endl;

		//1 2 5 3 4
		//��5֮ǰ����3��1
		vector<int>::iterator pos2 = find(v.begin(), v.end(), 5);
		if (pos2 != v.end())
		{
			v.insert(pos2, 3, 1);
			for (auto x : v)
				cout << x << " ";
		}
		cout << endl << endl;

		vector<int> v2(3, 5);// 5 5 5
		//12111534
		//��2֮ǰ����v2.begin()~v2.end()
		vector<int>::iterator pos3 = find(v.begin(), v.end(), 2);
		if (pos3 != v.end())
		{
			v.insert(pos3, v2.begin(), v2.end());
			for (auto x : v)
				cout << x << " ";
		}
	}

	void test10()
	{
		vector<int> v;
		for (size_t i = 0; i < 10; ++i)
			v.push_back(i);//0~9
		
		//ɾ��4
		vector<int>::iterator pos = find(v.begin(), v.end(), 4);
		if (pos != v.end())
		{
			v.erase(pos);
			for (auto x : v)
				cout << x << " ";
		}
		cout << endl << endl;

		//ɾ��0~5���������ݣ�������5
		vector<int>::iterator startV = find(v.begin(), v.end(), 0);
		vector<int>::iterator endV = find(v.begin(), v.end(), 5);
		if (startV != v.end() && endV != v.end())
		{
			v.erase(startV, endV);
			for (auto x : v)
				cout << x << " ";
		}
	}
}
namespace lyh
{
	void test11()
	{
		vector<int> v1;
		vector<int> v2(3, 1);
		string s1("abcdefg");
		vector<int> v3(s1.begin(), s1.end());
		cout <<"v1�����ݸ�����"<< v1.size() << "  v1�ĳ�ʼ������" << v1.capacity() << endl;
		cout << "v2�����ݸ�����"<<v2.size() << "  v2�ĳ�ʼ������" << v2.capacity() << endl;
		cout << "v3�����ݸ�����" << v3.size() << "  v3�ĳ�ʼ������" << v3.capacity() << endl;
		
		cout << "v2���������£�" << endl;
		for (size_t i = 0; i < v2.size(); ++i)
		{
			cout << v2[i] << " "; 
		}
		cout << endl;

		cout << "v3���������£�" << endl;
		for (size_t i = 0; i < v3.size(); ++i)
		{
			cout << v3[i] << " ";
		}
	}
	
	void test12()
	{
		vector<int> v;
		//��ǰ����ռ䣬����������
		//v.reserve(1000);

		v.resize(1000, 0); //�ı����������ı�����
		cout << "��ʼ������" << v.capacity() << endl;
		cout << "��ʼ��������" << v.size() << endl;
		size_t curCapacity = v.capacity();
		size_t maxNum = 1000;
		for (size_t i = 0; i < maxNum; ++i)
		{
			v.push_back(i);
			//����������������
			if (curCapacity != v.capacity())
			{
				curCapacity = v.capacity();
				cout << "�����ݣ�" << curCapacity << endl;
			}
		}

	}

	void test13()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.pop_back();

		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

		//����ȡ������v��ÿһ���������������ø�ֵ��x(���x��������)
		for (auto& x : v)
		{
			cout << x << " ";
		}
	}
	void test14()
	{
		vector<int> v;
		v.insert(v.end(), 1);//β��
		v.insert(v.begin(), 2);//ͷ��
		//2  1
		for (auto& x : v)
			cout << x << " ";
		cout << endl << endl;

		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		//2 1 3 4 5
		//��3֮ǰ����һ��6
		//�ҵ�3��λ��
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
		v.insert(pos, 6);
		for (auto& x : v)
			cout << x << " ";
	}
	void test15()
	{
		vector<int> v;
		//v.insert(v.end(), 1);//β��
		//v.insert(v.begin(), 2);//ͷ��
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		//2 1 3 4 5
		//��3֮ǰ����һ��6
		//�ҵ�3��λ��
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
		v.insert(pos, 6);
		//���ݺ������pos����Ұָ�룬�Ѿ�ʧЧ
		cout << *pos;
	}
	/*void test16()
	{
		vector<int> v;
		v.push_back(3);
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
		
		//v.insert(v.begin(), 2);//ͷ��
	}*/

	/*void test17()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		vector<int>::iterator pos = find(v.begin(), v.end(), 1);
		v.erase(pos);
		for (auto x : v)
			cout << x << " ";
	}*/
	void test18()
	{
		//ɾ�����г��ֵ�1
		vector<int> v(3, 1);
		v.push_back(4);
		v.push_back(5);
		v.push_back(1);
		v.push_back(6);

		//����vector
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it == 1)
			{
				//����erase�󣬵���������ʧЧ�ķ��գ�
				//����erase�᷵�� ��ɾ��Ԫ�� �� ��һ��Ԫ�� �ĵ�������������it����
				it = v.erase(it);
				//��ʱit�Ѿ�ָ����һ��Ԫ�أ���Ӧ����++
			}
			else
				++it;
		}

		for (auto x : v)
			cout << x << " ";
	}
	void test19()
	{
		//�����е�2ǰ�����9
		vector<int> v;
		v.push_back(2);
		v.push_back(2);
		v.push_back(4);
		v.push_back(2);
		v.push_back(7);
		// 2  3  4  2  7  
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it == 2)
			{
				//�������ݺ�ͬ����Ҫ����it������it���ܻ���Ұָ��
				//stl�涨���� �����������λ�õĵ�����
				it = v.insert(it, 9);
				++it;
				//����Ӧ�������ղ��Ѿ�������������
				++it;
			}
			else
				++it;
		}
		
		for (auto x : v)
			cout << x << " ";
	}

	void test20()
	{
		vector<int> v1(2, 3);
		for (auto x : v1)
			cout << x << " ";
		cout << endl;

		//��������
		vector<int> v2(v1);
		for (auto x : v2)
			cout << x << " ";
		cout << endl;

		vector<int> v3;
		//��ֵ���������
		v3 = v1;
		for (auto x : v3)
			cout << x << " ";
	}
}
int main()
{
	lyh::test12();
	return 0;
}
