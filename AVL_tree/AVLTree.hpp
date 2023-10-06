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
	int _bf;//ƽ������balance factor
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
	//�ж�ÿ���������������Ҹ߶Ȳ��Ƿ�С��2
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
	
	size_t curLevelLeftNum = 1;//��ǰ��ʣ��Ľ����Ŀ
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
	//ֱ�Ӳ��룬�õ��������ָ��
	Node* insertNode = ordinaryInsert(kv);

	if (insertNode == _root) return true;
	if (insertNode == nullptr) return false;

	Node* child = insertNode;
	Node* parent = child->_parent;

	//���Ų�����ĸ��׽�㣬�������Ƚ���ƽ������
	while (parent != nullptr)
	{
		//�ȸ���ƽ������
		if (parent->_left == child)
			--parent->_bf;
		else
			++parent->_bf;

		//�����º�ƽ������Ϊ0��˵��parent���ڵ������߶Ȳ��䣬����Ҫ�������ϸ���
		//��parent->_bf��Ϊ1/-1��parent���������ĸ߶ȱ��ˣ�Ҫ�������ϸ���
		//parent->_bf == 2/-2,ƽ�ⱻ���ƣ�parent��������Ҫ��ת����
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
	
	//����
	if (_root == nullptr)
	{
		_root = newNode;
		return _root;
	}

	//�ҵ�����λ�� �� ����λ�õĸ��׽�㣬���벢����
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
		else//�Ѿ�����ȵ�key������ʧ��
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
	
	//����pParent�ĺ��ӣ�ԭ��ָ��parent��λ�ã�����ָ��pR
	if (pParent != nullptr)
	{
		if (pParent->_left == parent)
			pParent->_left = pR;
		else
			pParent->_right = pR;
	}

	//����pR
	pR->_left = parent;
	pR->_parent = pParent;

	//����parent
	parent->_parent = pR;
	parent->_right = pRL;
	
	//����pRL�ĸ���
	if(pRL)
		pRL->_parent = parent;

	//���parentԭ�����������ĸ����޸ĸ�
	if (parent == _root)
		_root = pR;

	//�޸�ƽ������
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

	//����pParent
	if (pParent != nullptr)
	{
		if (pParent->_left == parent)
			pParent->_left = pL;
		else
			pParent->_right = pL;
	}

	//����pL
	pL->_parent = pParent;
	pL->_right = parent;

	//����parent
	parent->_parent = pL;
	parent->_left = pLR;

	//����pLR
	if (pLR != nullptr)
		pLR->_parent = parent;

	if (parent == _root)
		_root = pL;

	//�޸�ƽ������
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
		//˵��PRL���²���Ľ��
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
		//˵��PLR���²���Ľ��
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 0;
	}
	else
		assert(false);
}
