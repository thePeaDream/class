#pragma once
#include <deque>
namespace lyh
{
	template<class T, class Container = std::deque<T>>
	class queue
	{
	public:
		//入队列
		void push(const T& val)
		{
			_con.push_back(val);
		}

		//出队列
		void pop()
		{
			_con.pop_front();
		}
		
		//队头
		T& front()
		{
			return _con.front();
		}

		//队尾
		T& back()
		{
			return _con.back();
		}

		//判空
		bool empty()
		{
			return _con.empty();
		}

		size_t size()
		{
			return _con.size();
		}
	private:
		Container _con;
	};
}