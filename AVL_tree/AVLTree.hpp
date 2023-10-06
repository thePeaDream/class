#pragma once
#include <utility>
#include <assert.h>
#include <stack>
#include <queue>
#include <iostream>
#include <time.h>
using namespace std;
template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode(const pair<K, V>& kv = std::pair<K,V>())
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_bf(0)
	{}

	AVLTreeNode* _left;
	AVLTreeNode* _right;
	AVLTreeNode* _parent;
	std::pair<K, V> _kv;
	int _bf;//平衡因子balance factor
};

template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
private:
	Node* _root = nullptr;

public:
	void inOrder();
	bool insert(const std::pair<K, V>& kv);
	bool isAVLTree();

private:
	Node* ordinaryInsert(const std::pair<K, V>& kv);
	
	void rotate(Node* parent);
	Node* leftRotate(Node* parent);
	Node* rightRotate(Node* parent);
	void rightLeftRotate(Node* parent);
	void leftRightRotate(Node* parent);
	
	bool isAVLTreeChild(Node* root);
	size_t height(Node* root);
};

/*
template<class K, class V>
bool AVLTree<K, V>::isAVLTree()
{
	return isAVLTreeChild(_root);
}
template<class K, class V>
bool AVLTree<K, V>::isAVLTreeChild(AVLTreeNode<K, V>* root)
{
	if (root == nullptr) return true;
	size_t leftTreeHeight = height(root->_left);
	size_t rightTreeHeight = height(root->_right);

	size_t diff = rightTreeHeight - leftTreeHeight;
	if (diff != root->_bf) assert(false);
	if (abs((int)diff) >= 2)
		return false;
	return isAVLTreeChild(root->_left)&& isAVLTreeChild(root->_right);
}*/

template<class K, class V>
bool AVLTree<K, V>::isAVLTree()
{
	if (_root == nullptr) return true;
	//判断每棵子树，它的左右高度差是否小于2
	stack<Node*> st;
	Node* cur = _root;
	while (!st.empty() || cur != nullptr)
	{
		while (cur)
		{
			if (isAVLTreeChild(cur) == false)
				return false;
			st.push(cur);
			cur = cur->_left;		
		}

		Node* top = st.top();
		st.pop();
		cur = top->_right;
	}
	return true;
}

template<class K, class V>
bool AVLTree<K, V>::isAVLTreeChild(AVLTreeNode<K,V>* root)
{
	int leftHeight = height(root->_left);
	int rightHeight = height(root->_right);
	if (rightHeight - leftHeight != root->_bf)
		assert(false);
	return abs(leftHeight - rightHeight) < 2;
}


/*
template<class K, class V>
size_t AVLTree<K, V>::height(AVLTreeNode<K, V>* root)
{
	if (root == nullptr) return 0;
	int left = height(root->_left);
	int right = height(root->_right);
	return (right > left ? right + 1 : left + 1);
}*/

template<class K, class V>
size_t AVLTree<K, V>::height(AVLTreeNode<K, V>* root)
{
	if (root == nullptr) return 0;
	queue<Node*> level;
	level.push(root);
	
	size_t curLevelLeftNum = 1;//当前层剩余的结点数目
	size_t h = 0;
	while (!level.empty())
	{
		Node* cur = level.front();
		
		level.pop();
		if(cur->_left)
			level.push(cur->_left);
		if(cur->_right)
			level.push(cur->_right);
		

		curLevelLeftNum--;
		if (curLevelLeftNum == 0)
		{
			h++;
			curLevelLeftNum = level.size();
		}
	}
	return h;
}




template<class K, class V>
void AVLTree<K, V>::inOrder()
{
	stack<Node*> st;
	Node* cur = _root;
	while (cur || !st.empty())
	{
		while (cur)
		{
			st.push(cur);
			cur = cur->_left;
		}
		Node* top = st.top();
		cout << top->_kv.first << "->" << top->_kv.second << endl;
		st.pop();
		cur = top->_right;
	}
}

template<class K, class V>
bool AVLTree<K, V>::insert(const std::pair<K, V>& kv)
{
	//直接插入，得到插入结点的指针
	Node* insertNode = ordinaryInsert(kv);

	if (insertNode == _root) return true;
	if (insertNode == nullptr) return false;

	Node* child = insertNode;
	Node* parent = child->_parent;

	//沿着插入结点的父亲结点，更新祖先结点的平衡因子
	while (parent != nullptr)
	{
		//先更新平衡因子
		if (parent->_left == child)
			--parent->_bf;
		else
			++parent->_bf;

		//若更新后，平衡因子为0，说明parent所在的子树高度不变，不需要继续向上更新
		//若parent->_bf变为1/-1，parent所在子树的高度变了，要继续向上更新
		//parent->_bf == 2/-2,平衡被打破，parent所在子树要旋转处理
		if (parent->_bf == 0)
			break;
		else if (parent->_bf == 1 || parent->_bf == -1)
		{
			child = parent;
			parent = parent->_parent;
		}
		else if (parent->_bf == 2 || parent->_bf == -2)
		{
			rotate(parent);
			break;
		}
		else
			assert(false);
	}
	return true;
}


template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K, V>::ordinaryInsert(const std::pair<K, V>& kv)
{
	Node* newNode = new Node(kv);
	
	//空树
	if (_root == nullptr)
	{
		_root = newNode;
		return _root;
	}

	//找到插入位置 和 插入位置的父亲结点，插入并链接
	Node* cur = _root;
	Node* parent = nullptr;
	while (cur != nullptr)
	{
		if (kv.first > (cur->_kv).first)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (kv.first < (cur->_kv).first)
		{
			parent = cur;
			cur = cur->_left;
		}
		else//已经有相等的key，插入失败
			return nullptr;
	}
	if (kv.first < (parent->_kv).first)
		parent->_left = newNode;
	else
		parent->_right = newNode;
	newNode->_parent = parent;
	
	return newNode;
}

template<class K, class V>
void AVLTree<K, V>::rotate(AVLTreeNode<K, V>* parent)
{
	if (parent->_bf == 2 && parent->_right->_bf == 1)
		leftRotate(parent);
	else if (parent->_bf == -2 && parent->_left->_bf == -1)
		rightRotate(parent);
	else if (parent->_bf == 2 && parent->_right->_bf == -1)
		rightLeftRotate(parent);
	else if (parent->_bf == -2 && parent->_left->_bf == 1)
		leftRightRotate(parent);
	else
		assert(false);
}

template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::leftRotate(AVLTreeNode<K, V>* parent)
{
	Node* pRL = parent->_right->_left;
	Node* pR = parent->_right;
	Node* pParent = parent->_parent;
	
	//更新pParent的孩子，原来指向parent的位置，现在指向pR
	if (pParent != nullptr)
	{
		if (pParent->_left == parent)
			pParent->_left = pR;
		else
			pParent->_right = pR;
	}

	//更新pR
	pR->_left = parent;
	pR->_parent = pParent;

	//更新parent
	parent->_parent = pR;
	parent->_right = pRL;
	
	//更新pRL的父亲
	if(pRL)
		pRL->_parent = parent;

	//如果parent原来是整棵树的根，修改根
	if (parent == _root)
		_root = pR;

	//修改平衡因子
	pR->_bf = 0;
	parent->_bf = 0;

	return pR;
}

template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::rightRotate(AVLTreeNode<K,V>* parent)
{
	Node* pL = parent->_left;
	Node* pLR = parent->_left->_right;
	Node* pParent = parent->_parent;

	//更新pParent
	if (pParent != nullptr)
	{
		if (pParent->_left == parent)
			pParent->_left = pL;
		else
			pParent->_right = pL;
	}

	//更新pL
	pL->_parent = pParent;
	pL->_right = parent;

	//更新parent
	parent->_parent = pL;
	parent->_left = pLR;

	//更新pLR
	if (pLR != nullptr)
		pLR->_parent = parent;

	if (parent == _root)
		_root = pL;

	//修改平衡因子
	pL->_bf = 0;
	parent->_bf = 0;

	return pL;
}


template<class K, class V>
void AVLTree<K,V>::rightLeftRotate(AVLTreeNode<K,V>* parent)
{
	int flag = parent->_right->_left->_bf;

	rightRotate(parent->_right);
	Node* newRoot = leftRotate(parent);
	newRoot->_bf = 0;

	if (flag == -1)
	{
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 1;
	}
	else if (flag == 1)
	{
		newRoot->_left->_bf = -1;
		newRoot->_right->_bf = 0;
	}
	else if (flag == 0)
	{
		//说明PRL是新插入的结点
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 0;
	}
	else
		assert(false);
}

template<class K, class V>
void AVLTree<K, V>::leftRightRotate(AVLTreeNode<K, V>* parent)
{
	int flag = parent->_left->_right->_bf;

	leftRotate(parent->_left);
	Node* newRoot = rightRotate(parent);
	newRoot->_bf = 0;
	if (flag == 1)
	{
		newRoot->_left->_bf = -1;
		newRoot->_right->_bf = 0;
	}
	else if (flag == -1)
	{
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 1;
	}
	else if (flag == 0)
	{
		//说明PLR是新插入的结点
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 0;
	}
	else
		assert(false);
}
