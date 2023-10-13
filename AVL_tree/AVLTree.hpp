#pragma once
#include <utility>
#include <assert.h>
#include <stack>
#include <queue>
#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;
//AVL���Ľ������
//��ǰ����ƽ������ = ��ǰ�����������߶� - �������߶�   //������¼��ǰ�������������߶Ȳ�
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
//AVLTree������
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
private:
	Node* _root = nullptr;
public:
	void inOrder();
	bool insert(const std::pair<K, V>& kv);
	bool erase(const K& key);
	size_t height();
	bool isAVLTree();

private: //����ɾ�����
	//�������ת��ʽʵ��
	Node* _leftRotate(Node* cur);
	Node* _rightRotate(Node* cur);
	Node* _rightLeftRotate(Node* cur);
	Node* _leftRightRotate(Node* cur);

	//����Ĳ��룬�����²���Ľ�㣬����ʧ�ܷ���nullptr����װ��AVL���Ĳ�����
	Node* _ordinaryInsert(const std::pair<K, V>& kv);
	//�����ɾ��������ɾ�����ĸ��׽��
	Node* _ordinaryErase(const K& key);

	//��������ת����cur����������ת�����ڲ���4����ת��� + ��Ӧ�����ƽ�����ӵ���
	void _insertRotateAdjustBF(Node* cur);
	Node* _eraseRotateAdjustBF(Node* cur);

	
	//��������ת��ɺ������¸�������������ת����ת��Ӧƽ�����ӵĵ���
	void _insertLeftRotateAdjustBF(Node* newRoot);
	void _insertRightRotateAdjustBF(Node* newRoot);
	void _insertRightLeftRotateAdjustBF(Node* newRoot);
	void _insertLeftRightRotateAdjustBF(Node* newRoot);

	//��������ת��ɺ������¸���ɾ���������ת����ת��Ӧƽ�����ӵĵ���
	void _eraseLeftRotateAdjustBF(Node* newRoot);
	void _eraseRightRotateAdjustBF(Node* newRoot);
	void _eraseRightLeftRotateAdjustBF(Node* newRoot);
	void _eraseLeftRightRotateAdjustBF(Node* newRoot);

private://�����ж��Ƿ���AVLTree
	//һ�������ĸ߶�
	size_t _height(Node* root);
	//�ж�AVLTree��һ�����������Ҹ߶Ȳ��Ƿ�Ϸ�
	bool isAVLTreeChild(Node* _root);	
};

template<class K, class V>
bool AVLTree<K, V>::insert(const std::pair<K, V>& kv)
{
	//ֱ�Ӳ��룬�õ��������ָ��
	Node* insertNode = _ordinaryInsert(kv);

	//����������Ǹ����������
	//�����������nullptr,����ʧ�ܣ������Ѿ�����ͬ��keyֵ
	if (insertNode == _root) return true;
	if (insertNode == nullptr) return false;


	//���Ÿ��²���������Ƚ���ƽ������
	Node* child = insertNode;
	Node* parent = child->_parent;//parent������Ҫ����bf�Ľ�㣬child�����ж�parent->_bf��θ���
	while (parent != nullptr)//parent == nullptr,˵�����Ƚ���ƽ�������Ѿ�ȫ���������
	{
		//�ȸ���ƽ������
		//child�����ж�parent->_bf��θ���
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
			//��parent�������������ת����+ƽ�����ӵ���
			_insertRotateAdjustBF(parent);
			break;
		}
		else
			assert(false);
	}
	return true;
}

//������룬�����²���Ľ��ָ��
template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K, V>::_ordinaryInsert(const std::pair<K, V>& kv)
{
	//Ҫ������½��
	Node* newNode = new Node(kv);
	
	//����ǰ�ǿ���
	if (_root == nullptr)
	{
		_root = newNode;
		return _root;
	}

	//�ҵ�����λ�� �� ����λ�õĸ��׽�㣬���벢����

	Node* cur = _root;//��¼�����λ��
	Node* parent = nullptr;//��¼����λ�õĸ��׽��
	
	while (cur != nullptr)
	{
		//�����ֵ > ��ǰ����ֵ����keyȥ�Ƚϣ� ���� ȥ�����Ҳ���λ��
		//�����ֵ < ��ǰ����ֵ    ���� ȥ�����Ҳ���λ��
		//�����ֵ = ��ǰ����ֵ   ���� ����ʧ��
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
		else
		{
			delete newNode;
			//�Ѿ�����ȵ�key������ʧ��
			return nullptr;
		}
	}

	//����������ֵ��parentС�����������
	//����������ұ�
	if (kv.first < (parent->_kv).first)
		parent->_left = newNode;
	else
		parent->_right = newNode;
	
	//newNode�ĸ��׽��һ��Ҫ����
	newNode->_parent = parent;
	
	return newNode;
}


template<class K, class V>
bool AVLTree<K, V>::erase(const K& key)
{
	//cur�Ǳ�ɾ�����ĸ��׽��
	Node* cur = _ordinaryErase(key);
	
	//child�Ǹ߶ȱ����͵�����
	Node* child = nullptr;

	if (cur == nullptr)
	{
		//��ɾ��ǰ���������ȱ���_root��key���ж��������������ֱ�ӷ���true
		//1 ��ɾ���Ľ����_root������Ҫ����
		//2 û���ҵ�ɾ���Ľ��
		return true;
	}

	//���ڿ���ʹ���滻��ɾ����������ɾ�����keyֵ����ȷ��
	int leftTreeHeight = _height(cur->_left);
	int rightTreeHeight = _height(cur->_right);
	cur->_bf = rightTreeHeight - leftTreeHeight;

	//ɾ����� ��Ӱ���������Ƚ���ƽ������
	while (cur != nullptr)
	{
		if (child != nullptr)
		{
			if (cur->_left == child)
				++cur->_bf;
			else
				--cur->_bf;
		}

		
		if (cur->_bf == 0)
		{
			child = cur;
			cur = cur->_parent;
		}
		else if (cur->_bf == 1 || cur->_bf == -1)
			break;
		else if (cur->_bf == 2 || cur->_bf == -2)
		{
			//���flagΪ�գ���ת�������߶Ȳ��䣬����Ҫ��������
			Node* flag = _eraseRotateAdjustBF(cur);
			if (flag == nullptr)
				break;
			//���������¸������Ƚ���������
			child = flag;
			cur = flag->_parent;
		}
		else
			assert(false);
	}
	return true;
}

//����ɾ�������ر�ɾ�����ĸ��׽��
template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K,V>::_ordinaryErase(const K& key)
{
	//��¼ɾ�����λ�� �� ɾ�����ĸ��׽��λ��
	Node* del = _root;
	Node* delParent = nullptr;

	while (del != nullptr)
	{
		if (key > del->_kv.first)
		{
			delParent = del;
			del = del->_right;
		}
		else if (key < del->_kv.first)
		{
			delParent = del;
			del = del->_left;
		}
		else//�ɹ��ҵ�Ҫɾ���Ľ��
		{
			//1 ɾ�����������Ϊ��
			//2 ɾ�����������Ϊ��
			//3 ɾ��������������ӣ��滻��ɾ�������ӵ����������滻ɾ��
			if (del->_left == nullptr)
			{
				if (delParent == nullptr)
					_root = del->_right;
				else if (delParent->_left == del)
					delParent->_left = del->_right;
				else if (delParent->_right == del)
					delParent->_right = del->_right;
				delete del;
				return delParent;
			}
			else if (del->_right == nullptr)
			{
				if (delParent == nullptr)
					_root = del->_left;
				else if (delParent->_left == del)
					delParent->_left = del->_left;
				else if (delParent->_right == del)
					delParent->_right = del->_left;
				delete del;
				return delParent;
			}
			else//��ɾ��������������ӣ��滻��ɾ��
			{
				//��������������滻ɾ��
				Node* max = del->_left;
				Node* maxParent = del;;
				while (max->_right)
				{
					maxParent = max;
					max = max->_right;
				}

				del->_kv = max->_kv;

				//ɾ��max
				if (maxParent->_left == max)
					maxParent->_left = max->_left;
				else
					maxParent->_right = max->_left;
				delete max;
				return maxParent;
			}
		}
	}
	return nullptr;
}

//��cur�������(cur->_bf == 2)������ת����
template<class K, class V>
void AVLTree<K, V>::_insertRotateAdjustBF(AVLTreeNode<K, V>* cur)
{
	//4����ת�����Ҫ��ͼ�����������
	
	//1 ����ǰcur���������ϸߣ��²���Ľ����cur���������������� ����ֱ������
	//2 ����ǰcur���������ϸߣ��²���Ľ����cur���������������� ����ֱ������
	//3 ����ǰcur���������ϸߣ��²���Ľ����cur���������������� �����ȶ�cur->right�����������ٶ�cur��������
	//4 ����ǰcur���������ϸߣ��²���Ľ����cur����������������  ���� �ȶ�cur->left�����������ٶ�cur��������
	if ( cur->_bf == 2 && cur->_right->_bf == 1)
	{
		Node* newRoot = _leftRotate(cur);
		_insertLeftRotateAdjustBF(newRoot);
	}
	else if ( cur->_bf == -2&& cur->_left->_bf == -1 )
	{
		Node* newRoot = _rightRotate(cur);
		_insertRightRotateAdjustBF(newRoot);
	}
	else if (cur->_bf == 2 && cur->_right->_bf == -1)
	{
		Node* newRoot = _rightLeftRotate(cur);
		_insertRightLeftRotateAdjustBF(newRoot);
	}
	else if (cur->_bf == -2 && cur->_left->_bf == 1)
	{
		Node* newRoot = _leftRightRotate(cur);
		_insertLeftRightRotateAdjustBF(newRoot);
	}
	else
		//�д��󷽱����
		assert(false);
}

template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K, V>::_eraseRotateAdjustBF(Node* cur)
{
	//����nullptr��˵����ת�� ��ǰ�����ĸ߶Ȳ��䣬����Ҫ�����������Ƚ��
	//������������¸�����
	if ( cur->_bf == 2 && cur->_right->_bf == 1)
	{
		Node* newRoot = _leftRotate(cur);
		_eraseLeftRotateAdjustBF(newRoot);
		return newRoot;
	}
	else if (cur->_bf == 2 && cur->_right->_bf == 0)
	{
		Node* newRoot = _leftRotate(cur);
		_eraseLeftRotateAdjustBF(newRoot);
		return nullptr;
	}
	else if (cur->_bf == -2 && cur->_left->_bf == -1)
	{
		Node* newRoot = _rightRotate(cur);
		_eraseRightRotateAdjustBF(newRoot);
		return newRoot;
	}
	else if (cur->_bf == -2 && cur->_left->_bf == 0)
	{
		Node* newRoot = _rightRotate(cur);
		_eraseRightRotateAdjustBF(newRoot);
		return nullptr;
	}
	else if (cur->_bf == 2 && cur->_right->_bf == -1)
	{
		Node* newRoot = _rightLeftRotate(cur);
		_eraseRightLeftRotateAdjustBF(newRoot);

		return newRoot;
	}
	else if (cur->_bf == -2 && cur->_left->_bf == 1)
	{
		Node* newRoot = _leftRightRotate(cur);
		_eraseLeftRightRotateAdjustBF(newRoot);
		return newRoot;
	}
	else
			assert(false);
}

//���ģ�������ת��ͼ����ǰ��¼Ҫ�޸ĵĽ��
template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::_leftRotate(AVLTreeNode<K, V>* cur)//������ת�������µĸ�
{
	Node* parent = cur->_parent;
	Node* right = cur->_right;
	Node* rightLeft = cur->_right->_left;

	//��ͼ�������µ�����ע��parent��rightLeftΪ�յ������
	if (parent != nullptr)
	{
		if (parent->_left == cur)
			parent->_left = right;
		else
			parent->_right = right;
	}
	right->_parent = parent;

	right->_left = cur;
	cur->_parent = right;

	cur->_right = rightLeft;
	if (rightLeft != nullptr)
		rightLeft->_parent = cur;

	//���cur == _root��Ҫ����_root
	if (cur == _root)
		_root = right;

	//������������µĸ�
	return right;
}

template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::_rightRotate(AVLTreeNode<K,V>* cur)//������ת�������µĸ�
{
	Node* parent = cur->_parent;
	Node* left = cur->_left;
	Node* leftRight = cur->_left->_right;

	//��ͼ�������µ�����ע��parent��leftRightΪ�յ������
	if (parent != nullptr)
	{
		if (parent->_left == cur)
			parent->_left = left;
		else
			parent->_right = left;
	}
	left->_parent = parent;

	left->_right = cur;
	cur->_parent = left;

	cur->_left = leftRight;
	if(leftRight != nullptr)
		leftRight->_parent = cur;

	//���cur == _root��Ҫ����_root
	if (cur == _root)
		_root = left;

	//������������µĸ�
	return left;
}

template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K,V>::_rightLeftRotate(AVLTreeNode<K,V>* cur)
{
	//�ȶ�cur������������
	//�ٶ�cur������������
	//�õ��������¸�
	_rightRotate(cur->_right);
	Node* newRoot = _leftRotate(cur);

	return newRoot;
}

template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::_leftRightRotate(AVLTreeNode<K, V>* cur)
{
	_leftRotate(cur->_left);
	Node* newRoot = _rightRotate(cur);
	return newRoot;
}

template<class K, class V>
void AVLTree<K,V>::_insertLeftRotateAdjustBF(Node* newRoot)
{
	newRoot->_bf = 0;
	newRoot->_left->_bf = 0;
}

template<class K, class V>
void AVLTree<K, V>::_insertRightRotateAdjustBF(Node* newRoot)
{
	newRoot->_bf = 0;
	newRoot->_right->_bf = 0;
}

template<class K, class V>
void AVLTree<K, V>::_insertRightLeftRotateAdjustBF(Node* newRoot)
{
	//��ת��ɺ������ж�ƽ�����ӵ��������rightLeft����Ϊ�������ĸ�
	int flag = newRoot->_bf;

	//����ƽ������
	//flag = 0:˵��rightLeft�����²���Ľ��
	//flag = 1:˵����c���������㷢���߶Ȳ�ı�
	//flag = -1,˵����b���������㷢���߶Ȳ�ı�
	if (flag == 0)
		newRoot->_bf = newRoot->_left->_bf = newRoot->_right->_bf = 0;
	else if (flag == 1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = -1;
		newRoot->_right->_bf = 0;
	}
	else if (flag == -1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 1;
	}
	else
		assert(false);
}

template<class K, class V>
void AVLTree<K, V>::_insertLeftRightRotateAdjustBF(Node* newRoot)
{
	//��ת��ɺ������ж�ƽ�����ӵ��������leftRight����Ϊ�������ĸ�
	int flag = newRoot->_bf;

	//flag = 0:leftRight�����²���Ľ��
	//flag = 1:˵����c����������
	//flag = -1:˵����b����������
	if (flag == 0)
		newRoot->_bf = newRoot->_left->_bf = newRoot->_right->_bf = 0;
	else if (flag == 1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = -1;
		newRoot->_right->_bf = 0;
	}
	else if (flag == -1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 1;
	}
	else
		assert(false);
}

template<class K, class V>
void AVLTree<K,V>::_eraseLeftRotateAdjustBF(Node* newRoot)
{
	if (newRoot->_bf == 1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = 0;
	}
	else if (newRoot->_bf == 0)
	{
		newRoot->_bf = -1;
		newRoot->_left->_bf = 1;
	}
	else
		assert(false);
}

template<class K ,class V>
void AVLTree<K,V>::_eraseRightRotateAdjustBF(Node* newRoot)
{
	if (newRoot->_bf == -1)
	{
		newRoot->_bf = 0;
		newRoot->_right->_bf = 0;
	}
	else if (newRoot->_bf == 0)
	{
		newRoot->_bf = 1;
		newRoot->_right->_bf = -1;
	}
	else
		assert(false);
}

template<class K, class V>
void AVLTree<K, V>::_eraseRightLeftRotateAdjustBF(Node* newRoot)
{
	if (newRoot->_bf == 0)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 0;
	}
	else if(newRoot->_bf == 1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = -1;
		newRoot->_right->_bf = 0;
	}
	else if(newRoot->_bf == -1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 1;
	}
}

template<class K,class V>
void AVLTree<K, V>::_eraseLeftRightRotateAdjustBF(Node* newRoot)
{
	if (newRoot->_bf == 0)
		newRoot->_bf = newRoot->_left->_bf = newRoot->_right->_bf = 0;
	else if (newRoot->_bf == 1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = -1;
		newRoot->_right->_bf = 0;
	}
	else if (newRoot->_bf == -1)
	{
		newRoot->_bf = 0;
		newRoot->_left->_bf = 0;
		newRoot->_right->_bf = 1;
	}
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
size_t AVLTree<K, V>::height()
{
	return _height(_root);
}

template<class K, class V>
size_t AVLTree<K, V>::_height(Node* root)
{
	if (root == nullptr) return 0;
	//�ö��в��������ÿһ������� ++ret
	int ret = 0;

	//��ǰ�㻹��Ҫ�����Ľ����Ŀ
	int curLevelLeftNum = 1;

	//��¼�������Ľ��
	Node* cur = nullptr;

	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		cur = q.front();
		q.pop();

		//�������Ľ�㣬���ĺ��Ӳ�Ϊ�վ������
		if (cur->_left != nullptr)
			q.push(cur->_left);
		if (cur->_right != nullptr)
			q.push(cur->_right);

		//��ǰ��������Ľ����Ŀ-1
		curLevelLeftNum--;
		if (curLevelLeftNum == 0)//��ǰ��������
		{
			++ret;
			curLevelLeftNum = q.size();
		}
	}

	return ret;
}

template<class K, class V>
bool AVLTree<K, V>::isAVLTree()
{
	if (_root == nullptr) return true;
	//�������н�㣬ֻҪ���н�㶼���� �����������߶Ȳ����1 ����AVLTree

	//ǰ�����
	stack<Node*> st;
	Node* cur = _root;
	while (cur != nullptr || !st.empty())
	{
		while (cur)
		{
			st.push(cur);
			if (isAVLTreeChild(cur) == false)
				return false;
			cur = cur->_left;
		}
		Node* top = st.top();
		st.pop();
		cur = top->_right;
	}
	return true;
}

//�ж�AVLTree��һ�����������Ҹ߶Ȳ��Ƿ�Ϸ�
template<class K, class V>
bool AVLTree<K, V>::isAVLTreeChild(Node* root)
{
	if (root == nullptr) return true;

	int leftHeight = _height(root->_left);
	int rightHeight = _height(root->_right);
	int flag = rightHeight - leftHeight;
	assert(flag == root->_bf);
	if (flag == root->_bf && abs(flag) < 2)
		return true;
	else
		return false;
}