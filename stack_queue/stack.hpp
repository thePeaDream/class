#pragma once
#include <deque>
namespace lyh
{
	template<class T, class Container = std::deque<T>>
	class stack
	{
	public:
		void push(const T& val)//»Î’ª
		{
			_con.push_back(val);
		}

		void pop()//≥ˆ’ª
		{
			_con.pop_back();
		}

		T& top()//’ª∂•
		{
			return _con.back();
		}

		bool empty()//≈–ø’
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