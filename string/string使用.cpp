#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
typedef int TY;
using namespace std;
void test1()
{
	//1 默认构造string()
	string s1;
	
	//2 用字符串初始化string(const char *s)
	string s2 = "abcd";//先用"abcd"构造临时对象，再拷贝构造s2 + 编译器优化 -》直接构造
	//string s2("abcd");

	//3 拷贝构造string(const string& str)
	string s3(s2);//同string s3 = s2

	//它们里面重载了cin和cout运算符，
	//可以直接用cout打印string类，用cin输入字符串
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cin >> s1;
	cout << s1 << endl;

}
void test2()
{
	//4 string (const string& str, size_t pos, size_t len = npos);部分拷贝构造
	
	//从string类"hello world"下标为2位置开始数3个字符，用该子串进行拷贝构造
	/*string tmp("hello world");
	string s1(tmp, 2, 3);
	cout << s1 << endl;

	//从string类"hello world"下标为3位置开始数999个字符，超过该字符串，最多到结尾
	string s2(tmp, 3, 999);
	cout << s2 << endl;
	*/
	string tmp("newYear");
	string s3(tmp, 3);
	cout << s3 << endl;
}
void test3()
{
	//5 string(const char* s, size_t n);
	//用s的前n个字符，来初始化字符串
	string s1("abcdef", 3);
	cout << s1 << endl; //输出abc
	
	//6 string(size_t n, char c);
	//用n个字符c,初始化字符串
	string s2(3, 'a');
	cout << s2 << endl; //输出aaa
}
void test4()
{
	string s1(5, 'x');//"xxxxx"
	cout << s1 << endl;
	string s2("abcd");

	//operator=(const string& str)
	s1 = s2;
	cout << s1 << endl; //"abcd"

	//operator=(const char* str)
	s1 = "hello";
	cout << s1 << endl;//"hello"

	//operator=(char x)
	s1 = 'a';
	cout << s1 << endl;//"a"
}
void test5()
{
	string s1("hello world");
	//可以读写对应位置的字符,会转换成调用operator[]
	cout << s1[0] << endl;
	cout << s1.operator[](0) << endl;
	s1[0] = 'a';
	cout << s1 << endl;

	const string s2("ttt");
	//s2[0] = 'x';会报错
}
void test6()
{
	string s1(6, 'a');//"aaaaaa"
	for (size_t i = 0; i < s1.size(); ++i)//size()会返回当前字符个数
	{
		cout << s1[i];
		++s1[i];
	}
	cout << endl;
	cout << s1 << endl; // 修改后"bbbbbb"

	//const string可以遍历，但不可以修改
	const string s2("abcd");
	for (size_t i = 0; i < s2.size(); ++i)
	{
		//s2[i]++;会报错
		cout << s2[i];
	}
}
void test7()
{
	string s1("abc");
	string::iterator it = s1.begin();//begin()会返回第一个位置的迭代器
	while (it != s1.end())
	{
		cout << *it << " ";   //输出a b c
		++it;
	}
}
void test8()
{
	string s1("abcd");
	//反向迭代器类型名字——reverse_iterator，
	//提供rbegin()和rend()用于反向遍历容器
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit;//不管正向还是反向，都是++
	}
}
void test9()
{
	const string s1("abcd");
	//const正向迭代器类型：const_iterator
	string::const_iterator const_it = s1.begin();
	while (const_it != s1.end())
	{
		cout << *const_it << " ";
		const_it++;
	}

	//const反向迭代器类型：const_reverse_iterator
	string::const_reverse_iterator const_rit = s1.rbegin();
	while (const_rit != s1.rend())
	{
		cout << *const_rit << " ";
		++const_rit;
	}
}
void test10()
{
	string s1("hello");
	//void push_back(char c) 尾插一个字符c
	s1.push_back('s');
	cout << s1 << endl;

	//string& append (const char* s); 尾插一个字符串
	s1.append("world");
	cout << s1 << endl;

	//string& append(const string& str)
	string tmp("aaa");
	s1.append(tmp);
	cout << s1 << endl;
}
void test11()
{
	string s1("abc");
	//+=一个字符
	s1 += 'd';
	cout << s1 << endl;
	
	//+=一个常量字符串
	s1 += "efg";
	cout << s1 << endl;

	//+=一个string对象
	string s2("hijk");
	s1 += s2;
	cout << s1 << endl;
}
void test12()
{
	string s3("abcd");
	cout << "当前存储的字符数："<< s3.size() << endl;
	cout << "当前容量：" << s3.capacity() << endl;
	s3.reserve(1007);//扩容到1000
	cout << "扩容后存储的字符数：" << s3.size() << endl;
	cout << "扩容后容量：" << s3.capacity() << endl;
}
void test13()
{
	string s1("abcd");
	s1.resize(99);

	string s2("aaaa");
	s2.resize(1);
	cout << s2 << endl;//"a"

	string s3("bbbb");
	s3.resize(7, 't');
	cout << s3 << endl;//"bbbbttt"
}
void test14()
{
	string s1("it is sunny");
	//在每个空格处插入@_
	for (size_t i = 0; i < s1.size(); )
	{
		if (s1[i] == ' ')
		{
			//string& insert (size_t pos, const char* s);在pos位置，插入s
			s1.insert(i, "@_");
			//注意当前空格的下标改成了i+2
			i += 3;//避开已经遍历的空格
		}
		else
			i++;
	}
	cout << s1 << endl;

	string s2("a cd");
	s2.insert(1, 2, 'c');
	cout << s2;
}
void test15()
{
	//string& erase(size_t pos = 0, size_t len = npos);
	//从pos位置开始删除len个数据，若len大于pos之后的字符数，删到结尾
	string s1("abcdefg");
	cout << s1.erase(2, 3) << endl;//"abfg"
	
    //iterator erase(iterator p);
	//删除迭代器某个位置的字符
	string s2("utf-8");
	s2.erase(s2.begin() + 1);//删除t
	cout << s2 << endl;

	//iterator erase(iterator first, iterator last);
	//删除某个迭代器区间的字符串[左闭右开)，不会删除last对应位置的字符
	string s3("utf-16");
	s3.erase(s3.begin() + 1, s3.end() - 1);//删除"tf-1"
	cout << s3 << endl;
}

void test16()
{
	string fileName("源.cpp");
	//假设现在要用c接口读取当前文件 FILE* fopen(const char* _FileName, const char* _Mode)
	//fopen(fileName, "r");此时string类型的fileName不能直接传过去，要用c_str返回c形式字符串
	//c形式的字符串：const char*类型，指向一个字符串常量 或者 就是字符数组
	FILE* fr = fopen(fileName.c_str(), "r");
	char ch = fgetc(fr);
	while (ch != EOF)
	{
		cout << ch;
		ch = fgetc(fr);
	}
}

void test17()
{
	string s1("abcd");
	//调用重载的<<运算符 ostream& operator<<(ostream& os,const string& str)
	cout << s1 << endl;

	//调用重载的<<运算符 ostream& operator<<(ostream& os, const char* s) 
	cout << s1.c_str() << endl;
}
void test18()
{
	string s1("abcd");
	s1 += '\0';
	s1 += "ttt";

	cout << "string类型的字符串打印："<<s1 <<"，s1.size()为" <<s1.size() << endl;
	cout << "c类型的字符串打印：" << s1.c_str() << endl;
}
void test19()
{
	string fileName("test.cpp");
	//找到文件后缀,并打印出来
	size_t ret = fileName.find('.');
	if (ret == -1)
		cout << "无后缀" << endl;
	else
	{
		string suff = fileName.substr(ret, string::npos);
		cout << suff << endl;
	}
}
void test20()
{
	string fileName("test.cpp.tar");
	size_t ret = fileName.rfind('.');
	if (ret == string::npos)
		cout << "无后缀" << endl;
	else
	{
		string suff = fileName.substr(ret);
		cout << suff << endl;
	}
}

void splitUrl(const string& url)
{
	 //"https://legacy.cplusplus.com/reference/string/string/?kw=string";
	
	 //1 先找 :// 或 : 分割出协议
	size_t pos1 = url.find(':');
	if (pos1 == string::npos)
	{
		cout << "url非法" << endl;
		exit(-1);
	}
	string agreement = url.substr(0, pos1 - 1);
	cout << "协议名：" << agreement << endl;

	//2 在://位置之后，找到第一个/，分割出主机ip
	size_t begin = pos1 + 3;
	size_t pos2 = url.find('/', begin);
	if (pos2 == string::npos)
	{
		cout << "url非法" << endl;
		exit(-1);
	}
	string ip = url.substr(begin, pos2 - begin);
	cout << "主机IP地址：" << ip << endl;

	//3 分割出资源具体地址
	 string specificAddress = url.substr(pos2 + 1);
	 cout << "资源具体地址：" << specificAddress << endl;

}
void test21()
{
	const string url = "https://legacy.cplusplus.com/reference/string/string/?kw=string";
	splitUrl(url);
}
void test22()
{
	string s1;
	//istream& getline(istream & is, string & str)，默认以换行符终止输入
	getline(cin, s1);
	cout <<"输入后："<< s1 << endl << endl;

	string s2;
	//istream& getline(istream & is, string & str, char delim);自定义delim符号终止输入
	getline(cin, s2,'@');
	cout <<"输入后：" << s2 << endl;
}
void test23()
{
	int a = 0;
	double b = 3.3;
	
	//string to_string(int a) 
	string aStr = to_string(a);

	//string to_string(double a)
	string bStr = to_string(b);
	
	cout << "转换成功：" << aStr << " " << bStr << endl;

	string s1 = "123";
	string s2 = "13.2";
	int tmp1 = stoi(s1);
	double tmp2 = stod(s2);
	cout << "转换成功：" << tmp1 << "  " << tmp2 << endl;

	string s3 = "345699  tt";
	size_t idx = 0;
	int tmp3 = stoi(s3, &idx , 10);
	cout << tmp3 <<" 转换的数字长度为：" << idx;
}
int main()
{
	test23();
	return 0;
}