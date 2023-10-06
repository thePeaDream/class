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
			cout << "avl树构建失败" << endl;
			break;
		}
		else
			cout << "插入成功，仍然为AVL树"<< i << endl;
	}
}

int main()
{
	srand(time(nullptr));
	testAVLTree();
	return 0;
}