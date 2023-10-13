#include "AVLTree.hpp"


//删除结点31后，对cur左右双旋时，会导致cur子树高度-1，还得继续调整
int arr[] = { 40, 12, 45, 6, 30, 42, 47, 5, 9,31 ,41, 43, 46, 49, 7 };
void testAVLTree2()
{
	AVLTree<int, int> tree;
	for(int i = 0; i < sizeof(arr)/sizeof(int);++i)
		tree.insert(make_pair(arr[i], i));
	tree.erase(31);
	cout << tree.isAVLTree();

}

void testAVLTree1()
{
	srand(time(nullptr));
	AVLTree<int, int> tree;
	int n = 1000;
	//插入10000个随机值
	for (int i = 0; i < n; ++i)
	{
		int x = rand() % n;
		tree.insert(make_pair(x, i));
		//每次插入完成后仍然是AVL树
		if (tree.isAVLTree())
			cout << "插入成功"<< i << endl;
		else
		{
			cout << "插入发生异常" << endl;
			exit(-1);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		//地毯式删除
		tree.erase(i);
		if (tree.isAVLTree())
			cout << "删除成功"<< i << endl;
		else
		{
			cout << "删除发生异常" << endl;
			exit(-1);
		}
	}
}

int main()
{
	
	testAVLTree1();
	return 0;
}