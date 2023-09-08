#pragma once
#include <string.h>
#include <assert.h>
namespace lyh
{
	int bufferSize = 10;
	template<class T, class Ref, class Ptr>
	struct dequeIterator
	{
	public:    //��Ա����
		//�������ݵ�ָ��
		T* _cur;

		//��ʶ ������������buffer �Ŀ�ʼ�ͽ���
		T* _first;
		T* _last;

		//��������ַ���飬��n��λ�ñ����˵�ǰbuffer�׵�ַ����ʶ�õ�n��λ�õĵ�ַ
		//Ҳ��Ϊ�п���
		T** _buffer_adr_array_n;
	public:
		typedef dequeIterator<T, Ref, Ptr> Iterator;

		//��deque��������ݵĵ�ַ����ά����ǰ���ݻ��������п�����������iterator
		dequeIterator(T* val,T** buffer_adr_array_n)
		{
			_cur = val;
			_buffer_adr_array_n = buffer_adr_array_n;
			if (_cur != nullptr)
			{
				_first = *buffer_adr_array_n;
				_last = *buffer_adr_array_n + bufferSize;
			}
			else
			{
				_first = nullptr;
				_last = nullptr;
			}
		}

		//Iterator it;
		//++it
		//���õ�����ָ����һ��Ԫ��
		//˼·��++_cur�����_cur != _last��˵��û�г�����ǰbuffer
		//���_cur == _last��˵��Ҫ��ת����һ��buffer�׵�ַ
		Iterator& operator++()
		{
			++_cur;
			if (_cur == _last)
			{
				T* nextBuffer = *(++_buffer_adr_array_n);
				_cur = nextBuffer;
				//��ת�Ժ�Ҫ���±�ʶ�߽�
				_first = nextBuffer;
				_last = nextBuffer + bufferSize;
			}
			return *this;
		}

		//--it
		//���õ�����ָ��ǰһ��Ԫ��
		//˼·�����ж�_cur == _first
		//��� _cur !=_first, ֻ��Ҫ--_cur
		//_cur = _first, ��ת����һ��buffer��βԪ��
		Iterator operator--()
		{
			if (_cur != _first)
			{
				--_cur;
				return *this;
			}
			else
			{
				T* preBuffer = *(--_buffer_adr_array_n);
				_cur = preBuffer + bufferSize - 1;
				_first = preBuffer;
				_last = preBuffer + bufferSize;
				return *this;
			}
		}

		//it += 5
		Iterator& operator+=(int step)
		{
			//���õ�������_cur��ʼ ��ǰ��step���������ָ��λ��
			//˼·��_cur + step ���� _first + (_cur - _first) + step
			// �õ�������_first��ʼ ��ǰ�ߡ� (_cur - _first) + step�� ��

			size_t offset = _cur - _first + step;
			if (offset < bufferSize)
			{
				//û�г�����ǰ����buffer
				_cur += step;
			}
			else
			{
				//��_first��ʼ����Ҫ�Ĳ�������Խ�˼���buffer
				size_t bufferNum = offset / bufferSize;
				//����Ĳ�����������������buffer��λ��
				size_t pos = offset % bufferSize;

				_buffer_adr_array_n += bufferNum;
				_cur = *_buffer_adr_array_n + pos;
				_first = *_buffer_adr_array_n;
				_last = *_buffer_adr_array_n + bufferSize;
			}
			return *this;
		}

		Iterator operator+(int step)
		{
			Iterator tmp = *this;
			tmp += step;
			return tmp;
		}

		// it2 - it1 Ĭ��it2ָ������Ԫ�أ������������������ľ��� 
		size_t operator-(const Iterator& it1)
		{
			//�����ͬһ��buffer��
			if (it1._buffer_adr_array_n == _buffer_adr_array_n)
			{
				return _cur - it1._cur;
			}
			else
			{
				//it1����buffer��ʣ��Ԫ�� + it2����buffer��ʣ��Ԫ�� + ֮������buffer������Ԫ��
				int num2 = _cur - _first;
				int num1 = it1._finish - it1._cur;
				int tmp = (_buffer_adr_array_n - (it1._buffer_adr_array_n + 1)) * bufferSize;
				return num1 + num2 + tmp;
			}
		}

		bool operator==(const Iterator& it1)
		{
			return _cur == it1._cur;
		}

		bool operator!=(const Iterator& it1)
		{
			return _cur != it1._cur;
		}

		bool operator<(const Iterator& it1)
		{
			return _buffer_adr_array_n < it1._buffer_adr_array_n;
		}
		bool operator>=(const Iterator& it1)
		{
			return !(*this < it1);
		}
		bool operator<=(const Iterator& it1)
		{
			return (*this == it1) || (*this < it1);
		}
		bool operator>(const Iterator& it1)
		{
			return !(*this <= it1);
		}

		Ref operator*()
		{
			return *_cur;
		}

		Ptr operator->()
		{
			return _cur;
		}

		Ref operator[](size_t n)
		{
			return *(*this + n);
		}

	};

	template<class T>
	class deque
	{
	public:
		typedef dequeIterator<T, T&, T*> iterator;
	private:
		iterator _start;
		iterator _finish;
		T** _buffer_adr_array;//�п�����
		size_t _array_size;//�����С
	public:
		deque()
			:_start(nullptr,nullptr)
			,_finish(nullptr,nullptr)
		{
			_array_size = 3;
			_buffer_adr_array = new T * [3];
			memset(_buffer_adr_array, 0, sizeof(T*) * 3);
		}


		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}

		void push_back(const T& val)
		{
			//Ԫ��Ϊ��ʱ
			if (_start == _finish)
			{
				//ֻ���п����飬��û�������κ�buffer
				//������buffer���п�������м俪ʼ�洢buffer��ַ
				size_t arrayMid = (0 + _array_size) / 2;
				_buffer_adr_array[arrayMid] = new T[bufferSize];
				*(_buffer_adr_array[arrayMid]) = val;

				//_buffer_adr_array[arrayMid]����Ԫ�ص�ַ
				//_buffer_adr_array + arrayMid����Ӧ���п���
				iterator newStart(_buffer_adr_array[arrayMid], _buffer_adr_array + arrayMid);
				_start = newStart;
				_finish = newStart + 1;
			}
			//Ԫ�ز�Ϊ��
			else
			{
				//�ҵ����һ��Ԫ��
				*_finish = val;
				++_finish;
			}
		}

		/*void pop_back()
		{
			assert(_start != _finish);
			--_finish;
		}

		void push_front(const T& val)
		{
			if (_start == _finish)
			{
				//���п���������ռ䣬�����洢buffer��ַ
				_buffer_adr_array = new T * [_array_size];
				memset(_buffer_adr_array, 0, sizeof(T*) * _array_size);
				int arrayMid = (0 + _array_size) / 2;
				_buffer_adr_array[arrayMid] = new T[bufferSize];
				iterator newStart(_buffer_adr_array[arrayMid], _buffer_adr_array + arrayMid);
				_start = newStart;
				_finish = newStart + 1;
			}
			else
			{
				--_start;
				*_start = val;
			}
		}

		void pop_front()
		{
			assert(_start != _finish);
			++_start;
		}*/

		//iterator insert(iterator pos, const T& val)
		//{
		//	if (pos == _start)
		//	{
		//		push_front(val);
		//		return _start;
		//	}
		//	//˫�˶��������ˣ�ѡ�����ݽ�С��һ�ˣ�Ų����һ�˵�����
		//	size_t left = pos - _start;
		//	if (left < size()/2)
		//	{
		//		//��������٣�Ų�����
		//		iterator beginMove = _start;
		//		while (beginMove <= pos)
		//		{
		//			*(beginMove - 1) = *beginMove;
		//			++beginMove;
		//		}
		//		*pos = val;
		//	}
		//	else
		//	{
		//		iterator beginMove = _finish;
		//		while (beginMove > pos)
		//		{
		//			*beginMove = *(beginMove - 1);
		//			--beginMove;
		//		}
		//		++_finish;
		//		*pos = val;
		//	}
		//	return pos;
		//}

		//iterator erase(iterator pos)
		//{
		//	assert(_start != _finish);
		//	//ѡ�����ݽ�С��һ�ˣ�Ų����һ�˵�����
		//	if (pos == _start)
		//	{
		//		pop_front();
		//		return _start;
		//	}
		//	else if (pos = _finish - 1)
		//	{
		//		pop_back();
		//		return _finish;
		//	}
		//	else
		//	{
		//		size_t left = pos - _start;
		//		if (left < size() / 2)
		//		{
		//			iterator beginMove = pos;
		//			while (beginMove != _start)
		//			{
		//				*beginMove = *(beginMove - 1);
		//				--beginMove;
		//			}
		//		}
		//		else
		//		{
		//			iterator beginMove = pos + 1;
		//			while (beginMove != _finish)
		//			{
		//				*(beginMove - 1) = *beginMove;
		//				++beginMove;
		//			}
		//		}
		//	}
		//}

		size_t size()const
		{
			return _finish - _start;
		}
	};
}