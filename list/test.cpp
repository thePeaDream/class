#include<iostream>
#include "list.hpp"

namespace std
{
	//����������
	void testUse1()
	{
		list<int> lt;

		//β���ͷ��
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_front(4);

		//����������
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++it;
		}
	}

	//����ɾ��
	void testUse2()
	{
		//iterator insert(iterator pos, const T& val)��pos֮ǰ����val�������²�����ĵ�����
		//iterator erase(iterator pos)ɾ��posλ�õĽ�㣬���ر�ɾ��������һ��������
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		//��2ǰ�����4��Ȼ��ɾ��2
		list<int>::iterator pos = find(lt.begin(), lt.end(), 2);
		if (pos != lt.end())
		{
			lt.insert(pos, 4);//��ʱpos����ʧЧ����Ϊ�ײ��� ��ͷ˫��ѭ������
			lt.erase(pos);//��ʧЧ����㱻�ͷ��ˣ���ʱpos��Ұָ��
		}
		for (int a : lt)
			cout << a << " ";
	}

	//��һ�����������ת�Ƹ���һ������ splice
	void testUse3()
	{
		//lt1 ��1 2 3 4
		list<int> lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);

		//lt2 ��5 6 7 8
		list<int> lt2;
		lt2.push_back(5);
		lt2.push_back(6);
		lt2.push_back(7);
		lt2.push_back(8);


		list<int>::iterator it1 = lt1.begin();
		//1 void splice(iterator pos, list& x)
		//��x���������ȫ��ת�Ƹ�ĳ�������pos֮ǰ
		lt1.splice(it1, lt2);
		//��ʱ lt1��5 6 7 8 1 2 3 4

		cout << "lt1�����ݣ�";
		for (auto x : lt1)
			cout << x << " ";
		cout << endl;

		cout << "lt2�����ݣ�";
		for (auto x : lt2)
			cout << x << " ";
		cout << endl;

		// lt1��5 6 7 8 1 2 3 4
		// lt2��10 11
		lt2.push_back(10);
		lt2.push_back(11);

		//��x�����iλ�����ݣ�ת�Ƹ�pos֮ǰ
		//2 void splice(iterator pos, list& x, iterator i)

		//��lt1��һ�������������ݣ�ת�Ƹ�lt2��Ԫ��֮ǰ
		lt2.splice(lt2.begin(), lt1, lt1.begin());

		cout << "lt1�����ݣ�";
		for (auto x : lt1)
			cout << x << " ";
		cout << endl;

		cout << "lt2�����ݣ�";
		for (auto x : lt2)
			cout << x << " ";
		cout << endl;

		//lt1��6 7 8 9 1 2 3 4
		//lt2��5 10 11
		//��x�����ĳ������������[����ҿ�)��ת�Ƶ�pos֮ǰ
		//3 void splice(iterator pos, list& x, iterator first, iterator last)

		//��lt1��7~3���н��(������3)��ת�Ƹ�lt2ͷ��֮ǰ
		list<int>::iterator first = find(lt1.begin(), lt1.end(), 7);
		list<int>::iterator last = find(lt1.begin(), lt1.end(), 3);
		if (first != lt1.end() && last != lt1.end())
			lt2.splice(lt2.begin(), lt1, first, last);

		cout << "lt1�����ݣ�";
		for (auto x : lt1)
			cout << x << " ";
		cout << endl;

		cout << "lt2�����ݣ�";
		for (auto x : lt2)
			cout << x << " ";
		cout << endl;
		//lt1��6 3 4
		//lt2��7 8 9 1 2 5 10 11
	}

	//removeɾ�����������г��ֵ�val
	void testUse4()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(1);
		lt.push_back(4);
		lt.push_back(1);
		//void remove(const T& val)
		lt.remove(1);
		for (auto x : lt)
			cout << x << " ";
		cout << endl;
	}

	//���������sort
	void testUse5()
	{
		//void sort()
		/*list<int> lt;
		lt.push_back(5);
		lt.push_back(4);
		lt.push_back(3);
		lt.push_back(2);
		lt.push_back(1);
		lt.sort();
		for (auto x : lt)
			cout << x << " ";
		cout << endl;
		*/
		//Ϊʲô����Ҫ�����ṩsort�����㷨�����sort����
		//�㷨����sortǰ��������ռ��������ײ��ÿ���
		//�����sort�ײ�ʹ�ù鲢���򣬹鲢�����������Ҫ���ռ䣬������Ĺ鲢����Ҫ�ռ临�Ӷ�


		//�漰���ٻ��������ʣ�vector����������ռ���÷������ݵ��ٶȸ��죬
		// һ�����ݣ���list + sort ����  ������  ��vector + �㷨��sort����
		list<int> lt1;
		vector<int> v1;
		srand((unsigned)time(nullptr));
		int num = 1000000;
		//����num��������������Ƿֱ���뵽list��vector�У��Ƚ������ʱ��
		for (int i = 0; i < num; ++i)
		{
			int insert = rand() % 100000;
			lt1.push_back(insert);
			v1.push_back(insert);
		}

		//���������
		clock_t beginList = clock();
		lt1.sort();
		clock_t endList = clock();

		//�㷨�������
		clock_t beginVector = clock();
		sort(v1.begin(), v1.end());
		clock_t endVector = clock();

		cout << "����sortʱ�䣺" << endList - beginList << endl;
		cout << "�㷨��sortʱ�䣺" << endVector - beginVector << endl;
	}

	void testUse()
	{
		//testUse1();
		//testUse2();
		//testUse3();
		testUse4();
		//testUse5();
	}
}

namespace yh
{
	//������ͨ������
	void testMyList1()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);

		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			std::cout << *it << " ";
			++it;//�������ĵ�������ԭ��ָ�룬++�޷�ָ����һ����� |  ���it��Node*���ͣ�*it��Node����������
			//���Ա�������һ�����ͣ�Ȼ���ڸ������ڲ�ʹ�����������++��*��!=
		}
	}

	//����const������
	void testMyList2(const list<int>& lt)
	{
		//const��������const������
		list<int>::const_iterator cit = lt.begin();
		while (cit != lt.end())
		{
			std::cout << *cit << " ";
			++cit;
		}
	}


	struct A
	{
		int _a;
		int _b;
		A(int a = 0, int b = 0)
			:_a(a)
			,_b(b)
		{}
	};

	//���Ե����������ص�operator->()
	void testMyList3()
	{
		list<A> lt;
		lt.push_back(A(0, 0));
		lt.push_back(A(1, 1));
		lt.push_back(A(2, 2));

		list<A>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//it->ת����it.operator->(),�������ݵĵ�ַ
			//ʵ����Ӧ��
			std::cout << it->_a << " " << it->_b<< std::endl;
			++it;
		}
	}

	//���Բ���ɾ��
	void testMyList4()
	{
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		for (auto x : lt)
			std::cout << x << " ";
		std::cout << std::endl;
		lt.insert(lt.begin(), 5);
		lt.insert(lt.begin(), 6);
		for (auto x : lt)
			std::cout << x << " ";
		std::cout << std::endl;
		lt.erase(lt.begin());
		lt.erase(lt.begin());
		for (auto x : lt)
			std::cout << x << " ";
	}

	//���Ը��ֹ��캯�� �Լ� =���������
	void testMyList5()
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		
		//���������乹��
		list<int> lv(v.begin(), v.end());
		for (auto x : lv)
			std::cout << x << " ";
		std::cout << std::endl;

		//��������
		list<int> lt2 = lv;
		for (auto x : lt2)
			std::cout << x << " ";
		std::cout << std::endl;

		//��ֵ���������
		list<int> lt3;
		lt3.push_back(9);
		lt3.push_back(19);
		lt2 = lt3;
		for (auto x : lt2)
			std::cout << x << " ";
		std::cout << std::endl;
	}

	void testMyList()
	{
		
		//testMyList1();
		// list<int> lt;
		//lt.push_back(1);
		//lt.push_back(2);
		//lt.push_back(3);
		//testMyList2(lt);
		//testMyList3();
		//testMyList4();
		testMyList5();
	}
}

int main()
{
	//std::testUse();
	yh::testMyList();
	return 0;
}