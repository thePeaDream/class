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

		//��ֵ��������أ����ÿ�������
		//copy���βΣ����������������
		//��this��_root������copy����copy��æ����ԭ�ռ�
		//ͬʱ�õ�copy�Ŀ�����ɵ���.
		BinarySearchTree& operator=(BinarySearchTree copy)
		{
			swap(copy._root, _root);
			return *this;
		}
		~BinarySearchTree()
		{
			_destory(_root);
		}

		//��������
		bool insert(const K& key)
		{
			Node* newNode = new Node(key);

			//����
			if (_root == nullptr)
			{
				_root = newNode;
				return true;
			}

			//�ҵ�����λ��
			Node* cur = _root;
			//��¼����λ�õĸ��׽��
			Node* parent = nullptr;
			while (cur != nullptr)
			{
				//����������и�key,����ʧ��
				//�����������Ĺ�������Ҳ���λ��
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

			//��ʽ����,�ȸ��׽���Ͳ��뵽�ұߣ�������뵽���
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

		//ɾ��Ԫ��
		bool erase(const K& key)
		{
			// 1 �ҵ�Ҫɾ���Ľ��
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
				else//�ҵ�Ҫɾ���Ľ��
				{
					//1 Ҫɾ���Ľ��ֻ��1/0������
					if (cur->_left == nullptr)//���ɾ����������Ϊ�գ��Ͱ������Һ����и���parent
					{
						//ע��_root���ܾ���Ҫɾ���Ľ�㣬��ʱҪ�޸�_root
						if (cur == _root)
							_root = cur->_right;
						else if (parent->_left == cur)
							parent->_left = cur->_right;
						else if (parent->_right == cur)
							parent->_right = cur->_right;
						delete cur;
					}
					else if (cur->_right == nullptr)//���ɾ�������Һ���Ϊ�գ��Ͱ����������и���parent
					{
						if (_root == cur)
							_root = cur->_left;
						else if (parent->_left == cur)
							parent->_left = cur->_left;
						else if (parent->_right == cur)
							parent->_right = cur->_left;
						delete cur;
					}
					else//Ҫɾ���Ľ������������(�滻��)
					{
						//��cur������������� ���� cur����������С��� �����滻ɾ��
						Node* max = cur->_left;
						Node* maxParent = cur;
						//�ҵ��滻�������ĸ��׽��
						while (max->_right != nullptr)
						{
							maxParent = max;
							max = max->_right;
						}

						//���滻���ļ�ֵ����cur
						cur->_key = max->_key;
						//ɾ���滻���
						if (maxParent->_left == max)
							maxParent->_left = max->_left;
						else
							maxParent->_right = max->_left;
						delete max;
					}
					return true;
				}
			}
			
			//û���ҵ�Ҫɾ����Ԫ��,ɾ��ʧ��
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
			else if (key > root->_key)//ȥ��������
				return _findR(root->_right, key);
			else//ȥ��������
				return _findR(root->_left, key);
		}

		//����β���Node*��root���Ǿֲ�������root���޸Ĳ���Ӱ�����������
		//����ĳ�Node*&, root���� ��һ�㸸�׽��ĺ���ָ�� ����
		bool _insertR(Node*& root, const K& key)
		{
			//�ҵ�����λ��
			if (root == nullptr)
			{
				root = new Node(key);
				return true;
			}

			if (key > root->_key)//���key�ȸ���������������
				return _insertR(root->_right, key);
			else if (key < root->_key)//key�ȸ�С��������������
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
				//��ʼɾ��
				//1 ��Ϊ��
				//2 ��Ϊ��
				//3 ���Ҷ���Ϊ��
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
				else//root�������ӽ�㣬���滻��ɾ��
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
				//��һ��������߽��ȫ������ջ��
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

			//���������������
			_destory(root->_left);
			_destory(root->_right);
			delete root;
		}

		//����root����������ؿ������������ĸ�
		Node* _copy(Node* root)
		{
			if (root == nullptr)
				return nullptr;
			//�ȿ��������ٵݹ鿽����������������
			Node* copyRoot = new Node(root->_key);
			Node* copyLeft = _copy(root->_left);
			Node* copyRight = _copy(root->_right);

			//����
			copyRoot->_left = copyLeft;
			copyRoot->_right = copyRight;
			return copyRoot;
		}

	};
}



