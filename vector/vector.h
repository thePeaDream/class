#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>
namespace lyh
{	
	template<class T>
	class vector
	{
	public:
		//vector底层是个连续的数组，迭代器就是原生指针
		typedef T* iterator;
		typedef const T* const_iterator;

		//默认构造
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		//用n个val构造
		vector(size_t n, const T& val)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			//开空间+初始化空间
			T* tmp = new T[n];
			for (size_t i = 0; i < n; ++i)
				tmp[i] = val;

			//更新成员变量
			_start = tmp;
			_finish = _start + n;
			_end_of_storage = _finish;//初始容量和初始数据个数一致
		}

		//当定义vector<int> v2(3,1)时;
		//由于编译器会调用最匹配的函数，会调用到迭代器区间构造的函数
		//因为该函数的两个模板参数都相同，不会去调用vector(size_t n, const T& val)
		//所以多提供一个vector(int n, const T& val)
		vector(int n, const T& val)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			//开空间+初始化空间
			T* tmp = new T[n];
			for (size_t i = 0; i < n; ++i)
				tmp[i] = val;

			//更新成员变量
			_start = tmp;
			_finish = _start + n;
			_end_of_storage = _finish;//初始容量和初始数据个数一致
		}

		//用一段迭代器区间构造
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			//元素个数
			size_t n = last - first;
			
			//开空间+拷贝数据
			T* tmp = new T[n];
			for (size_t i = 0; i < n; ++i)
			{
				tmp[i] = first[i];
			}
			//更新成员变量
			_start = tmp;
			_finish = tmp + n;
			_end_of_storage = tmp + n;
		}

		//1 手动拷贝构造
		/*vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{
			//开空间，拷贝数据
			T* tmp = new T[v.capacity()];
			//也可以用v.size()

			//memcpy实现的浅拷贝，若出现vector<vector<int>> vv，
			//vector内部不能浅拷贝T类型，也必须是深拷贝
			//错误：memcpy(tmp, v._start, sizeof(T) * v.size());
			
			for (size_t i = 0; i < v.size(); i++)
			{
				tmp[i] = v[i]; //相当于内部调用T类型的赋值运算符重载完成深拷贝

				//注意(const vector<T>类型)v调用const类型的[]运算符重载，没有会报错
			}

			//更新成员变量
			_start = tmp;
			_finish = tmp + v.size();
			_end_of_storage = tmp + v.capacity();
		}*/

		void swap(vector<T>& tmp)
		{
			//交换所有成员变量
			std::swap(tmp._start, _start);
			std::swap(tmp._finish, _finish);
			std::swap(tmp._end_of_storage, _end_of_storage);
		}

		//2 用已有的构造函数帮助拷贝构造
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			//调用之前写的迭代器区间构造函数
			vector<T> tmp(v.begin(), v.end());
			
			//交换tmp和this的所有成员变量
			swap(tmp);
			//直接用库里的swap交换2个类对象,会调用vector<T>的1次拷贝构造，和vector<T>的2次赋值运算符重载
			//所以内部写一个swap用于交换两个类的成员变量即可
		}

		//1 赋值运算符重载，手动拷贝
		/*vector<T>& operator=(const vector<T>& v)
		{
			//不是自我赋值才处理
			if (&v != this)
			{
				//开空间+拷贝数据
				T* tmp = new T[v.capacity()];

				//与拷贝构造相似，不能浅拷贝T类型
				//memcpy(tmp, v._start, v.size() * sizeof(T));
				for (size_t i = 0; i < v.size(); ++i)
				{
					tmp[i] = v[i];
				}

				//释放旧空间
				delete[] _start;

				//更新this的成员变量
				_start = tmp;
				_finish = tmp + v.size();
				_end_of_storage = tmp + v.capacity();
			}
			return *this;
		}*/
		//2 赋值运算符重载，调用拷贝构造实现
		vector<T>& operator=(vector<T> v)
		{
			//形参拷贝构造实参，此时v正是this需要的

			//this的成员变量与v的成员变量交换
			//让形参v在函数调用结束后帮忙清理旧空间
			swap(v);
			return *this;
		}
		//析构
		~vector()
		{
			//std::cout << "成功调用析构函数" << std::endl;//仅用于验证
			delete[] _start;
		}

		//容量大小
		size_t size()const
		{
			return _finish - _start;
		}
		size_t capacity()const
		{
			return _end_of_storage - _start;
		}

		//设置数据个数为n，新增加的数据初始化为val
		void resize(size_t n, const T& val)
		{
			//(1) n > 当前数据量
			if (n > size())
			{
				//扩容+初始化
				reserve(n);
				for (size_t i = size(); i < n; i++)
					_start[i] = val;

				_finish = _start + n;
			}
			//(2) n < 当前数据量
			else if (n < size())
			{
				//删除多出n的数据
				_finish = _start + n;
			}
			//(3) n =当前数据量，无操作
			else{}
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				//开空间，拷贝数据
				T* newBlock = new T[n];
				for (size_t i = 0; i < size(); ++i)
				{
					newBlock[i] = _start[i];
				}
				//memcpy(newBlock, _start, sizeof(T) * size());
				
				//记录当前size()的值，因为它内部是_finish - _start算出来的，更新成员变量时，不能使用size()
				size_t st = size();

				//释放旧空间
				delete[] _start;

				//更新成员变量
				_start = newBlock;
				_finish = newBlock + st;
				_end_of_storage = newBlock + n;
			}
		}

		//const引用可以引用常量数据、引用隐式类型转换中间产生的临时变量
		//引用减少拷贝
		//尾插
		void push_back(const T& x)
		{
			//1 检查扩容
			if (_finish == _end_of_storage)
				reserve(capacity() ==   0 ?  5 : 2 * capacity() );
			//2 插入数据
			*_finish = x;
			++_finish;
		}
		//尾删
		void pop_back()
		{
			assert(size() > 0);
			--_finish;
		}

		//访问
		//[]运算符重载
		T& operator[](size_t n)
		{
			//检查是否越界访问
			assert(n < size());
			return *(_start + n);
		}

		//const[]运算符重载
		const T& operator[](size_t n)const
		{
			//检查是否越界访问
			assert(n < size());
			return *(_start + n);
		}

		//迭代器
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin()const
		{
			return _start;
		}
		const_iterator end()const
		{
			return _finish;
		}
		
		//任意位置插入和删除 （会引发迭代器失效）
		//第一种插入实现：在pos位置之前插入val 【错误1】
		/*void insert(iterator pos, const T& val)//若发生扩容，_start等成员变量全都指向全新的空间，但传过去的pos仍然指向旧空间
		{
			//允许头插或尾插
			assert(pos >= _start && pos <= _finish);
			
			//判断扩容
			if (_finish == _end_of_storage)
				reserve(capacity() == 0 ? 5 : capacity() * 2);
			
			//从后往前拷贝
			iterator cur = _finish;
			iterator pre = _finish - 1;
			while (cur != pos)
			{
				*cur = *pre;
				--pre;
				--cur;
			}
			//当cur == pos，说明所有数据挪好了

			//放置数据，更新_finish
			*pos = val;
			++_finish;
		}*/
		
		//错误2 函数形参的iterator改为引用
		/*void insert(iterator& pos, const T& val)
		{
			//允许头插或尾插
			assert(pos >= _start && pos <= _finish);

			//先计算当前pos与_start的相对位置
			size_t relative_pos = pos - _start;

			//保证扩容后，pos指向的相对位置与之前的一致
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 5 : capacity() * 2);
				pos = _start + relative_pos;//一定要更新pos
			}
			//接下来正常拷贝

			//从后往前拷贝
			iterator cur = _finish;
			iterator pre = _finish - 1;
			while (cur != pos)
			{
				*cur = *pre;
				--pre;
				--cur;
			}
			//当cur == pos，说明所有数据挪好了

			//放置数据，更新_finish
			*pos = val;
			++_finish;
		}*/

		//先计算扩容前pos与_start的相对位置，发生扩容后修改pos
		iterator insert(iterator pos, const T& val)
		{
			//允许头插或尾插
			assert(pos >= _start && pos <= _finish);

			//先计算当前pos与_start的相对位置
			size_t relative_pos = pos - _start;

			//保证扩容后，pos指向的相对位置与之前的一致
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 5 : capacity() * 2);
				pos = _start + relative_pos;//一定要更新pos
			}
			//接下来正常拷贝

			//从后往前拷贝
			iterator cur = _finish;
			iterator pre = _finish - 1;
			while (cur != pos)
			{
				*cur = *pre;
				--pre;
				--cur;
			}
			//当cur == pos，说明所有数据挪好了

			//放置数据，更新_finish
			*pos = val;
			++_finish;

			//返回新插入数据的迭代器位置
			return pos;
		}

		//删除pos位置的数据
		iterator erase(iterator pos)
		{
			assert(size() > 0);
			assert(pos >= _start);
			assert(pos < _finish);
			//把后面的数据往前挪动
			iterator pre = pos;
			iterator cur = pos + 1;
			while (cur != _finish)
			{
				*pre = *cur;
				++pre;
				++cur;
			}
			--_finish;

			//返回 被删除元素 的 下一个元素 的 迭代器位置，仍然是pos
			return pos;
		}

	private:
		iterator _start;  //指向第一个数据
		iterator _finish; //指向最后一个数据的下一个位置
		iterator _end_of_storage;//指向当前开的空间的末尾
	};
}