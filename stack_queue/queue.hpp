#pragma once
#include <deque>
namespace lyh
{
	template<class T, class Container = std::deque<T>>
	class queue
	{
	public:
		//�����
		void push(const T& val)
		{
			_con.push_back(val);
		}

		//������
		void pop()
		{
			_con.pop_front();
		}
		
		//��ͷ
		T& front()
		{
			return _con.front();
		}

		//��β
		T& back()
		{
			return _con.back();
		}

		//�п�
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