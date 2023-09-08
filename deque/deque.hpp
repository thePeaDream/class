#pragma once
#include <string.h>
#include <assert.h>
namespace lyh
{
	int bufferSize = 10;
	template<class T, class Ref, class Ptr>
	struct dequeIterator
	{
	public:    //成员变量
		//具体数据的指针
		T* _cur;

		//标识 具体数据所在buffer 的开始和结束
		T* _first;
		T* _last;

		//缓冲区地址数组，第n个位置保存了当前buffer首地址，标识该第n个位置的地址
		//也称为中控器
		T** _buffer_adr_array_n;
	public:
		typedef dequeIterator<T, Ref, Ptr> Iterator;

		//用deque里具体数据的地址，和维护当前数据缓冲区的中控器，来构造iterator
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
		//即让迭代器指向下一个元素
		//思路：++_cur，如果_cur != _last，说明没有超过当前buffer
		//如果_cur == _last，说明要跳转到下一个buffer首地址
		Iterator& operator++()
		{
			++_cur;
			if (_cur == _last)
			{
				T* nextBuffer = *(++_buffer_adr_array_n);
				_cur = nextBuffer;
				//跳转以后，要重新标识边界
				_first = nextBuffer;
				_last = nextBuffer + bufferSize;
			}
			return *this;
		}

		//--it
		//即让迭代器指向前一个元素
		//思路：先判断_cur == _first
		//如果 _cur !=_first, 只需要--_cur
		//_cur = _first, 跳转到上一个buffer的尾元素
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
			//即让迭代器从_cur开始 向前走step步，求得新指向位置
			//思路：_cur + step 看成 _first + (_cur - _first) + step
			// 让迭代器从_first开始 向前走【 (_cur - _first) + step】 步

			size_t offset = _cur - _first + step;
			if (offset < bufferSize)
			{
				//没有超过当前所在buffer
				_cur += step;
			}
			else
			{
				//从_first开始，需要的步数，跨越了几个buffer
				size_t bufferNum = offset / bufferSize;
				//多出的步数，就是最终所在buffer的位置
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

		// it2 - it1 默认it2指向后面的元素，返回两个迭代器相差的距离 
		size_t operator-(const Iterator& it1)
		{
			//如果在同一个buffer中
			if (it1._buffer_adr_array_n == _buffer_adr_array_n)
			{
				return _cur - it1._cur;
			}
			else
			{
				//it1所在buffer的剩下元素 + it2所在buffer的剩下元素 + 之间完整buffer的所有元素
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
		T** _buffer_adr_array;//中控数组
		size_t _array_size;//数组大小
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
			//元素为空时
			if (_start == _finish)
			{
				//只有中控数组，但没有申请任何buffer
				//申请新buffer，中控数组从中间开始存储buffer地址
				size_t arrayMid = (0 + _array_size) / 2;
				_buffer_adr_array[arrayMid] = new T[bufferSize];
				*(_buffer_adr_array[arrayMid]) = val;

				//_buffer_adr_array[arrayMid]：首元素地址
				//_buffer_adr_array + arrayMid：对应的中控器
				iterator newStart(_buffer_adr_array[arrayMid], _buffer_adr_array + arrayMid);
				_start = newStart;
				_finish = newStart + 1;
			}
			//元素不为空
			else
			{
				//找到最后一个元素
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
				//给中控数组申请空间，用来存储buffer地址
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
		//	//双端队列是两端，选择数据较小的一端，挪动那一端的数据
		//	size_t left = pos - _start;
		//	if (left < size()/2)
		//	{
		//		//左端数据少，挪动左边
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
		//	//选择数据较小的一端，挪动那一端的数据
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