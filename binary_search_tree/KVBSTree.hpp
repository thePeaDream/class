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
		bool insert(const K& key, const V& val)
		{
			Node* newNode = new Node(key, val);

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

						//���滻����key��value����cur
						cur->_key = max->_key;
						cur->_val = max->_val;

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


		//KeyValueģ�� ���� ����ָ�룬���������޸Ķ�Ӧ��value
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


