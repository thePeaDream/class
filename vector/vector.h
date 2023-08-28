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
		//vector�ײ��Ǹ����������飬����������ԭ��ָ��
		typedef T* iterator;
		typedef const T* const_iterator;

		//Ĭ�Ϲ���
		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		//��n��val����
		vector(size_t n, const T& val)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			//���ռ�+��ʼ���ռ�
			T* tmp = new T[n];
			for (size_t i = 0; i < n; ++i)
				tmp[i] = val;

			//���³�Ա����
			_start = tmp;
			_finish = _start + n;
			_end_of_storage = _finish;//��ʼ�����ͳ�ʼ���ݸ���һ��
		}

		//������vector<int> v2(3,1)ʱ;
		//���ڱ������������ƥ��ĺ���������õ����������乹��ĺ���
		//��Ϊ�ú���������ģ���������ͬ������ȥ����vector(size_t n, const T& val)
		//���Զ��ṩһ��vector(int n, const T& val)
		vector(int n, const T& val)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			//���ռ�+��ʼ���ռ�
			T* tmp = new T[n];
			for (size_t i = 0; i < n; ++i)
				tmp[i] = val;

			//���³�Ա����
			_start = tmp;
			_finish = _start + n;
			_end_of_storage = _finish;//��ʼ�����ͳ�ʼ���ݸ���һ��
		}

		//��һ�ε��������乹��
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			//Ԫ�ظ���
			size_t n = last - first;
			
			//���ռ�+��������
			T* tmp = new T[n];
			for (size_t i = 0; i < n; ++i)
			{
				tmp[i] = first[i];
			}
			//���³�Ա����
			_start = tmp;
			_finish = tmp + n;
			_end_of_storage = tmp + n;
		}

		//1 �ֶ���������
		/*vector(const vector<T>& v)
			:_start(nullptr)
			,_finish(nullptr)
			,_end_of_storage(nullptr)
		{
			//���ռ䣬��������
			T* tmp = new T[v.capacity()];
			//Ҳ������v.size()

			//memcpyʵ�ֵ�ǳ������������vector<vector<int>> vv��
			//vector�ڲ�����ǳ����T���ͣ�Ҳ���������
			//����memcpy(tmp, v._start, sizeof(T) * v.size());
			
			for (size_t i = 0; i < v.size(); i++)
			{
				tmp[i] = v[i]; //�൱���ڲ�����T���͵ĸ�ֵ���������������

				//ע��(const vector<T>����)v����const���͵�[]��������أ�û�лᱨ��
			}

			//���³�Ա����
			_start = tmp;
			_finish = tmp + v.size();
			_end_of_storage = tmp + v.capacity();
		}*/

		void swap(vector<T>& tmp)
		{
			//�������г�Ա����
			std::swap(tmp._start, _start);
			std::swap(tmp._finish, _finish);
			std::swap(tmp._end_of_storage, _end_of_storage);
		}

		//2 �����еĹ��캯��������������
		vector(const vector<T>& v)
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			//����֮ǰд�ĵ��������乹�캯��
			vector<T> tmp(v.begin(), v.end());
			
			//����tmp��this�����г�Ա����
			swap(tmp);
			//ֱ���ÿ����swap����2�������,�����vector<T>��1�ο������죬��vector<T>��2�θ�ֵ���������
			//�����ڲ�дһ��swap���ڽ���������ĳ�Ա��������
		}

		//1 ��ֵ��������أ��ֶ�����
		/*vector<T>& operator=(const vector<T>& v)
		{
			//�������Ҹ�ֵ�Ŵ���
			if (&v != this)
			{
				//���ռ�+��������
				T* tmp = new T[v.capacity()];

				//�뿽���������ƣ�����ǳ����T����
				//memcpy(tmp, v._start, v.size() * sizeof(T));
				for (size_t i = 0; i < v.size(); ++i)
				{
					tmp[i] = v[i];
				}

				//�ͷžɿռ�
				delete[] _start;

				//����this�ĳ�Ա����
				_start = tmp;
				_finish = tmp + v.size();
				_end_of_storage = tmp + v.capacity();
			}
			return *this;
		}*/
		//2 ��ֵ��������أ����ÿ�������ʵ��
		vector<T>& operator=(vector<T> v)
		{
			//�βο�������ʵ�Σ���ʱv����this��Ҫ��

			//this�ĳ�Ա������v�ĳ�Ա��������
			//���β�v�ں������ý������æ����ɿռ�
			swap(v);
			return *this;
		}
		//����
		~vector()
		{
			//std::cout << "�ɹ�������������" << std::endl;//��������֤
			delete[] _start;
		}

		//������С
		size_t size()const
		{
			return _finish - _start;
		}
		size_t capacity()const
		{
			return _end_of_storage - _start;
		}

		//�������ݸ���Ϊn�������ӵ����ݳ�ʼ��Ϊval
		void resize(size_t n, const T& val)
		{
			//(1) n > ��ǰ������
			if (n > size())
			{
				//����+��ʼ��
				reserve(n);
				for (size_t i = size(); i < n; i++)
					_start[i] = val;

				_finish = _start + n;
			}
			//(2) n < ��ǰ������
			else if (n < size())
			{
				//ɾ�����n������
				_finish = _start + n;
			}
			//(3) n =��ǰ���������޲���
			else{}
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				//���ռ䣬��������
				T* newBlock = new T[n];
				for (size_t i = 0; i < size(); ++i)
				{
					newBlock[i] = _start[i];
				}
				//memcpy(newBlock, _start, sizeof(T) * size());
				
				//��¼��ǰsize()��ֵ����Ϊ���ڲ���_finish - _start������ģ����³�Ա����ʱ������ʹ��size()
				size_t st = size();

				//�ͷžɿռ�
				delete[] _start;

				//���³�Ա����
				_start = newBlock;
				_finish = newBlock + st;
				_end_of_storage = newBlock + n;
			}
		}

		//const���ÿ������ó������ݡ�������ʽ����ת���м��������ʱ����
		//���ü��ٿ���
		//β��
		void push_back(const T& x)
		{
			//1 �������
			if (_finish == _end_of_storage)
				reserve(capacity() ==   0 ?  5 : 2 * capacity() );
			//2 ��������
			*_finish = x;
			++_finish;
		}
		//βɾ
		void pop_back()
		{
			assert(size() > 0);
			--_finish;
		}

		//����
		//[]���������
		T& operator[](size_t n)
		{
			//����Ƿ�Խ�����
			assert(n < size());
			return *(_start + n);
		}

		//const[]���������
		const T& operator[](size_t n)const
		{
			//����Ƿ�Խ�����
			assert(n < size());
			return *(_start + n);
		}

		//������
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
		
		//����λ�ò����ɾ�� ��������������ʧЧ��
		//��һ�ֲ���ʵ�֣���posλ��֮ǰ����val ������1��
		/*void insert(iterator pos, const T& val)//���������ݣ�_start�ȳ�Ա����ȫ��ָ��ȫ�µĿռ䣬������ȥ��pos��Ȼָ��ɿռ�
		{
			//����ͷ���β��
			assert(pos >= _start && pos <= _finish);
			
			//�ж�����
			if (_finish == _end_of_storage)
				reserve(capacity() == 0 ? 5 : capacity() * 2);
			
			//�Ӻ���ǰ����
			iterator cur = _finish;
			iterator pre = _finish - 1;
			while (cur != pos)
			{
				*cur = *pre;
				--pre;
				--cur;
			}
			//��cur == pos��˵����������Ų����

			//�������ݣ�����_finish
			*pos = val;
			++_finish;
		}*/
		
		//����2 �����βε�iterator��Ϊ����
		/*void insert(iterator& pos, const T& val)
		{
			//����ͷ���β��
			assert(pos >= _start && pos <= _finish);

			//�ȼ��㵱ǰpos��_start�����λ��
			size_t relative_pos = pos - _start;

			//��֤���ݺ�posָ������λ����֮ǰ��һ��
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 5 : capacity() * 2);
				pos = _start + relative_pos;//һ��Ҫ����pos
			}
			//��������������

			//�Ӻ���ǰ����
			iterator cur = _finish;
			iterator pre = _finish - 1;
			while (cur != pos)
			{
				*cur = *pre;
				--pre;
				--cur;
			}
			//��cur == pos��˵����������Ų����

			//�������ݣ�����_finish
			*pos = val;
			++_finish;
		}*/

		//�ȼ�������ǰpos��_start�����λ�ã��������ݺ��޸�pos
		iterator insert(iterator pos, const T& val)
		{
			//����ͷ���β��
			assert(pos >= _start && pos <= _finish);

			//�ȼ��㵱ǰpos��_start�����λ��
			size_t relative_pos = pos - _start;

			//��֤���ݺ�posָ������λ����֮ǰ��һ��
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 5 : capacity() * 2);
				pos = _start + relative_pos;//һ��Ҫ����pos
			}
			//��������������

			//�Ӻ���ǰ����
			iterator cur = _finish;
			iterator pre = _finish - 1;
			while (cur != pos)
			{
				*cur = *pre;
				--pre;
				--cur;
			}
			//��cur == pos��˵����������Ų����

			//�������ݣ�����_finish
			*pos = val;
			++_finish;

			//�����²������ݵĵ�����λ��
			return pos;
		}

		//ɾ��posλ�õ�����
		iterator erase(iterator pos)
		{
			assert(size() > 0);
			assert(pos >= _start);
			assert(pos < _finish);
			//�Ѻ����������ǰŲ��
			iterator pre = pos;
			iterator cur = pos + 1;
			while (cur != _finish)
			{
				*pre = *cur;
				++pre;
				++cur;
			}
			--_finish;

			//���� ��ɾ��Ԫ�� �� ��һ��Ԫ�� �� ������λ�ã���Ȼ��pos
			return pos;
		}

	private:
		iterator _start;  //ָ���һ������
		iterator _finish; //ָ�����һ�����ݵ���һ��λ��
		iterator _end_of_storage;//ָ��ǰ���Ŀռ��ĩβ
	};
}