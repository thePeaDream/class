#include "AVLTree.hpp"

void testAVLTree()
{
	AVLTree<int, int> avlTree;
	int n = 100000;
	for (size_t i = 0; i < n; ++i)
	{
		avlTree.insert(make_pair(rand(), i));
		
		bool flag = avlTree.isAVLTree();
		if (flag == false)
		{
			cout << "avl������ʧ��" << endl;
			break;
		}
		else
			cout << "����ɹ�����ȻΪAVL��"<< i << endl;
	}
}

int main()
{
	srand(time(nullptr));
	testAVLTree();
	return 0;
}