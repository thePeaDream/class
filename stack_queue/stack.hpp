#pragma once
#include <deque>
namespace lyh
{
	template<class T, class Container = std::deque<T>>
	class stack
	{
	public:
		void push(const T& val)//��ջ
		{
			_con.push_back(val);
		}

		void pop()//��ջ
		{
			_con.pop_back();
		}

		T& top()//ջ��
		{
			return _con.back();
		}

		bool empty()//�п�
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