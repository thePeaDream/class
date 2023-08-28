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
		cout << "走重载的operator new" << endl;
		void* ret = _alloc.allocate(1);//在内存池里申请一个结点内存
		return ret;
	}

	void operator delete(void* block)
	{
		cout << "走重载的operator delete" << endl;
		//释放内存还给内存池
		_alloc.deallocate((ListNode*)block, 1);
	}
private:
	ListNode* _next;
	int _val;
	static allocator<ListNode> _alloc;//让该类的所有对象共用一个内存池【声明】
};
//定义
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
		//显式实例化，显式传模板参数T，指定要存储的数据类型
		vector<int> v1;
		vector<double> v2;

		//调用成员函数push_back(),尾插数据
		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);

		v2.push_back(1.1);
		v2.push_back(2.2);
		v2.push_back(3.3);

		//vector重载了operator[ ]，可以像数组一样访问对应位置的值
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
		
		//正常使用
		vector<int> v1(3, 1);//用3个1初始化v1

		vector<int> v2(3);//用3个默认的int初始化v2，即0
		vector<int*> v3(3);//用3个默认的int*初始化v3，即nullptr
	}
	void test4()
	{
		string s1("abcdef");
		
		//char类型会隐式类型转换成int，迭代器类型string::iterator
		vector<int> v1(s1.begin(), s1.end());

		//迭代器类型vector<int>::iterator
		vector<int> v2(v1.begin(), v1.end());

		cout << "遍历v1：" << endl;
		for (size_t i = 0; i < v1.size(); ++i)
			cout << v1[i] << "  ";
		cout << endl;

		cout << "遍历v2：" << endl;
		for (size_t i = 0; i < v2.size(); ++i)
			cout << v2[i] << "  ";
		cout << endl;
	}
	void test5()
	{
		vector<int> v1(3, 1);

		//效果相同,内部实现深拷贝
		vector<int> v2 = v1;
		vector<int> v3(v1);
	}

	
	void test6()
	{
		vector<int> v(3, 2);
		vector<int>::iterator it = v.begin();
		//左闭右开
		while (it != v.end())
		{
			cout << *it << "  ";
			++it;
		}
	}

	//测试vs2022的vector扩容机制
	void test7()
	{
		vector<int> v;
		cout << "初始容量：" << v.capacity() << endl;
		size_t curCapacity = v.capacity();
		size_t maxNum = 1000;
		for (size_t i = 0; i < maxNum; ++i)
		{
			v.push_back(i);
			//插入后如果发生扩容
			if (curCapacity != v.capacity())
			{
				curCapacity = v.capacity();
				cout << "新扩容：" << curCapacity << endl;
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
		//直接修改
		if (it != v1.end())
		{
			//找到并修改
			*it = 4;
			for (auto x : v1)
				cout << x << " ";
		}
		else
			cout << "未找到" << endl;
	}
	void test9()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);

		//先找到3的位置
		vector<int>::iterator pos1 = find(v.begin(), v.end(), 3);
		if (pos1 != v.end())
		{
			//找到并插入5
			v.insert(pos1, 5);
			for (auto x : v)
				cout << x << " ";
		}
		cout << endl << endl;

		//1 2 5 3 4
		//在5之前插入3个1
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
		//在2之前插入v2.begin()~v2.end()
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
		
		//删除4
		vector<int>::iterator pos = find(v.begin(), v.end(), 4);
		if (pos != v.end())
		{
			v.erase(pos);
			for (auto x : v)
				cout << x << " ";
		}
		cout << endl << endl;

		//删除0~5的所有数据，不包括5
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
		cout <<"v1的数据个数："<< v1.size() << "  v1的初始容量：" << v1.capacity() << endl;
		cout << "v2的数据个数："<<v2.size() << "  v2的初始容量：" << v2.capacity() << endl;
		cout << "v3的数据个数：" << v3.size() << "  v3的初始容量：" << v3.capacity() << endl;
		
		cout << "v2的数据如下：" << endl;
		for (size_t i = 0; i < v2.size(); ++i)
		{
			cout << v2[i] << " "; 
		}
		cout << endl;

		cout << "v3的数据如下：" << endl;
		for (size_t i = 0; i < v3.size(); ++i)
		{
			cout << v3[i] << " ";
		}
	}
	
	void test12()
	{
		vector<int> v;
		//提前申请空间，不会有扩容
		//v.reserve(1000);

		v.resize(1000, 0); //改变数据量，改变容量
		cout << "初始容量：" << v.capacity() << endl;
		cout << "初始数据量：" << v.size() << endl;
		size_t curCapacity = v.capacity();
		size_t maxNum = 1000;
		for (size_t i = 0; i < maxNum; ++i)
		{
			v.push_back(i);
			//插入后如果发生扩容
			if (curCapacity != v.capacity())
			{
				curCapacity = v.capacity();
				cout << "新扩容：" << curCapacity << endl;
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

		//依次取出容器v的每一个迭代器，解引用赋值给x(如果x不是引用)
		for (auto& x : v)
		{
			cout << x << " ";
		}
	}
	void test14()
	{
		vector<int> v;
		v.insert(v.end(), 1);//尾插
		v.insert(v.begin(), 2);//头插
		//2  1
		for (auto& x : v)
			cout << x << " ";
		cout << endl << endl;

		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		//2 1 3 4 5
		//在3之前插入一个6
		//找到3的位置
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
		v.insert(pos, 6);
		for (auto& x : v)
			cout << x << " ";
	}
	void test15()
	{
		vector<int> v;
		//v.insert(v.end(), 1);//尾插
		//v.insert(v.begin(), 2);//头插
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		//2 1 3 4 5
		//在3之前插入一个6
		//找到3的位置
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
		v.insert(pos, 6);
		//扩容后，外面的pos成了野指针，已经失效
		cout << *pos;
	}
	/*void test16()
	{
		vector<int> v;
		v.push_back(3);
		vector<int>::iterator pos = find(v.begin(), v.end(), 3);
		
		//v.insert(v.begin(), 2);//头插
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
		//删除所有出现的1
		vector<int> v(3, 1);
		v.push_back(4);
		v.push_back(5);
		v.push_back(1);
		v.push_back(6);

		//遍历vector
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it == 1)
			{
				//由于erase后，迭代器会有失效的风险，
				//所以erase会返回 被删除元素 的 下一个元素 的迭代器，可以用it接收
				it = v.erase(it);
				//此时it已经指向下一个元素，不应该再++
			}
			else
				++it;
		}

		for (auto x : v)
			cout << x << " ";
	}
	void test19()
	{
		//在所有的2前面插入9
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
				//插入数据后同样需要更新it，否则it可能会是野指针
				//stl规定返回 插入的新数据位置的迭代器
				it = v.insert(it, 9);
				++it;
				//所以应该跳过刚才已经遍历过的数据
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

		//拷贝构造
		vector<int> v2(v1);
		for (auto x : v2)
			cout << x << " ";
		cout << endl;

		vector<int> v3;
		//赋值运算符重载
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
