#include "string.h"
using std::exception;
void testn()
{
	int i = 0;
	double d = 1.0;
	cin.operator>>(i);  // cin >> i;  
	cin.operator>>(d); //cin >> d;
	
	cout.operator<<(i)<<endl; //cout << i << endl;
	cout.operator<<(d);           //cout << d;
}

int main()
{
	//testn();
	//yh::test31();
	std::string s1("abcd");
	s1.resize(50, 'x');
	cout << "resize(50, 'x')��s1�����ݸ�����" << s1.size() << endl;
	cout << s1 << endl<<endl;

	s1.resize(5);
	cout << "resize(5)��s1�����ݸ�����"<<s1.size() << endl;
	cout << s1 << endl << endl;

	s1.resize(4, 'u');
	cout << "resize(4,'u')��s1�����ݸ�����" << s1.size() << endl;
	cout << s1 << endl << endl;

	s1.resize(4);
	cout << "resize(4)��s1�����ݸ�����" << s1.size() << endl;
	cout << s1 << endl;
	return 0;
}
