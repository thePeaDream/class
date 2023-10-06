#include <iostream>
#include <stack>
#include <string>
using namespace std;
namespace lyh
{
	template<class K>
	struct BinarySearchTreeNode
	{
		typedef BinarySearchTreeNode<K> BSTreeNode;
		BinarySearchTreeNode(const K& key = K())
			:_left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}

		
		BSTreeNode* _left;
		BSTreeNode* _right;
		K _key;
	};

	template<class K>
	class BinarySearchTree
	{
		typedef BinarySearchTreeNode<K> Node;
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
		bool insert(const K& key)
		{
			Node* newNode = new Node(key);

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

		bool insertR(const K& key)
		{
			return _insertR(_root, key);
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

						//把替换结点的键值交给cur
						cur->_key = max->_key;
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

		bool eraseR(const K& key)
		{
			return _eraseR(_root, key);
		}

		bool find(const K& key)
		{
			Node* cur = _root;
			while (cur != nullptr)
			{
				if (key == cur->_key)
					return true;
				else if (key < cur->_key)
					cur = cur->_left;
				else if (key > cur->_key)
					cur = cur->_right;
			}
			return false;
		}

		bool findR(const K& key)
		{
			return _findR(_root, key);
		}

		void InOrder()const
		{
			_InOrderR(_root);
			cout << endl;
		}

		
	private:
		bool _findR(Node* root, const K& key)
		{
			if (root == nullptr) return false;

			if (root->_key == key)
				return true;
			else if (key > root->_key)//去右子树找
				return _findR(root->_right, key);
			else//去左子树找
				return _findR(root->_left, key);
		}

		//如果形参是Node*，root就是局部变量，root的修改不会影响二叉搜索树
		//如果改成Node*&, root就是 上一层父亲结点的孩子指针 别名
		bool _insertR(Node*& root, const K& key)
		{
			//找到插入位置
			if (root == nullptr)
			{
				root = new Node(key);
				return true;
			}

			if (key > root->_key)//如果key比根大，往右子树插入
				return _insertR(root->_right, key);
			else if (key < root->_key)//key比根小，往左子树插入
				return _insertR(root->_left, key);
			else
				return false;
		}

		bool _eraseR(Node*& root, const K& key)
		{
			if (root == nullptr) return false;

			if (key > root->_key)
				return _eraseR(root->_right, key);
			else if (key < root->_key)
				return _eraseR(root->_left, key);
				//开始删除
				//1 右为空
				//2 左为空
				//3 左右都不为空
				Node* del = root;
				if (root->_left == nullptr)
				{
					root = root->_right;
					delete del;
				}
				else if (root->_right == nullptr)
				{
					root = root->_left;
					delete del;
				}
				else//root有两个子结点，用替换法删除
				{
					Node* max = root->_left;
					Node* maxParent = root;
					while (max->_right != nullptr)
					{
						maxParent = max;
						max = max->_right;
					}
					root->_key = max->_key;
					if (maxParent->_left == max)
						maxParent->_left = max->_left;
					else
						maxParent->_right = max->_left;
					delete max;
				}
				return true;
		}

		void _InOrderR(Node* root)const
		{
			if (root == nullptr) return;

			_InOrderR(root->_left);
			cout << root->_key << " ";
			_InOrderR(root->_right);
		}

		void _InOrderNotR(Node* root)const
		{
			stack<Node*> st;
			Node* cur = root;
			
			while (!st.empty() || cur != nullptr)
			{
				//将一棵树的左边结点全部放入栈中
				while (cur != nullptr)
				{
					st.push(cur);
					cur = cur->_left;
				}
				cout << st.top()->_key << " ";
				cur = st.top()->_right;
				st.pop();
			}
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



