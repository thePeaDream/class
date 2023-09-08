#pragma once
#include <iostream>
#include <vector>
#include <assert.h>
using std::endl;
using std::cout;
using std::cin;
namespace yh
{
	template<class T>
	struct less
	{
		bool operator()(const T& val1, const T& val2)const
		{
			return val1 < val2;
		}
	};

	template<class T>
	struct greater
	{
		bool operator()(const T& val1, const T& val2)const
		{
			return val1 > val2;
		}
	};


	template<class T, class Container = std::vector<T>, class Compare = std::less<T>>
	class priority_queue
	{
	private:
		Container _con;
	public:
		//对自定义类型，初始化列表会去调用它的默认构造
		priority_queue(){}
		
		//用一段迭代器区间构造
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		{
			//相当于建堆，建堆最好用向下调整算法为O(N)

			while (first != last)
			{
				_con.push_back(*first);
				++first;
			}

			//从倒数第一个非叶子结点开始，使用向下调整算法建堆
			for (int i = (size() - 1 - 1) / 2; i >= 0; --i)
			{
				//size() - 1是最后一个结点位置，(size()-1 - 1) / 2是最后一个结点的父结点
				adjustDown(i);
			}
		}
		
		
		//向优先级队列插入数据，插入后保证它仍然是一个堆
		//使用向上调整算法
		void push(const T& val)
		{
			_con.push_back(val);
			adjustUp(_con.size() - 1);
		}
		//将pos位置元素，向上调整（比较它与它的祖先结点）
		void adjustUp(size_t pos)
		{
			static Compare compare;

			size_t parent = (pos - 1) / 2;
			//若pos = 0,没有父亲结点，不能再向上调整
			while (pos > 0)
			{
				//小于建大堆，默认建大堆
				if (compare(_con[parent], _con[pos]))//默认是_con[parent] < _con[pos]
				{
					//pos向上调整
					std::swap(_con[parent], _con[pos]);

					//更新pos和它的parent
					pos = parent;
					parent = (pos - 1) / 2;
				}
				else
					break;
			}
		}
		
		//删除堆顶数据，一般用来选出最大最小的元素
		//1 交换 堆顶元素和尾元素
		//2 尾删
		//3 对此时堆顶数据 用向下调整算法
		void pop()
		{
			assert(size() > 0);
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			adjustDown(0);
		}
		void adjustDown(size_t pos)
		{
			static Compare compare;
			//前提是左边和右边都是大堆或小堆

			//当没有左孩子时，调整结束
			size_t mChild = 2 * pos + 1;
			while (mChild < size())
			{
				if (mChild + 1 < _con.size() && compare(_con[mChild], _con[mChild + 1]) )//默认是_con[mChild] < _Con[mChild+1]
					++mChild;

				if (compare(_con[pos], _con[mChild]))
				{
					std::swap(_con[pos], _con[mChild]);

					pos = mChild;
					mChild = pos * 2 + 1;
				}
				else
					break;
			}
		}
		
		size_t size() const
		{
			return _con.size();
		}
		bool empty() const 
		{ 
			return _con.empty(); 
		}
		const T& top() const 
		{ 
			return _con.front(); 
		}
	};

}
