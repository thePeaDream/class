#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
typedef int TY;
using namespace std;
void test1()
{
	//1 Ĭ�Ϲ���string()
	string s1;
	
	//2 ���ַ�����ʼ��string(const char *s)
	string s2 = "abcd";//����"abcd"������ʱ�����ٿ�������s2 + �������Ż� -��ֱ�ӹ���
	//string s2("abcd");

	//3 ��������string(const string& str)
	string s3(s2);//ͬstring s3 = s2

	//��������������cin��cout�������
	//����ֱ����cout��ӡstring�࣬��cin�����ַ���
	cout << s1 << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cin >> s1;
	cout << s1 << endl;

}
void test2()
{
	//4 string (const string& str, size_t pos, size_t len = npos);���ֿ�������
	
	//��string��"hello world"�±�Ϊ2λ�ÿ�ʼ��3���ַ����ø��Ӵ����п�������
	/*string tmp("hello world");
	string s1(tmp, 2, 3);
	cout << s1 << endl;

	//��string��"hello world"�±�Ϊ3λ�ÿ�ʼ��999���ַ����������ַ�������ൽ��β
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
	//��s��ǰn���ַ�������ʼ���ַ���
	string s1("abcdef", 3);
	cout << s1 << endl; //���abc
	
	//6 string(size_t n, char c);
	//��n���ַ�c,��ʼ���ַ���
	string s2(3, 'a');
	cout << s2 << endl; //���aaa
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
	//���Զ�д��Ӧλ�õ��ַ�,��ת���ɵ���operator[]
	cout << s1[0] << endl;
	cout << s1.operator[](0) << endl;
	s1[0] = 'a';
	cout << s1 << endl;

	const string s2("ttt");
	//s2[0] = 'x';�ᱨ��
}
void test6()
{
	string s1(6, 'a');//"aaaaaa"
	for (size_t i = 0; i < s1.size(); ++i)//size()�᷵�ص�ǰ�ַ�����
	{
		cout << s1[i];
		++s1[i];
	}
	cout << endl;
	cout << s1 << endl; // �޸ĺ�"bbbbbb"

	//const string���Ա��������������޸�
	const string s2("abcd");
	for (size_t i = 0; i < s2.size(); ++i)
	{
		//s2[i]++;�ᱨ��
		cout << s2[i];
	}
}
void test7()
{
	string s1("abc");
	string::iterator it = s1.begin();//begin()�᷵�ص�һ��λ�õĵ�����
	while (it != s1.end())
	{
		cout << *it << " ";   //���a b c
		++it;
	}
}
void test8()
{
	string s1("abcd");
	//����������������֡���reverse_iterator��
	//�ṩrbegin()��rend()���ڷ����������
	string::reverse_iterator rit = s1.rbegin();
	while (rit != s1.rend())
	{
		cout << *rit << " ";
		++rit;//���������Ƿ��򣬶���++
	}
}
void test9()
{
	const string s1("abcd");
	//const������������ͣ�const_iterator
	string::const_iterator const_it = s1.begin();
	while (const_it != s1.end())
	{
		cout << *const_it << " ";
		const_it++;
	}

	//const������������ͣ�const_reverse_iterator
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
	//void push_back(char c) β��һ���ַ�c
	s1.push_back('s');
	cout << s1 << endl;

	//string& append (const char* s); β��һ���ַ���
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
	//+=һ���ַ�
	s1 += 'd';
	cout << s1 << endl;
	
	//+=һ�������ַ���
	s1 += "efg";
	cout << s1 << endl;

	//+=һ��string����
	string s2("hijk");
	s1 += s2;
	cout << s1 << endl;
}
void test12()
{
	string s3("abcd");
	cout << "��ǰ�洢���ַ�����"<< s3.size() << endl;
	cout << "��ǰ������" << s3.capacity() << endl;
	s3.reserve(1007);//���ݵ�1000
	cout << "���ݺ�洢���ַ�����" << s3.size() << endl;
	cout << "���ݺ�������" << s3.capacity() << endl;
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
	//��ÿ���ո񴦲���@_
	for (size_t i = 0; i < s1.size(); )
	{
		if (s1[i] == ' ')
		{
			//string& insert (size_t pos, const char* s);��posλ�ã�����s
			s1.insert(i, "@_");
			//ע�⵱ǰ�ո���±�ĳ���i+2
			i += 3;//�ܿ��Ѿ������Ŀո�
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
	//��posλ�ÿ�ʼɾ��len�����ݣ���len����pos֮����ַ�����ɾ����β
	string s1("abcdefg");
	cout << s1.erase(2, 3) << endl;//"abfg"
	
    //iterator erase(iterator p);
	//ɾ��������ĳ��λ�õ��ַ�
	string s2("utf-8");
	s2.erase(s2.begin() + 1);//ɾ��t
	cout << s2 << endl;

	//iterator erase(iterator first, iterator last);
	//ɾ��ĳ��������������ַ���[����ҿ�)������ɾ��last��Ӧλ�õ��ַ�
	string s3("utf-16");
	s3.erase(s3.begin() + 1, s3.end() - 1);//ɾ��"tf-1"
	cout << s3 << endl;
}

void test16()
{
	string fileName("Դ.cpp");
	//��������Ҫ��c�ӿڶ�ȡ��ǰ�ļ� FILE* fopen(const char* _FileName, const char* _Mode)
	//fopen(fileName, "r");��ʱstring���͵�fileName����ֱ�Ӵ���ȥ��Ҫ��c_str����c��ʽ�ַ���
	//c��ʽ���ַ�����const char*���ͣ�ָ��һ���ַ������� ���� �����ַ�����
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
	//�������ص�<<����� ostream& operator<<(ostream& os,const string& str)
	cout << s1 << endl;

	//�������ص�<<����� ostream& operator<<(ostream& os, const char* s) 
	cout << s1.c_str() << endl;
}
void test18()
{
	string s1("abcd");
	s1 += '\0';
	s1 += "ttt";

	cout << "string���͵��ַ�����ӡ��"<<s1 <<"��s1.size()Ϊ" <<s1.size() << endl;
	cout << "c���͵��ַ�����ӡ��" << s1.c_str() << endl;
}
void test19()
{
	string fileName("test.cpp");
	//�ҵ��ļ���׺,����ӡ����
	size_t ret = fileName.find('.');
	if (ret == -1)
		cout << "�޺�׺" << endl;
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
		cout << "�޺�׺" << endl;
	else
	{
		string suff = fileName.substr(ret);
		cout << suff << endl;
	}
}

void splitUrl(const string& url)
{
	 //"https://legacy.cplusplus.com/reference/string/string/?kw=string";
	
	 //1 ���� :// �� : �ָ��Э��
	size_t pos1 = url.find(':');
	if (pos1 == string::npos)
	{
		cout << "url�Ƿ�" << endl;
		exit(-1);
	}
	string agreement = url.substr(0, pos1 - 1);
	cout << "Э������" << agreement << endl;

	//2 ��://λ��֮���ҵ���һ��/���ָ������ip
	size_t begin = pos1 + 3;
	size_t pos2 = url.find('/', begin);
	if (pos2 == string::npos)
	{
		cout << "url�Ƿ�" << endl;
		exit(-1);
	}
	string ip = url.substr(begin, pos2 - begin);
	cout << "����IP��ַ��" << ip << endl;

	//3 �ָ����Դ�����ַ
	 string specificAddress = url.substr(pos2 + 1);
	 cout << "��Դ�����ַ��" << specificAddress << endl;

}
void test21()
{
	const string url = "https://legacy.cplusplus.com/reference/string/string/?kw=string";
	splitUrl(url);
}
void test22()
{
	string s1;
	//istream& getline(istream & is, string & str)��Ĭ���Ի��з���ֹ����
	getline(cin, s1);
	cout <<"�����"<< s1 << endl << endl;

	string s2;
	//istream& getline(istream & is, string & str, char delim);�Զ���delim������ֹ����
	getline(cin, s2,'@');
	cout <<"�����" << s2 << endl;
}
void test23()
{
	int a = 0;
	double b = 3.3;
	
	//string to_string(int a) 
	string aStr = to_string(a);

	//string to_string(double a)
	string bStr = to_string(b);
	
	cout << "ת���ɹ���" << aStr << " " << bStr << endl;

	string s1 = "123";
	string s2 = "13.2";
	int tmp1 = stoi(s1);
	double tmp2 = stod(s2);
	cout << "ת���ɹ���" << tmp1 << "  " << tmp2 << endl;

	string s3 = "345699  tt";
	size_t idx = 0;
	int tmp3 = stoi(s3, &idx , 10);
	cout << tmp3 <<" ת�������ֳ���Ϊ��" << idx;
}
int main()
{
	test23();
	return 0;
}