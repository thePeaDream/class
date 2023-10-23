#include "2-3-4树.hpp"
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
			cout << "插入时发生错误" << endl;
			break;
		}
	}
	cout << "元素全部插入成功"<<endl;
	
	for (int i = 0; i < n; ++i)
	{
		if (bLTree.isBalanceTree() == false)
		{
			cout << "删除时发生错误" << endl;
			break;
		}
	}
	cout << "元素全部删除成功" << endl;
}

int main()
{
	srand(time(nullptr));
	testBalanceTree();
	return 0;
}