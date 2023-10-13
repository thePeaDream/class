#include "AVLTree.hpp"


//ɾ�����31�󣬶�cur����˫��ʱ���ᵼ��cur�����߶�-1�����ü�������
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
	//����10000�����ֵ
	for (int i = 0; i < n; ++i)
	{
		int x = rand() % n;
		tree.insert(make_pair(x, i));
		//ÿ�β�����ɺ���Ȼ��AVL��
		if (tree.isAVLTree())
			cout << "����ɹ�"<< i << endl;
		else
		{
			cout << "���뷢���쳣" << endl;
			exit(-1);
		}
	}

	for (int i = 0; i < n; ++i)
	{
		//��̺ʽɾ��
		tree.erase(i);
		if (tree.isAVLTree())
			cout << "ɾ���ɹ�"<< i << endl;
		else
		{
			cout << "ɾ�������쳣" << endl;
			exit(-1);
		}
	}
}

int main()
{
	
	testAVLTree1();
	return 0;
}