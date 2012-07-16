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
		
		string(const char* str)//�ó����ַ�����ʼ��string
			//:_str(str) Ȩ�޵�����
			:_str(new char[strlen(str)+1])//���ռ䣬ע��'\0'
			,_size(strlen(str))
			,_capacity(strlen(str))
		{
			strcpy(_str, str);
		}*/
		//���캯��
		string(const char* str = "")
		{
			//ֻ����һ��strlen
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

		//[]���������
		char& operator[](size_t pos)
		{
			//���Խ��
			assert(pos < _size);
			return _str[pos];
		}

		//const string����
		const char& operator[](size_t pos)const
		{
			//���Խ��
			assert(pos < _size);
			return _str[pos];
		}

		//������[����ҿ�)
		//string�ĵ���������ԭ��ָ��
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
			//���¿ռ䣬�࿪һ����'\0'
			_str = new char[_capacity + 1];

			//��str�����ݿ������¿ռ�
			strcpy(_str, str._str);
		}*/
		
		//��������
		

		//s1 = s2
		/*string& operator=(const string& str)
		{
			if (this != &str)//����������Ҹ�ֵ
			{
				//�ȿ��¿ռ俽�����ݣ�newʧ�ܺ󣬲����ƻ�_str
				char* tmp = new char[str._capacity + 1];
				strcpy(tmp, str._str);

				//��thisԭ���Ŀռ��ͷ�
				delete[] _str;

				_str = tmp;
				_size = str._size;
				_capacity = str._capacity;
			}
			return *this;
		}*/
	
		//�ִ�д��
		//s2(s1)
		void swap(string& s)
		{
			//�ý�����������������������������г�Ա
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}
		
		string(const string& str)
		{
			//�������е�string(const char* str = "")������ʱtmp
			string tmp(str._str);

			//Ȼ��*this��tmp���г�Ա���н���
			this->swap(tmp);

			//��Ϊtmp�Ǿֲ����󣬳����������������������
			//��*this�������õĿռ������ֵ�������
			//���Խ�����Ҫ�޸�tmp,��ֹ�����������
			tmp._str = nullptr;//delete[]�ڲ��м���ָ�룬Ϊ��ʲô������
		}
		
		//s2 = s1
		string& operator=(string str)//���ÿ�����������str
		{
			swap(str);
			//str�Ǿֲ����󣬳����������Զ����٣������ͷ�ԭ��s2�ľɿռ�
			return *this;
		}

		//���洢n����Ч�ַ��Ŀռ䣬��������
		void reserve(size_t n)
		{
			//�����Ҫ�Ŀռ�n���ڵ�ǰ����
			if (n > _capacity)
			{
				//���¿ռ䣬�Ѿɿռ�����ݿ�����ȥ
				char* tmp = new char[n+1];
				strcpy(tmp, _str);
				//�ͷžɿռ�
				delete _str;

				//���µ�ǰ����*this�ĳ�Ա
				_str = tmp;
				_capacity = n;
			}
		}
		void push_back(char x)
		{
			if (_capacity == _size)
			{
				//ע��_capacity��ʼֵΪ0�����
				reserve(_capacity == 0 ? 5 : _capacity * 2);
			}
			//������
			_str[_size] = x;
			++_size;
			//ע��'\0'
			_str[_size] = '\0';
		}

		string& operator+=(char x)
		{
			//����push_back
			push_back(x);
			return *this;
		}

		void append(const char* str)
		{
			size_t length = strlen(str);

			//��ʱ�����������ܴ��������ַ�
			if (_capacity < _size + length)
			{
				reserve(_size + length);
			}
			//_str+_size ��string���һ����Ч���ݵ���һ��λ��
			strcpy(_str + _size, str);
			_size += length;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		//��posλ�ò���һ���ַ�
		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);//=_size�൱��β��
			reserve(_size + 1);//�ж�����
			
			//�Ӻ���ǰŲ����
			//��ǰһ��λ�õ��ַ���ֵ����ǰλ�õ��ַ�
			size_t pre = _size - 1;
			size_t  cur= _size;//��ʼλ��Ϊ'\0'
			while(cur > pos)
			{
				//�� ǰһ��λ������ Ų�� ��ǰλ��
				_str[cur] = _str[pre];
				pre--;
				cur--;
			}
			//�޸�posλ�����ݣ���++_size
			_str[pos] = ch;
			++_size;

			//���һ���ַ�����һ��λ��Ϊ'\0'
			_str[_size] = '\0';
			
			return *this;
		}
		//��posλ�ò���һ���ַ���
		string& insert(size_t pos, const char* str)
		{
			//����λ���ж�
			assert(pos <= _size);

			//����ǿմ��������в���
			if (strlen(str) == 0)
				return *this;
			//�����ж�
			size_t length = strlen(str);
			reserve(length + _size);

			//ǰ������ָ�룬
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

		//��posλ�ÿ�ʼɾ��len���ַ�
		string& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);

			//ɾ����β�����
			if (len == npos || pos + len - 1  >= _size )
			{
				_size = pos;
				_str[_size] = '\0';
			}
			//ɾ��ĳ������������ַ�
			else if(len > 0)
			{
				//��ʼɾ����λ��(��ӦҪŲ����λ��pos ~_size - 1 - len)
				size_t pre = pos;
				//��ʼ��ǰŲ��λ��(Ҫ��ǰŲ��������pos+len ~ _size - 1)
				size_t cur = pre + len;

				while (cur <= _size - 1)
				{
					_str[pre] = _str[cur];
					++pre;
					++cur;
				}

				//Ų������_size
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
			//����c���Կ��strstr
			//const char* strstr(const char* str1, const char* str2);
			//char* strstr(char* str1, const char* str2);
			//���str2��str1���Ӵ�������str1��Ӧָ��λ�ã����򷵻�NULL

			const char* tmp = strstr(_str + pos, sub);
			if (tmp == nullptr)
			{
				return npos;
			}
			else
			{
				return (tmp - _str);//ָ��-ָ����ʼ�������±�λ�ã���Ϊ��������������ռ�
			}
		}
		void resize(size_t n, char ch = '\0')
		{		
			if (n == _size)//������
				return;
			else if (n < _size)//ɾ������
			{
				_size = n;
				_str[_size] = '\0';
			}
			else//���ݣ�ͬʱ��ʼ������Ŀռ�
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
		char* _str;//ָ��̬���ٵĿռ�
		size_t _size;//��ǰ��Ч�ַ��ĸ���
		size_t _capacity;//��ǰ�洢��Ч�ַ��Ŀռ��С��������'\0'
	};

	//1 ����ʵ��Ϊ��Ա���������ʵ��Ϊ��Ա����,thisָ����ռ�������
	//2 ��һ��Ҫʵ��Ϊstring����Ԫ��������Ϊ����Ҫ����string��˽�г�Ա
	ostream& operator<<(ostream& out, const string& str)
	{
		for (int i = 0; i < str.size(); i++)
		{
			out << str[i];
		}
		//֧������������
		return out;
	}

	/*istream& operator>>(istream& in, string& str)
	{
		char ch;
		//in >> ch;
		//cin�ǻ���Ե�����Ŀո���߻��У�����ѿո�ͻ��н���ch
		str = "";
		ch = in.get();//����һ��get()��Ա��������������ַ���ȡ
		while (ch != ' ' && ch != '\n')
		{
		 //����������룬����Ƶ����Ч�ʲ���
			str += ch;
			ch = in.get();
		}
		//�ڽ������������ʱ��cinĬ����' '��'\n' ��Ϊ���ݵķָ������cin����ȥ��������
		return in;
	}*/
	//�������Ƶ�����⣬���ڲ�����һ��buff����,һ��һ��ȥ��
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
				//�����������������һ���Ը�str��������Ч�������ݵ�����
				str += buff;
				i = 0;
			}
			ch = in.get();
		}
	
		buff[i] = '\0';
		str += buff;
		return in;
	}
	

	//�ú����������ռ�yh��
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
		s3.insert(0, "");//����մ�
		cout << s3.c_str();
	}
	
	void test29()
	{
		string s1("abcdefgh");
		s1.erase(0, 2);//ͷɾ "cdefgh"
		cout << s1.c_str() << endl;

		s1.erase(1, 2);//�м�ɾ"cfgh"
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
