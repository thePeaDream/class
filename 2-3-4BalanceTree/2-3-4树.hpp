#include<iostream>
#include<vector>
#include <assert.h>
#include <time.h>
#include <stack>
#include <queue>
using namespace std;

//2-3-4���Ľ��
template<class K, class V>
struct BalanceTreeNode
{
	BalanceTreeNode(const pair<K, V>& kv)
	{
		_kv[0] = kv;
		for (int i = 0; i < 5; ++i)
			_child[i] = nullptr;
	}

	//������Ԫ�أ����ֻ�ܰ���3��Ԫ�أ���4���ռ䷽���ѱ䣩
	pair<K, V> _kv[4];
	//������Ԫ�ظ���
	int _num = 1;

	//���׽��
	BalanceTreeNode* _parent = nullptr;

	//��������4�����ӽ�㣨����1���ռ������ѱ䣩
	BalanceTreeNode* _child[5];
	//���ӽ����Ŀ
	int _childNum = 0;
};

template<class K, class V>
class BalanceTree
{
	typedef BalanceTreeNode<K, V> Node;
private:
	Node* _root = nullptr;
public:
	//����
	bool find(const K& key)
	{
		//�Ӹ���ʼ��
		Node* cur = _root;
		//ֱ��curΪ�ս��
		while (cur != nullptr)
		{
			int i = 0;
			//������cur������Ԫ�رȽ�
			for(i = 0; i < cur->_num; ++i)
			{
				//��������key�Ƚ�
				
				//�� Ŀ��Ԫ�� �� cur���������Ԫ�� �󣬼���������cur���Ԫ��
				//�� Ŀ��Ԫ�� �� cur���������Ԫ�� С��ȥcur�ĵ�i�����ӽ��/�����ҡ�����cur��
				if (key > cur->_kv[i].first)
					continue;
				if (key < cur->_kv[i].first)
					break;
				if (key == cur->_kv[i].first)
					return true;
			}

			//û���ҵ��������cur
			//1 ��Ŀ��Ԫ�� �� cur�����i��Ԫ�� С
			//2 ��Ŀ��Ԫ�� �� cur��������Ԫ�� ��
			if (i < cur->_num)
				cur = cur->_child[i];
			else
			{
				if (cur->_childNum == 0)//curû�к���
					return false;
				else
					cur = cur->_child[cur->_childNum - 1];
			}
		}
		return false;
	}
	
	//����
	bool insert(const pair<K, V>& kv)
	{
		//����
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		
		//�Ӹ���ʼ���ҵ����Բ����Ҷ�ӽ��
		Node* cur = _root;
		//2-3-4����ÿ����㣬Ҫôû�к��ӣ�Ҫô����������
		while (cur->_childNum != 0)
		{
			//kv С�� ��ǰ���ĵ�һ��Ԫ�أ���ȥ ��ǰ���ĵ�һ������ ��
			//���ȵ�ǰ��������Ԫ��Ҫ��ȥ���������Ҳ�����
			int i = 0;
			for (i = 0; i < cur->_num; ++i)
			{
				if (kv.first < cur->_kv[i].first)
					break;
				else if (kv.first == cur->_kv[i].first)//����ʧ�ܣ��Ѿ�����ͬ��key
					return false;
				else
					continue;
			}
			//kvС��cur�ĵ�i��Ԫ�أ�ȥ��i��������
			//��kv����������Ԫ�أ�ȥ���һ�������ң���ǰiҲ�������һ��������λ��
			cur = cur->_child[i];
		}

		//��ʱcur��Ҷ�ӽ�㣬���Բ���
		//����������Ԫ��
		_mergeElement(cur, kv);

		//����ǰ���Ԫ��Ϊ4����Ҫ�ѱ�
		while (cur->_num == 4)
		{
			Node* parent  = _fission(cur);
			cur = parent;
		}
		return true;
	}

	//ɾ��
	bool erase(const K& key)
	{
		if (_root == nullptr)
			return false;

		//�Ӹ���ʼ������ɾ��Ԫ��
		Node* cur = _root;

		while (cur != nullptr)
		{		
			//��ʶ�Ƿ��ҵ�Ԫ��
			bool flag = false;

			//��ÿ�����ɨ��������Ԫ��
			//�� key С�� ��ǰ���ĵ�pos��Ԫ�أ�ȥ��pos�����ӽ����
			//�� key ���� ��ǰ���ĵ�pos��Ԫ�أ������ڵ�ǰ��������
			int pos = 0;
			for (pos = 0; pos < cur->_num; ++pos)
			{
				if (key > cur->_kv[pos].first)
					continue;
				else if (key == cur->_kv[pos].first)//�ҵ�Ҫɾ����Ԫ��
				{
					flag = true;
					break;
				}
				else if (key < cur->_kv[pos].first)//ȥcur->_child[pos]����
					break;
			}

			//�ҵ�ɾ��Ԫ�أ���ʱɾ��Ԫ��λ��cur��
			if (flag == true) 
				break;

			if (cur->_childNum != 0)
			{
				//����ȥ��pos�����ӽ����
				cur = cur->_child[pos];
			}
			else//cur��Ҷ�ӽ�㣬ͬʱû����cur�ҵ�Ҫɾ����Ԫ��
				cur = nullptr;
		}

		//û�ҵ�ɾ��Ԫ��
		if (cur == nullptr) return false;

		//cur����Ҫɾ��Ԫ��λ�ڵĽ��
		int pos = 0;
		for (pos = 0; pos < cur->_num; ++pos)
		{
			//�ҵ�ɾ��Ԫ�صľ���λ�ú�ֹͣ
			if (cur->_kv[pos].first == key)
				break;
		}
		//��ʱɾ��Ԫ�صľ���λ�þ��� cur->_kv[pos]


		//���cur����Ҷ�ӽ�㣬���滻��ת����ɾ��Ҷ�ӽ���Ԫ�أ�
		//�ѱ���ɾ����Ԫ���� cur->_child[pos]���������Ԫ�� �滻��ת����ɾ�������Ԫ��
		if (cur->_childNum != 0)
		{
			//��Ҷ�ӽ�㣬�滻��ת�� Ҫɾ����Ԫ��
			//��cur->_child[pos]���������Ԫ���滻
			Node* max = cur->_child[pos];//���Ԫ����λ�ڵĽ����max��¼
			
			//����ȥmax������������
			while (max->_child[max->_childNum - 1] != nullptr)
				max = max->_child[max->_childNum - 1];

			//��ʱ��max���Ԫ�� ��ֵ�� ����ɾ����Ԫ��
			cur->_kv[pos] = max->_kv[max->_num - 1];
			
			//Ҫɾ����Ԫ��λ�ڵĽ����£�����λ��Ҳ����
			cur = max;
			pos = max->_num - 1;
		}

		//��ʱcur��ɾ��Ԫ��λ�ڵĽ�㣬pos��ɾ��Ԫ���ڽ���λ��
		//��curһ����Ҷ�ӽ��
		
		// ��cur����ж���һ��Ԫ�أ�����ֱ��ɾ��������Ҫ���ദ��
		if (cur->_num > 1)
		{
			_deleteElement(cur, cur->_kv[pos]);
			return true;
		}
		else//��cur���ֻ��һ��Ԫ�أ�����ֱ��ɾ��
		{
			//���˼·��Ҫ��ͼ����
			//cur���׽���һ��Ԫ��
			//1 ��ʱ���׽������һ��Ԫ�أ�������cur�������ֵܽ�㣨һ��Ҳ��Ҷ�ӽ�㣬���Ա�����Ԫ�ز�����Ӱ�죩��һ��Ԫ��

			//2 ���cur�������ֵܽ��Ҳֻ��һ��Ԫ�أ�
			//���׽������һ��Ԫ�أ���ζ�ű���Ҫ��һ�����ӣ�������Ҫcur��cur�����ֵܺϲ���һ���½�㣬��Ϊ���׽��ĺ���

			//(1)�����׽���ʱԪ�ظ��� > 0���������
			//(2)�����׽��Ԫ�ظ��� = 0���ظ����׽��ĸ��׽���Ԫ�أ��ϲ����׽��͸��׽��������ֵܽ�㣨���������������ֵܽ��裩
			//��ֹ�����������ٴ���ĳ�������ĿΪ0


			//���⣺cur��_root,��_rootֻ��һ��Ԫ��
			if (cur == _root)
			{
				delete _root;
				_root = nullptr;
				return true;
			}

			//Ҫ��֪��cur�Ǹ��׽��ĵڼ������ӣ�cur���׽���һ��Ԫ�� ���� ���ĸ�Ԫ��ȡ����cur�ǵڼ������ӣ�
			Node* parent = cur->_parent;
			int pos = 0;
			for (pos = 0; pos < parent->_childNum; ++pos)
				if (parent->_child[pos] == cur)break;

			//parent��2-3-4���ķ�Ҷ�ӽ�㣬�������ĺ��ӽ����Ŀ = Ԫ����Ŀ+1
			//��������pos��Ԫ�أ����pos���������һ�����ӽ��λ�õĻ������⴦��
			int lent = pos;
			if (pos == parent->_childNum - 1)
				--lent;

			//�Ƚ踸�׽����˵
			//���׽����Ԫ����parent->_kv[lent]
			cur->_kv[0] = parent->_kv[lent];

			//�ȿ�cur�����ֵܽ���Ƿ��ж����Ԫ��
			Node* curBother = _neighboringBother(cur);
			//cur�����ֵܽ���ж����Ԫ�أ����׽��ֱ�ӽ�
			if (curBother->_num > 1)
			{
				//��������ֵܽ�� �� cur����ߣ��ͽ������ֵܽ������һ��Ԫ��
				//������һ��Ԫ��
				if (curBother->_kv[0].first < cur->_kv[0].first)
				{
					parent->_kv[lent] = curBother->_kv[curBother->_num - 1];
					_deleteElement(curBother, curBother->_kv[curBother->_num - 1]);
				}
				else
				{
					parent->_kv[lent] = curBother->_kv[0];
					_deleteElement(curBother, curBother->_kv[0]);
				}
				return true;
			}
			else//cur���ڵ��ֵܽ��û�ж����Ԫ�ؿ��Ը����׽��
			{
				//��ʱ���׽�㱻���ߵ�Ԫ�ز���������
				_deleteElement(parent, parent->_kv[lent]);
				Node* newNode = _mergeNode(cur, curBother);
				if (parent->_num > 0)
					return true;
				else//���׽�㱻�����
				{
					//cur��Ϊ����յĽ�㣬���д���
					cur = parent;
					while ( cur != _root && cur->_num == 0)//����㱻���/curû�б���� �˳�
					{
						//���׽���Ԫ��
						parent = cur->_parent;
						_lent(cur, parent);

						//cur��cur�����ֵܽ��ϲ�
						curBother = _neighboringBother(cur);
						Node* newNode = _mergeNode(cur, curBother);

						//1 �ϲ��Ժ󣬿��ܻᷢ���ѱ�������ѱ���ɺ�ȫ���������
						if (newNode->_num == 4)
						{
							_fission(newNode);
							return true;
						}

						//2 �ϲ��Ժ�û���ѱ䣬���������׽���Ԫ����Ŀ�Ƿ� > 0.
						cur = newNode->_parent;
					}
					if (cur->_num > 0)
						return true;
					else//˵��������Ԫ�ر�����ˣ���Ҫ��������
					{
						//��ʱcur == _root
						//_rootӦ�ñ��޸�
						_root = newNode;
						_root->_parent = nullptr;
						delete cur;
						return true;
					}
				}
			
			}
		}

	}
	
	bool isBalanceTree()
	{
		if (_root == nullptr) return true;
		
		//������ȱ���
		//ÿ������Ԫ����Ŀֻ����1/2/3����Ҷ�ӽ���Ӧ�ĺ�����������2/3/4

		stack<Node*> st;
		st.push(_root);
		while (!st.empty())
		{
			//����ǰ���
			Node* top = st.top();
			if (top->_num >= 4 || top->_num <= 0)
			{
				cout << "�н���Ԫ����Ŀ�Ƿ�" << endl;
				return false;
			}

			if (top->_child[0] == nullptr)//�����Ҷ�ӽ��
				assert(top->_childNum == 0);
			else//����Ҷ�ӽ��
				assert(top->_childNum == top->_num + 1);
			
			st.pop();

			//�����һ�����ӿ�ʼ������ջ����֤����ȳ�
			for (int i = top->_childNum - 1; i >= 0; --i)
				st.push(top->_child[i]);
		}
		return true;
	}

	//�������
	void printTree()
	{
		if (_root == nullptr)return;
		int high = 1;
		int curLeftNum = 1;
		queue<Node*> q;
		q.push(_root);
		while (!q.empty())
		{
			Node* cur = q.front();
			q.pop();
			for (int i = 0; i < cur->_num; ++i)
				cout << cur->_kv[i].first << " ";
			cout << "       ";

			for (int i = 0; i < cur->_childNum; ++i)
				q.push(cur->_child[i]);

			curLeftNum--;
			if (curLeftNum == 0)
			{
				curLeftNum = q.size();
				high++;
				cout << endl;
			}
		}
		cout << high;
	}

private:
	//��һ�����node������һ��Ԫ��
	//���غϲ����Ԫ�ز�����±�λ��
	size_t _mergeElement(Node* node, const pair<K, V>& p)
	{
		assert(node);

		int pos = 0;
		//�ҵ�����λ��
		while (pos < node->_num && p.first > node->_kv[pos].first)
			++pos;

		if (node->_kv[pos].first == p.first)
			return -1;

		//����Ų��Ԫ��
		for (int begin = node->_num - 1; begin >= pos; --begin)
			node->_kv[begin + 1] = node->_kv[begin];
		
		//��ʽ���룬ͬʱ����node->_num
		node->_kv[pos] = p;
		++node->_num;

		return pos;
	}


	//ǰ�᣺node1��node2���ֵܽ�㣬��node1->_kv[0] < node2->_kv[0]
	//�ϲ�node1��node2,ͬʱ�ͷŵ�node2�Ľ��ռ�,node1�Ǻϲ��Ľ��
	//���غϲ���ɵĽ��
	Node* _mergeNode(Node* node1, Node* node2)
	{
		Node* min = node1;
		Node* max = node2;
		if (min->_kv[0].first > max->_kv[0].first)
			swap(min, max);

		//��max��Ԫ��ȫ��β�嵽minԪ�غ��棬ÿ��β�嶼Ҫ ++min->_num
		for (int i = 0; i < max->_num; ++i)
			min->_kv[ min->_num++ ] = max->_kv[i];
		
		//��max�ĺ��ӽ�����ν���min��ÿ�ζ�Ҫ����min�ĺ��ӽ����Ŀ
		for (int i = 0; i < max->_childNum; ++i)
		{
			min->_child[min->_childNum++] = max->_child[i];
			max->_child[i]->_parent = min;
		}
		//max��min�ĸ��׽�㣬������Ҫ����
		Node* parent = max->_parent;

		//min��max���ֵܽ�㣬�����Ǿ�Ȼû�и��׽�㣬������
		if (parent == nullptr) assert(false);

		//���ж�min��parent�ĵڼ�������
		int pos1 = -1;
		for (int i = 0; i < parent->_childNum; ++i)
		{
			if (parent->_child[i] == min)
			{
				pos1 = i;
				break;
			}
		}

		//����ɾ��pos1λ�õĺ��ӽ��
		for (int begin = pos1+1; begin <= parent->_childNum-1; ++begin)
			parent->_child[begin-1] = parent->_child[begin];
		--parent->_childNum;
		
		//��λ�õĺ��ӽ���Ϊ�ϲ���ɵĽ��node1
		parent->_child[pos1] = min;
		delete max;
		
		return min;
	}

	//�ѱ�(���Ľ�㣬Ԫ����Ŀ����Ϊ4),���ظ��׽��
	Node* _fission(Node* node)
	{
		//��node�����Ԫ�� �½�һ�����
		Node* newLeft = new Node(node->_kv[0]);
		if (node->_childNum == 0)//Ҷ�ӽ�㷢�����ѱ�
		{
			newLeft->_num = 1;
			newLeft->_childNum = 0;
		}
		else if (node->_childNum != 0)//��Ҷ�ӽ�㷢�����ѱ�
		{
			newLeft->_child[0] = node->_child[0];
			newLeft->_child[1] = node->_child[1];
			newLeft->_childNum = 2;

			//ע�⸸�ӹ�ϵ�ĵ���
			newLeft->_child[0]->_parent = newLeft;
			newLeft->_child[1]->_parent = newLeft;
		}

		//��node���ұ�Ԫ�� �½�һ�����
		Node* newRight = new Node(node->_kv[2]);
		_mergeElement(newRight,node->_kv[3]);
		if (node->_childNum == 0)//Ҷ�ӽ�㷢�����ѱ�
		{
			newRight->_num = 2;
			newRight->_childNum = 0;
		}
		else if (node->_childNum != 0)
		{
			newRight->_child[0] = node->_child[2];
			newRight->_child[1] = node->_child[3];
			newRight->_child[2] = node->_child[4];
			newRight->_childNum = 3;
			
			newRight->_child[0]->_parent = newRight;
			newRight->_child[1]->_parent = newRight;
			newRight->_child[2]->_parent = newRight;
		}

		//node���м�Ԫ���븸�׽��ϲ�
		Node* parent = node->_parent;

		//���׽��Ϊ�գ��µĸ�����
		if ( parent == nullptr )
		{
			_root = new Node(node->_kv[1]);
			_root->_child[0] = newLeft;
			_root->_child[1] = newRight;
			newLeft->_parent = _root;
			newRight->_parent = _root;
			_root->_childNum = 2;
			delete node;
			return _root;
		}

		//���׽�㲻Ϊ��

		//�ѱ���ĵڶ���Ԫ�� �� parent �ϲ�
		size_t pos = _mergeElement(parent, node->_kv[1]);

		//newLeft��newRight������pos��pos+1��λ�ã�pos+1������ĺ������Ųһ��
		for (int end = parent->_childNum - 1; end >= pos+1; --end)
			parent->_child[end + 1] = parent->_child[end];
		++parent->_childNum;
		//����parent �� newLeft/newRight
		parent->_child[pos] = newLeft;
		parent->_child[pos+1] = newRight;
		newLeft->_parent = parent;
		newRight->_parent = parent;
		
		return parent;
	}

	//�����ɾ��һ��Ԫ��
	void _deleteElement(Node* node, const pair<K,V>& kv)
	{
		int search = 0;
		for ( search = 0; search < node->_num; ++search)
		{
			if (kv.first == node->_kv[search].first)
				break;
		}

		for (int begin = search + 1; begin <= node->_num - 1; ++begin)
			node->_kv[begin - 1] = node->_kv[begin];
		--node->_num;
	}

	//�����ڵ��ֵܽ��
	Node* _neighboringBother(Node* cur)
	{
		Node* parent = cur->_parent;
		
		//û���ֵܽ�㣬cur���Ǹ�
		if (parent == nullptr) return nullptr;

		//cur�ǵ�pos�����ӽ��
		int pos = 0;
		for (pos = 0; pos < parent->_childNum; ++pos)
		{
			if (parent->_child[pos] == cur)
				break;
		}
		if (pos == parent->_childNum - 1)
			return parent->_child[pos - 1];
		else
			return parent->_child[pos + 1];
	}

	//curԪ��Ϊ�գ���parent��Ԫ��
	//--parent->_num
	void _lent(Node* cur, Node* parent)
	{
		//cur��parent�ĵڼ�������
		int i = 0;
		for ( i = 0; i < parent->_childNum; ++i)
		{
			if (parent->_child[i] == cur)
				break;
		}

		if (i == parent->_childNum - 1)
			--i;
		cur->_kv[0] = parent->_kv[i];
		++cur->_num;
		_deleteElement(parent, parent->_kv[i]);
	}

};


