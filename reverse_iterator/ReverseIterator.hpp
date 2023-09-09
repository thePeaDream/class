#pragma once
//用一个迭代器类型，构造反向迭代器
//反向迭代器是一个迭代器适配器
//提供list的迭代器，就能适配出list的反向迭代器
//提供vector的迭代器，就能适配出vector的反向迭代器
namespace yh
{
	template<class Iterator, class Ref, class Ptr>
	class Reverse_Iterator
	{
	private:
		//成员属性
		Iterator _it;
		typedef Reverse_Iterator<Iterator,Ref, Ptr> RIterator;
	public:
		Reverse_Iterator(Iterator it)
			:_it(it)
		{}

		RIterator& operator++()
		{
			//反向迭代器++，就--封装的_it
			--_it;
			return *this;
		}

		RIterator& operator--()
		{
			//反向迭代器--，就++封装的_it
			++_it;
			return *this;
		}

		Ref operator*()const
		{
			//实现 反向迭代器的rbegin() 就是 正向迭代器的end()
			// 反向迭代器的rend() 就是 正向迭代器的begin()
			// 反向迭代器所指的位置 其实是 前一个元素
			Iterator tmp = _it;
			--tmp;
			return *tmp;
		}

		Ptr operator->()
		{
			return _it.operator->();
		}

		bool operator!=(const RIterator& rit)//作为const成员函数会报错？没有找到接受“const Iterator”类型的左操作数的运算符(或没有可接受的转换)
		{
			return _it != rit._it;
		}
		bool operator==(const RIterator& rit)
		{
			return _it == rit._it;
		}

	};
}