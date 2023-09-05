#include<iostream>
#include "list.hpp"

namespace std
{
	//迭代器遍历
	void testUse1()
	{
		list<int> lt;

		//尾插和头插
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_front(4);

		//迭代器遍历
		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << *it << " ";
			++it;
		}
	}

	//插入删除
	void testUse2()
	{
		//iterator insert(iterator pos, const T& val)在pos之前插入val，返回新插入结点的迭代器
		//iterator erase(iterator pos)删除pos位置的结点，返回被删除结点的下一个迭代器
		list<int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		//在2前面插入4，然后删除2
		list<int>::iterator pos = find(lt.begin(), lt.end(), 2);
		if (pos != lt.end())
		{
			lt.insert(pos, 4);//此时pos不会失效，因为底层是 带头双向循环链表
			lt.erase(pos);//会失效，结点被释放了，此时pos是野指针
		}
		for (int a : lt)
			cout << a << " ";
	}

	//将一个链表的数据转移给另一个链表 splice
	void testUse3()
	{
		//lt1 ：1 2 3 4
		list<int> lt1;
		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);

		//lt2 ：5 6 7 8
		list<int> lt2;
		lt2.push_back(5);
		lt2.push_back(6);
		lt2.push_back(7);
		lt2.push_back(8);


		list<int>::iterator it1 = lt1.begin();
		//1 void splice(iterator pos, list& x)
		//将x链表的数据全部转移给某个链表的pos之前
		lt1.splice(it1, lt2);
		//此时 lt1：5 6 7 8 1 2 3 4

		cout << "lt1的数据：";
		for (auto x : lt1)
			cout << x << " ";
		cout << endl;

		cout << "lt2的数据：";
		for (auto x : lt2)
			cout << x << " ";
		cout << endl;

		// lt1：5 6 7 8 1 2 3 4
		// lt2：10 11
		lt2.push_back(10);
		lt2.push_back(11);

		//将x链表的i位置数据，转移给pos之前
		//2 void splice(iterator pos, list& x, iterator i)

		//将lt1第一个迭代器的数据，转移给lt2首元素之前
		lt2.splice(lt2.begin(), lt1, lt1.begin());

		cout << "lt1的数据：";
		for (auto x : lt1)
			cout << x << " ";
		cout << endl;

		cout << "lt2的数据：";
		for (auto x : lt2)
			cout << x << " ";
		cout << endl;

		//lt1：6 7 8 9 1 2 3 4
		//lt2：5 10 11
		//将x链表的某个迭代器区间[左闭右开)，转移到pos之前
		//3 void splice(iterator pos, list& x, iterator first, iterator last)

		//将lt1的7~3所有结点(不包含3)，转移给lt2头部之前
		list<int>::iterator first = find(lt1.begin(), lt1.end(), 7);
		list<int>::iterator last = find(lt1.begin(), lt1.end(), 3);
		if (first != lt1.end() && last != lt1.end())
			lt2.splice(lt2.begin(), lt1, first, last);

		cout << "lt1的数据：";
		for (auto x : lt1)
			cout << x << " ";
		cout << endl;

		cout << "lt2的数据：";
		for (auto x : lt2)
			cout << x << " ";
		cout << endl;
		//lt1：6 3 4
		//lt2：7 8 9 1 2 5 10 11
	}

	//remove删除链表中所有出现的val
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

	//链表的排序sort
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
		//为什么链表要单独提供sort，与算法库里的sort区别
		//算法库里sort前提是物理空间连续，底层用快排
		//链表的sort底层使用归并排序，归并排序对数组需要开空间，但链表的归并不需要空间复杂度


		//涉及高速缓存命中率，vector连续的物理空间会让访问数据的速度更快，
		// 一组数据，【list + sort 排序】  不如用  【vector + 算法库sort排序】
		list<int> lt1;
		vector<int> v1;
		srand((unsigned)time(nullptr));
		int num = 1000000;
		//产生num个随机数，把它们分别插入到list和vector中，比较排序的时间
		for (int i = 0; i < num; ++i)
		{
			int insert = rand() % 100000;
			lt1.push_back(insert);
			v1.push_back(insert);
		}

		//链表的排序
		clock_t beginList = clock();
		lt1.sort();
		clock_t endList = clock();

		//算法库的排序
		clock_t beginVector = clock();
		sort(v1.begin(), v1.end());
		clock_t endVector = clock();

		cout << "链表sort时间：" << endList - beginList << endl;
		cout << "算法库sort时间：" << endVector - beginVector << endl;
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
	//测试普通迭代器
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
			++it;//如果链表的迭代器是原生指针，++无法指向下一个结点 |  其次it是Node*类型，*it是Node，不是数据
			//所以必须它是一个类型，然后在该类型内部使用运算符重载++、*、!=
		}
	}

	//测试const迭代器
	void testMyList2(const list<int>& lt)
	{
		//const对象会调用const迭代器
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

	//测试迭代器内重载的operator->()
	void testMyList3()
	{
		list<A> lt;
		lt.push_back(A(0, 0));
		lt.push_back(A(1, 1));
		lt.push_back(A(2, 2));

		list<A>::iterator it = lt.begin();
		while (it != lt.end())
		{
			//it->转换成it.operator->(),返回数据的地址
			//实际上应该
			std::cout << it->_a << " " << it->_b<< std::endl;
			++it;
		}
	}

	//测试插入删除
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

	//测试各种构造函数 以及 =运算符重载
	void testMyList5()
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		
		//迭代器区间构造
		list<int> lv(v.begin(), v.end());
		for (auto x : lv)
			std::cout << x << " ";
		std::cout << std::endl;

		//拷贝构造
		list<int> lt2 = lv;
		for (auto x : lt2)
			std::cout << x << " ";
		std::cout << std::endl;

		//赋值运算符重载
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