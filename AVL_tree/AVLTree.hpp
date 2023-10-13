#pragma once
#include <utility>
#include <assert.h>
#include <stack>
#include <queue>
#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;
//AVL树的结点声明
//当前结点的平衡因子 = 当前结点的右子树高度 - 左子树高度   //用来记录当前结点的左右子树高度差
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
//AVLTree的声明
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

private: //插入删除相关
	//具体的旋转方式实现
	Node* _leftRotate(Node* cur);
	Node* _rightRotate(Node* cur);
	Node* _rightLeftRotate(Node* cur);
	Node* _leftRightRotate(Node* cur);

	//常规的插入，返回新插入的结点，插入失败返回nullptr，封装在AVL树的插入里
	Node* _ordinaryInsert(const std::pair<K, V>& kv);
	//常规的删除，返回删除结点的父亲结点
	Node* _ordinaryErase(const K& key);

	//插入后的旋转：对cur子树进行旋转处理，内部有4种旋转情况 + 对应情况的平衡因子调整
	void _insertRotateAdjustBF(Node* cur);
	Node* _eraseRotateAdjustBF(Node* cur);

	
	//（传入旋转完成后树的新根）插入后完成旋转，旋转对应平衡因子的调整
	void _insertLeftRotateAdjustBF(Node* newRoot);
	void _insertRightRotateAdjustBF(Node* newRoot);
	void _insertRightLeftRotateAdjustBF(Node* newRoot);
	void _insertLeftRightRotateAdjustBF(Node* newRoot);

	//（传入旋转完成后树的新根）删除后完成旋转，旋转对应平衡因子的调整
	void _eraseLeftRotateAdjustBF(Node* newRoot);
	void _eraseRightRotateAdjustBF(Node* newRoot);
	void _eraseRightLeftRotateAdjustBF(Node* newRoot);
	void _eraseLeftRightRotateAdjustBF(Node* newRoot);

private://用于判断是否是AVLTree
	//一棵子树的高度
	size_t _height(Node* root);
	//判断AVLTree中一棵子树的左右高度差是否合法
	bool isAVLTreeChild(Node* _root);	
};

template<class K, class V>
bool AVLTree<K, V>::insert(const std::pair<K, V>& kv)
{
	//直接插入，得到插入结点的指针
	Node* insertNode = _ordinaryInsert(kv);

	//如果插入结点是根，插入完成
	//如果插入结点是nullptr,插入失败，树中已经有相同的key值
	if (insertNode == _root) return true;
	if (insertNode == nullptr) return false;


	//接着更新插入结点的祖先结点的平衡因子
	Node* child = insertNode;
	Node* parent = child->_parent;//parent才是需要更新bf的结点，child用来判断parent->_bf如何更新
	while (parent != nullptr)//parent == nullptr,说明祖先结点的平衡因子已经全部更新完成
	{
		//先更新平衡因子
		//child用来判断parent->_bf如何更新
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
			//对parent这棵子树进行旋转处理+平衡因子调整
			_insertRotateAdjustBF(parent);
			break;
		}
		else
			assert(false);
	}
	return true;
}

//常规插入，返回新插入的结点指针
template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K, V>::_ordinaryInsert(const std::pair<K, V>& kv)
{
	//要插入的新结点
	Node* newNode = new Node(kv);
	
	//插入前是空树
	if (_root == nullptr)
	{
		_root = newNode;
		return _root;
	}

	//找到插入位置 和 插入位置的父亲结点，插入并链接

	Node* cur = _root;//记录插入的位置
	Node* parent = nullptr;//记录插入位置的父亲结点
	
	while (cur != nullptr)
	{
		//插入的值 > 当前结点的值（用key去比较） —— 去右树找插入位置
		//插入的值 < 当前结点的值    —— 去左树找插入位置
		//插入的值 = 当前结点的值   —— 插入失败
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
			//已经有相等的key，插入失败
			return nullptr;
		}
	}

	//如果插入结点的值比parent小，插入在左边
	//否则插入在右边
	if (kv.first < (parent->_kv).first)
		parent->_left = newNode;
	else
		parent->_right = newNode;
	
	//newNode的父亲结点一定要更新
	newNode->_parent = parent;
	
	return newNode;
}


template<class K, class V>
bool AVLTree<K, V>::erase(const K& key)
{
	//cur是被删除结点的父亲结点
	Node* cur = _ordinaryErase(key);
	
	//child是高度被降低的子树
	Node* child = nullptr;

	if (cur == nullptr)
	{
		//在删除前，可以事先保存_root的key，判断下面情况，这里直接返回true
		//1 被删除的结点是_root，不需要调整
		//2 没有找到删除的结点
		return true;
	}

	//由于可能使用替换法删除，真正被删除结点key值不能确定
	int leftTreeHeight = _height(cur->_left);
	int rightTreeHeight = _height(cur->_right);
	cur->_bf = rightTreeHeight - leftTreeHeight;

	//删除结点 会影响它的祖先结点的平衡因子
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
			//如果flag为空，旋转的新树高度不变，不需要继续调整
			Node* flag = _eraseRotateAdjustBF(cur);
			if (flag == nullptr)
				break;
			//否则沿着新根的祖先结点继续调整
			child = flag;
			cur = flag->_parent;
		}
		else
			assert(false);
	}
	return true;
}

//常规删除，返回被删除结点的父亲结点
template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K,V>::_ordinaryErase(const K& key)
{
	//记录删除结点位置 和 删除结点的父亲结点位置
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
		else//成功找到要删除的结点
		{
			//1 删除结点左子树为空
			//2 删除结点右子树为空
			//3 删除结点有两个孩子，替换法删除，左孩子的最大结点可以替换删除
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
			else//待删除结点有两个孩子，替换法删除
			{
				//左子树的最大结点替换删除
				Node* max = del->_left;
				Node* maxParent = del;;
				while (max->_right)
				{
					maxParent = max;
					max = max->_right;
				}

				del->_kv = max->_kv;

				//删除max
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

//对cur这棵子树(cur->_bf == 2)进行旋转处理
template<class K, class V>
void AVLTree<K, V>::_insertRotateAdjustBF(AVLTreeNode<K, V>* cur)
{
	//4种旋转情况需要画图，这里简单叙述
	
	//1 插入前cur的右子树较高，新插入的结点在cur右子树的右子树中 ——直接左旋
	//2 插入前cur的左子树较高，新插入的结点在cur左子树的左子树中 ——直接右旋
	//3 插入前cur的右子树较高，新插入的结点在cur右子树的左子树中 ——先对cur->right子树右旋，再对cur子树左旋
	//4 插入前cur的左子树较高，新插入的结点在cur左子树的右子树中  —— 先对cur->left子树左旋，再对cur子树右旋
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
		//有错误方便调试
		assert(false);
}

template<class K, class V>
AVLTreeNode<K,V>* AVLTree<K, V>::_eraseRotateAdjustBF(Node* cur)
{
	//返回nullptr，说明旋转后 当前子树的高度不变，不需要继续调整祖先结点
	//否则把子树的新根返回
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

//核心：画出旋转的图，提前记录要修改的结点
template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::_leftRotate(AVLTreeNode<K, V>* cur)//返回旋转后子树新的根
{
	Node* parent = cur->_parent;
	Node* right = cur->_right;
	Node* rightLeft = cur->_right->_left;

	//按图从上往下调整（注意parent和rightLeft为空的情况）
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

	//如果cur == _root，要更新_root
	if (cur == _root)
		_root = right;

	//返回这棵子树新的根
	return right;
}

template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::_rightRotate(AVLTreeNode<K,V>* cur)//返回旋转后子树新的根
{
	Node* parent = cur->_parent;
	Node* left = cur->_left;
	Node* leftRight = cur->_left->_right;

	//按图从上往下调整（注意parent和leftRight为空的情况）
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

	//如果cur == _root，要更新_root
	if (cur == _root)
		_root = left;

	//返回这棵子树新的根
	return left;
}

template<class K, class V>
AVLTreeNode<K, V>* AVLTree<K,V>::_rightLeftRotate(AVLTreeNode<K,V>* cur)
{
	//先对cur的右子树右旋
	//再对cur整体子树左旋
	//得到子树的新根
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
	//旋转完成后，用来判断平衡因子调整情况的rightLeft，成为了子树的根
	int flag = newRoot->_bf;

	//调整平衡因子
	//flag = 0:说明rightLeft就是新插入的结点
	//flag = 1:说明在c子树插入结点发生高度差改变
	//flag = -1,说明在b子树插入结点发生高度差改变
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
	//旋转完成后，用来判断平衡因子调整情况的leftRight，成为了子树的根
	int flag = newRoot->_bf;

	//flag = 0:leftRight就是新插入的结点
	//flag = 1:说明在c子树插入结点
	//flag = -1:说明在b子树插入结点
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
	//用队列层序遍历，每一层遍历完 ++ret
	int ret = 0;

	//当前层还需要遍历的结点数目
	int curLevelLeftNum = 1;

	//记录遍历到的结点
	Node* cur = nullptr;

	queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		cur = q.front();
		q.pop();

		//遍历到的结点，它的孩子不为空就入队列
		if (cur->_left != nullptr)
			q.push(cur->_left);
		if (cur->_right != nullptr)
			q.push(cur->_right);

		//当前层待遍历的结点数目-1
		curLevelLeftNum--;
		if (curLevelLeftNum == 0)//当前层遍历完成
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
	//遍历所有结点，只要所有结点都满足 其左右子树高度差不超过1 就是AVLTree

	//前序遍历
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

//判断AVLTree中一棵子树的左右高度差是否合法
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