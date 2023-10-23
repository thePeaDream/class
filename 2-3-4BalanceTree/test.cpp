#include "2-3-4��.hpp"
void testBalanceTree()
{
	BalanceTree<int, int> bLTree;
	int n = 3000;

	for (int i = 0; i < n; ++i)
	{
		int x = rand() % n;
		//cout << x << " ";
		
		bLTree.insert(make_pair(x, i));
		
		if (bLTree.isBalanceTree() == false)
		{
			cout << "����ʱ��������" << endl;
			break;
		}
	}
	cout << "Ԫ��ȫ������ɹ�"<<endl;
	
	for (int i = 0; i < n; ++i)
	{
		if (bLTree.isBalanceTree() == false)
		{
			cout << "ɾ��ʱ��������" << endl;
			break;
		}
	}
	cout << "Ԫ��ȫ��ɾ���ɹ�" << endl;
}

int main()
{
	srand(time(nullptr));
	testBalanceTree();
	return 0;
}