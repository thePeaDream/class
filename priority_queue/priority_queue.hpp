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
		//���Զ������ͣ���ʼ���б��ȥ��������Ĭ�Ϲ���
		priority_queue(){}
		
		//��һ�ε��������乹��
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		{
			//�൱�ڽ��ѣ�������������µ����㷨ΪO(N)

			while (first != last)
			{
				_con.push_back(*first);
				++first;
			}

			//�ӵ�����һ����Ҷ�ӽ�㿪ʼ��ʹ�����µ����㷨����
			for (int i = (size() - 1 - 1) / 2; i >= 0; --i)
			{
				//size() - 1�����һ�����λ�ã�(size()-1 - 1) / 2�����һ�����ĸ����
				adjustDown(i);
			}
		}
		
		
		//�����ȼ����в������ݣ������֤����Ȼ��һ����
		//ʹ�����ϵ����㷨
		void push(const T& val)
		{
			_con.push_back(val);
			adjustUp(_con.size() - 1);
		}
		//��posλ��Ԫ�أ����ϵ������Ƚ������������Ƚ�㣩
		void adjustUp(size_t pos)
		{
			static Compare compare;

			size_t parent = (pos - 1) / 2;
			//��pos = 0,û�и��׽�㣬���������ϵ���
			while (pos > 0)
			{
				//С�ڽ���ѣ�Ĭ�Ͻ����
				if (compare(_con[parent], _con[pos]))//Ĭ����_con[parent] < _con[pos]
				{
					//pos���ϵ���
					std::swap(_con[parent], _con[pos]);

					//����pos������parent
					pos = parent;
					parent = (pos - 1) / 2;
				}
				else
					break;
			}
		}
		
		//ɾ���Ѷ����ݣ�һ������ѡ�������С��Ԫ��
		//1 ���� �Ѷ�Ԫ�غ�βԪ��
		//2 βɾ
		//3 �Դ�ʱ�Ѷ����� �����µ����㷨
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
			//ǰ������ߺ��ұ߶��Ǵ�ѻ�С��

			//��û������ʱ����������
			size_t mChild = 2 * pos + 1;
			while (mChild < size())
			{
				if (mChild + 1 < _con.size() && compare(_con[mChild], _con[mChild + 1]) )//Ĭ����_con[mChild] < _Con[mChild+1]
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
