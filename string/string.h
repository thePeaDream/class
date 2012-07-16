#pragma once
#include <string.h>
#include <iostream>
#include <assert.h>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;


namespace yh
{
	class string
	{
	public:
		/*string()
			:_str(nullptr)
			,_size(0)
			,_capacity(0)
		{}*/

		/*string()
			:_str(new char[1])
			,_size(0)
			,_capacity(0)
		{
			_str[0] = '\0';
		}
		
		string(const char* str)//用常量字符串初始化string
			//:_str(str) 权限的扩大
			:_str(new char[strlen(str)+1])//开空间，注意'\0'
			,_size(strlen(str))
			,_capacity(strlen(str))
		{
			strcpy(_str, str);
		}*/
		//构造函数
		string(const char* str = "")
		{
			//只调用一次strlen
			int size = strlen(str);
			_capacity = _size = size;

			_str = new char[_capacity + 1];

			strcpy(_str, str);
		}
		const char* c_str()const
		{
			return _str;
		}
		~string()
		{
			delete[] _str;
		}

		size_t size()const
		{
			return _size;
		}

		//[]运算符重载
		char& operator[](size_t pos)
		{
			//检查越界
			assert(pos < _size);
			return _str[pos];
		}

		//const string对象
		const char& operator[](size_t pos)const
		{
			//检查越界
			assert(pos < _size);
			return _str[pos];
		}

		//迭代器[左闭右开)
		//string的迭代器就是原生指针
		typedef char* iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}

		typedef const char* const_iterator;
		const_iterator begin()const
		{
			return _str;
		}
		const_iterator end()const
		{
			return _str + _size;
		}
		
		/*string(const string& str)
			:_size(str._size)
			,_capacity(str._capacity)
		{
			//开新空间，多开一个给'\0'
			_str = new char[_capacity + 1];

			//把str的内容拷贝到新空间
			strcpy(_str, str._str);
		}*/
		
		//拷贝构造
		

		//s1 = s2
		/*string& operator=(const string& str)
		{
			if (this != &str)//如果不是自我赋值
			{
				//先开新空间拷贝数据，new失败后，不会破坏_str
				char* tmp = new char[str._capacity + 1];
				strcpy(tmp, str._str);

				//把this原来的空间释放
				delete[] _str;

				_str = tmp;
				_size = str._size;
				_capacity = str._capacity;
			}
			return *this;
		}*/
	
		//现代写法
		//s2(s1)
		void swap(string& s)
		{
			//该交换函数，用来交换两个对象的所有成员
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		
		string(const string& str)
		{
			//调用已有的string(const char* str = "")构造临时tmp
			string tmp(str._str);

			//然后*this和tmp所有成员进行交换
			this->swap(tmp);

			//因为tmp是局部对象，出了作用域调用析构函数，
			//与*this交换所得的空间是随机值，会崩溃
			//所以交换后要修改tmp,阻止上述情况发生
			tmp._str = nullptr;//delete[]内部有检查空指针，为空什么都不干
		}
		
		//s2 = s1
		string& operator=(string str)//调用拷贝构造生成str
		{
			swap(str);
			//str是局部对象，出了作用域自动销毁，帮助释放原来s2的旧空间
			return *this;
		}

		//开存储n个有效字符的空间，不会缩容
		void reserve(size_t n)
		{
			//如果需要的空间n大于当前容量
			if (n > _capacity)
			{
				//开新空间，把旧空间的数据拷贝过去
				char* tmp = new char[n+1];
				strcpy(tmp, _str);
				//释放旧空间
				delete _str;

				//更新当前对象*this的成员
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char x)
		{
			if (_capacity == _size)
			{
				//注意_capacity初始值为0的情况
				reserve(_capacity == 0 ? 5 : _capacity * 2);
			}
			//放数据
			_str[_size] = x;
			++_size;
			//注意'\0'
			_str[_size] = '\0';
		}

		string& operator+=(char x)
		{
			//复用push_back
			push_back(x);
			return *this;
		}

		void append(const char* str)
		{
			size_t length = strlen(str);

			//此时的容量必须能存下所有字符
			if (_capacity < _size + length)
			{
				reserve(_size + length);
			}
			//_str+_size 即string最后一个有效数据的下一个位置
			strcpy(_str + _size, str);
			_size += length;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		//在pos位置插入一个字符
		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);//=_size相当于尾插
			reserve(_size + 1);//判断扩容
			
			//从后往前挪数据
			//把前一个位置的字符赋值给当前位置的字符
			size_t pre = _size - 1;
			size_t  cur= _size;//初始位置为'\0'
			while(cur > pos)
			{
				//把 前一个位置数据 挪到 当前位置
				_str[cur] = _str[pre];
				pre--;
				cur--;
			}
			//修改pos位置数据，并++_size
			_str[pos] = ch;
			++_size;

			//最后一个字符的下一个位置为'\0'
			_str[_size] = '\0';
			
			return *this;
		}
		//在pos位置插入一个字符串
		string& insert(size_t pos, const char* str)
		{
			//插入位置判断
			assert(pos <= _size);

			//如果是空串，不进行操作
			if (strlen(str) == 0)
				return *this;
			//扩容判断
			size_t length = strlen(str);
			reserve(length + _size);

			//前后两个指针，
			size_t cur= _size + length;
			size_t pre = _size;
			while (cur > pos+length - 1)
			{
				_str[cur] = _str[pre];
				--cur;
				--pre;
			}
			for (int i = 0; i < length; i++)
			{
				_str[pos + i] = str[i];
			}
			_size += length;
			return *this;
		}

		//从pos位置开始删除len个字符
		string& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);

			//删到结尾的情况
			if (len == npos || pos + len - 1  >= _size )
			{
				_size = pos;
				_str[_size] = '\0';
			}
			//删除某个区间的所有字符
			else if(len > 0)
			{
				//开始删除的位置(对应要挪到的位置pos ~_size - 1 - len)
				size_t pre = pos;
				//开始向前挪动位置(要向前挪动的区间pos+len ~ _size - 1)
				size_t cur = pre + len;

				while (cur <= _size - 1)
				{
					_str[pre] = _str[cur];
					++pre;
					++cur;
				}

				//挪完后更新_size
				_size -= len;
				_str[_size] = '\0';
			}
			return *this;
		}

		size_t capacity()const
		{
			return _capacity;
		}
		size_t find(char c, size_t pos = 0)const
		{
			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == c)
					return i;
			}
			return npos;
		}
		size_t find(const char* sub, size_t pos = 0)const
		{
			//复用c语言库的strstr
			//const char* strstr(const char* str1, const char* str2);
			//char* strstr(char* str1, const char* str2);
			//如果str2是str1的子串，返回str1对应指针位置，否则返回NULL

			const char* tmp = strstr(_str + pos, sub);
			if (tmp == nullptr)
			{
				return npos;
			}
			else
			{
				return (tmp - _str);//指针-指针起始就是其下标位置，因为它们是连续物理空间
			}
		}
		void resize(size_t n, char ch = '\0')
		{		
			if (n == _size)//不处理
				return;
			else if (n < _size)//删除数据
			{
				_size = n;
				_str[_size] = '\0';
			}
			else//扩容，同时初始化多出的空间
			{
				reserve(n);
				for (size_t i = _size; i < n; i++)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}
private:
		const static size_t npos = -1;
		char* _str;//指向动态开辟的空间
		size_t _size;//当前有效字符的个数
		size_t _capacity;//当前存储有效字符的空间大小，不包含'\0'
	};

	//1 不能实现为成员函数，如果实现为成员函数,this指针抢占左操作数
	//2 不一定要实现为string的友元函数，因为不需要访问string的私有成员
	ostream& operator<<(ostream& out, const string& str)
	{
		for (int i = 0; i < str.size(); i++)
		{
			out << str[i];
		}
		//支持连续流插入
		return out;
	}

	/*istream& operator>>(istream& in, string& str)
	{
		char ch;
		//in >> ch;
		//cin是会忽略掉输入的空格或者换行，不会把空格和换行交给ch
		str = "";
		ch = in.get();//它有一个get()成员函数，可以逐个字符读取
		while (ch != ' ' && ch != '\n')
		{
		 //但是逐个插入，扩容频繁，效率不高
			str += ch;
			ch = in.get();
		}
		//在接收输入的数据时，cin默认以' '或'\n' 作为数据的分割符，但cin不会去接收它们
		return in;
	}*/
	//解决扩容频繁问题，在内部定义一个buff数组,一批一批去加
	istream& operator>>(istream& in, string& str)
	{
		str = "";
		char ch;
		ch = in.get();
		char buff[64];
		size_t i = 0;
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 63)
			{
				buff[i] = '\0';
				//如果缓冲区已满，就一次性给str，可以有效减少扩容的消耗
				str += buff;
				i = 0;
			}
			ch = in.get();
		}
	
		buff[i] = '\0';
		str += buff;
		return in;
	}
	

	//该函数在命名空间yh中
	void test25()
	{
		string s1("abcd");
		cout << s1.capacity() << endl;
		s1.reserve(100);
		cout << s1.capacity();
	}

	void test26()
	{
		string s1;
		s1 += 'a';
		s1 += "bcd";
	}

	void test27()
	{
		string s1("abc");
		cout << s1.c_str() << endl;
		s1.insert(0, 't');
		cout << s1.c_str() << endl;//"tabc"
		s1.insert(1, 'g');
		cout << s1.c_str() << endl;//"tgabc"
		
	}
	void test28()
	{
		string s2("aaa");
		s2.insert(1, "bc");//"abcaa"
		cout << s2.c_str() << endl;
		s2.insert(5, "gg");//"abcaagg"
		cout << s2.c_str() << endl;
		s2.insert(0, "uu");//"uuabcaagg"
		cout << s2.c_str() << endl;

		string s3;
		s3.insert(0, "");//插入空串
		cout << s3.c_str();
	}
	
	void test29()
	{
		string s1("abcdefgh");
		s1.erase(0, 2);//头删 "cdefgh"
		cout << s1.c_str() << endl;

		s1.erase(1, 2);//中间删"cfgh"
		cout << s1.c_str() << endl;
	}
	void test30()
	{
		string s1("abcdefg");
		string s2(".cpp");
		cout << s1<< s2<<endl;
	}
	void test31()
	{
		string s1;
		string s2;
		cin >> s1 >> s2;
		cout << s1 << endl;
		cout << s2 << endl;
	}
}
