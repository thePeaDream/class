#include <iostream>
#include <stack>
using namespace std;
namespace yh
{
	template<class K, class V>
	struct BinarySearchTreeNode
	{
		typedef BinarySearchTreeNode<K,V> BSTreeNode;
		BinarySearchTreeNode( const K& key = K(), const V& value = V() )
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
			,_val(value)
		{}
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;
		V _val;
	};

	template<class K, class V>
	class BinarySearchTree
	{
		typedef BinarySearchTreeNode<K, V> Node;
	private:
		Node* _root;
	public:
		BinarySearchTree()
			:_root(nullptr) {}
		BinarySearchTree(const BinarySearchTree& copy)
		{
			_root = _copy(copy._root);
		}

		//赋值运算符重载，复用拷贝构造
		//copy是形参，出了作用域会销毁
		//把this的_root交换给copy，让copy帮忙销毁原空间
		//同时拿到copy的拷贝完成的树.
		BinarySearchTree& operator=(BinarySearchTree copy)
		{
			swap(copy._root, _root);
			return *this;
		}
		~BinarySearchTree()
		{
			_destory(_root);
		}

		//插入数据
		bool insert(const K& key, const V& val)
		{
			Node* newNode = new Node(key, val);

			//空树
			if (_root == nullptr)
			{
				_root = newNode;
				return true;
			}

			//找到插入位置
			Node* cur = _root;
			//记录插入位置的父亲结点
			Node* parent = nullptr;
			while (cur != nullptr)
			{
				//如果搜索树有该key,插入失败
				//否则按搜索树的规则向后找插入位置
				if (key == cur->_key)
					return false;
				else if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
			}

			//正式插入,比父亲结点大就插入到右边，否则插入到左边
			if (key > parent->_key)
				parent->_right = newNode;
			else if (key < parent->_key)
				parent->_left = newNode;
			return true;
		}

		//删除元素
		bool erase(const K& key)
		{
			// 1 找到要删除的结点
			Node* cur = _root;
			Node* parent = nullptr;

			while (cur != nullptr)
			{
				if (key > cur->_key)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (key < cur->_key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else//找到要删除的结点
				{
					//1 要删除的结点只有1/0个孩子
					if (cur->_left == nullptr)//如果删除结点的左孩子为空，就把它的右孩子托付给parent
					{
						//注意_root可能就是要删除的结点，此时要修改_root
						if (cur == _root)
							_root = cur->_right;
						else if (parent->_left == cur)
							parent->_left = cur->_right;
						else if (parent->_right == cur)
							parent->_right = cur->_right;
						delete cur;
					}
					else if (cur->_right == nullptr)//如果删除结点的右孩子为空，就把它的左孩子托付给parent
					{
						if (_root == cur)
							_root = cur->_left;
						else if (parent->_left == cur)
							parent->_left = cur->_left;
						else if (parent->_right == cur)
							parent->_right = cur->_left;
						delete cur;
					}
					else//要删除的结点有两个孩子(替换法)
					{
						//用cur的左子树最大结点 或者 cur的右子树最小结点 可以替换删除
						Node* max = cur->_left;
						Node* maxParent = cur;
						//找到替换结点和它的父亲结点
						while (max->_right != nullptr)
						{
							maxParent = max;
							max = max->_right;
						}

						//把替换结点的key和value交给cur
						cur->_key = max->_key;
						cur->_val = max->_val;

						//删除替换结点
						if (maxParent->_left == max)
							maxParent->_left = max->_left;
						else
							maxParent->_right = max->_left;
						delete max;
					}
					return true;
				}
			}

			//没有找到要删除的元素,删除失败
			return false;
		}


		//KeyValue模型 返回 结点的指针，可以用来修改对应的value
		Node* find(const K& key)
		{
			Node* cur = _root;
			while (cur != nullptr)
			{
				if (key == cur->_key)
					return cur;
				else if (key < cur->_key)
					cur = cur->_left;
				else if (key > cur->_key)
					cur = cur->_right;
			}
			return nullptr;
		}



		void InOrder()const
		{
			_InOrderR(_root);
			cout << endl;
		}


	private:

		void _InOrderR(Node* root)const
		{
			if (root == nullptr) return;

			_InOrderR(root->_left);
			cout << root->_key << "->"<< root->_val <<endl;
			_InOrderR(root->_right);
		}



		void _destory(Node* root)
		{
			if (root == nullptr)
				return;

			//后序遍历进行析构
			_destory(root->_left);
			_destory(root->_right);
			delete root;
		}

		//拷贝root这棵树，返回拷贝出来的树的根
		Node* _copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			//先拷贝根，再递归拷贝左子树、右子树
			Node* copyRoot = new Node(root->_key);
			Node* copyLeft = _copy(root->_left);
			Node* copyRight = _copy(root->_right);

			//链接
			copyRoot->_left = copyLeft;
			copyRoot->_right = copyRight;
			return copyRoot;
		}

	};
}


