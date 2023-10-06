#include "BSTree.hpp"
#include "KVBSTree.hpp"

using namespace lyh;

void testMyBSTreeInsertErase()
{
	BinarySearchTree<int> bsTree;
	
	//插入删除
	bsTree.insert(2);
	bsTree.insert(1);
	bsTree.insert(3);
	bsTree.insert(6);
	bsTree.insert(5);
	bsTree.insert(4);
	bsTree.InOrder();
	for (int i = 0; i < 6; ++i)
	{
		bsTree.erase(i+1);
		bsTree.InOrder();
	}

	//递归版本
	BinarySearchTree<int> bsTreeR;
	//插入删除
	bsTreeR.insertR(2);
	bsTreeR.insertR(1);
	bsTreeR.insertR(3);
	bsTreeR.insertR(6);
	bsTreeR.insertR(5);
	bsTreeR.insertR(4);
	bsTreeR.InOrder();
	for (int i = 0; i < 6; ++i)
	{
		bsTreeR.eraseR(i + 1);
		bsTreeR.InOrder();
	}
}

void testKV()
{
	string str = "aazzccddd";
	yh::BinarySearchTree<char, int> countChar;
	for (auto& x : str)
	{
		yh::BinarySearchTreeNode<char, int>* exist = countChar.find(x);
		//如果该字符存在,
		if (exist != nullptr)
			++exist->_val;
		else//否则插入字符，同时value设为1
			countChar.insert(x, 1);
	}

	countChar.InOrder();
}

int main()
{
	//testMyBSTreeInsertErase();
	testKV();
	return 0;
}