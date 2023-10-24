#include<iostream>
#include<vector>
#include <assert.h>
#include <time.h>
#include <stack>
#include <queue>
using namespace std;

//2-3-4树的结点
template<class K, class V>
struct BalanceTreeNode
{
	BalanceTreeNode(const pair<K, V>& kv)
	{
		_kv[0] = kv;
		for (int i = 0; i < 5; ++i)
			_child[i] = nullptr;
	}

	//包含的元素（最多只能包含3个元素，开4个空间方便裂变）
	pair<K, V> _kv[4];
	//包含的元素个数
	int _num = 1;

	//父亲结点
	BalanceTreeNode* _parent = nullptr;

	//最多可以有4个孩子结点（开多1个空间用于裂变）
	BalanceTreeNode* _child[5];
	//孩子结点数目
	int _childNum = 0;
};

template<class K, class V>
class BalanceTree
{
	typedef BalanceTreeNode<K, V> Node;
private:
	Node* _root = nullptr;
public:
	//查找
	bool find(const K& key)
	{
		//从根开始找
		Node* cur = _root;
		//直到cur为空结点
		while (cur != nullptr)
		{
			int i = 0;
			//依次与cur的所有元素比较
			for(i = 0; i < cur->_num; ++i)
			{
				//这里是用key比较
				
				//当 目标元素 比 cur里遍历到的元素 大，继续向后遍历cur里的元素
				//当 目标元素 比 cur里遍历到的元素 小，去cur的第i个孩子结点/子树找【更新cur】
				if (key > cur->_kv[i].first)
					continue;
				if (key < cur->_kv[i].first)
					break;
				if (key == cur->_kv[i].first)
					return true;
			}

			//没有找到都会更新cur
			//1 若目标元素 比 cur里面第i个元素 小
			//2 若目标元素 比 cur里面所有元素 大
			if (i < cur->_num)
				cur = cur->_child[i];
			else
			{
				if (cur->_childNum == 0)//cur没有孩子
					return false;
				else
					cur = cur->_child[cur->_childNum - 1];
			}
		}
		return false;
	}
	
	//插入
	bool insert(const pair<K, V>& kv)
	{
		//空树
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}
		
		//从根开始，找到可以插入的叶子结点
		Node* cur = _root;
		//2-3-4树的每个结点，要么没有孩子，要么孩子是满的
		while (cur->_childNum != 0)
		{
			//kv 小于 当前结点的第一个元素，就去 当前结点的第一棵子树 找
			//若比当前结点的所有元素要大，去最右子树找插入结点
			int i = 0;
			for (i = 0; i < cur->_num; ++i)
			{
				if (kv.first < cur->_kv[i].first)
					break;
				else if (kv.first == cur->_kv[i].first)//插入失败，已经有相同的key
					return false;
				else
					continue;
			}
			//kv小于cur的第i个元素，去第i个子树找
			//若kv大于其所有元素，去最后一棵子树找，当前i也会是最后一棵子树的位置
			cur = cur->_child[i];
		}

		//此时cur是叶子结点，可以插入
		//往结点里插入元素
		_mergeElement(cur, kv);

		//若当前结点元素为4，需要裂变
		while (cur->_num == 4)
		{
			Node* parent  = _fission(cur);
			cur = parent;
		}
		return true;
	}

	//删除
	bool erase(const K& key)
	{
		if (_root == nullptr)
			return false;

		//从根开始向下找删除元素
		Node* cur = _root;

		while (cur != nullptr)
		{		
			//标识是否找到元素
			bool flag = false;

			//对每个结点扫描其所有元素
			//若 key 小于 当前结点的第pos个元素，去第pos个孩子结点找
			//若 key 大于 当前结点的第pos个元素，继续在当前结点向后找
			int pos = 0;
			for (pos = 0; pos < cur->_num; ++pos)
			{
				if (key > cur->_kv[pos].first)
					continue;
				else if (key == cur->_kv[pos].first)//找到要删除的元素
				{
					flag = true;
					break;
				}
				else if (key < cur->_kv[pos].first)//去cur->_child[pos]中找
					break;
			}

			//找到删除元素，此时删除元素位于cur里
			if (flag == true) 
				break;

			if (cur->_childNum != 0)
			{
				//否则去第pos个孩子结点找
				cur = cur->_child[pos];
			}
			else//cur是叶子结点，同时没有在cur找到要删除的元素
				cur = nullptr;
		}

		//没找到删除元素
		if (cur == nullptr) return false;

		//cur就是要删除元素位于的结点
		int pos = 0;
		for (pos = 0; pos < cur->_num; ++pos)
		{
			//找到删除元素的具体位置后停止
			if (cur->_kv[pos].first == key)
				break;
		}
		//此时删除元素的具体位置就是 cur->_kv[pos]


		//如果cur不是叶子结点，用替换法转换成删除叶子结点的元素，
		//把本该删除的元素用 cur->_child[pos]子树的最大元素 替换，转换成删除该最大元素
		if (cur->_childNum != 0)
		{
			//非叶子结点，替换法转换 要删除的元素
			//用cur->_child[pos]子树的最大元素替换
			Node* max = cur->_child[pos];//最大元素所位于的结点用max记录
			
			//不断去max的最右子树找
			while (max->_child[max->_childNum - 1] != nullptr)
				max = max->_child[max->_childNum - 1];

			//此时用max最大元素 赋值给 本该删除的元素
			cur->_kv[pos] = max->_kv[max->_num - 1];
			
			//要删除的元素位于的结点更新，具体位置也更新
			cur = max;
			pos = max->_num - 1;
		}

		//此时cur是删除元素位于的结点，pos是删除元素在结点的位置
		//且cur一定是叶子结点
		
		// 若cur结点有多于一个元素，可以直接删除，不需要多余处理
		if (cur->_num > 1)
		{
			_deleteElement(cur, cur->_kv[pos]);
			return true;
		}
		else//若cur结点只有一个元素，不能直接删除
		{
			//大概思路（要画图）：
			//cur向父亲结点借一个元素
			//1 此时父亲结点少了一个元素，可以向cur的相邻兄弟结点（一定也是叶子结点，所以被借走元素不会有影响）借一个元素

			//2 如果cur的相邻兄弟结点也只有一个元素，
			//父亲结点少了一个元素，意味着必须要少一个孩子，所以需要cur和cur相邻兄弟合并成一个新结点，作为父亲结点的孩子

			//(1)若父亲结点此时元素个数 > 0，调整完成
			//(2)若父亲结点元素个数 = 0，重复向父亲结点的父亲结点借元素，合并父亲结点和父亲结点的相邻兄弟结点（接下来不会再向兄弟结点借）
			//终止条件：不会再存在某个结点数目为0


			//特殊：cur是_root,且_root只有一个元素
			if (cur == _root)
			{
				delete _root;
				_root = nullptr;
				return true;
			}

			//要先知道cur是父亲结点的第几个孩子（cur向父亲结点借一个元素 —— 借哪个元素取决于cur是第几个孩子）
			Node* parent = cur->_parent;
			int pos = 0;
			for (pos = 0; pos < parent->_childNum; ++pos)
				if (parent->_child[pos] == cur)break;

			//parent是2-3-4树的非叶子结点，所以它的孩子结点数目 = 元素数目+1
			//我这里借第pos个元素，如果pos正好是最后一个孩子结点位置的话，特殊处理
			int lent = pos;
			if (pos == parent->_childNum - 1)
				--lent;

			//先借父亲结点再说
			//向父亲结点借的元素是parent->_kv[lent]
			cur->_kv[0] = parent->_kv[lent];

			//先看cur相邻兄弟结点是否有多余的元素
			Node* curBother = _neighboringBother(cur);
			//cur相邻兄弟结点有多余的元素，父亲结点直接借
			if (curBother->_num > 1)
			{
				//如果相邻兄弟结点 在 cur的左边，就借相邻兄弟结点的最后一个元素
				//否则借第一个元素
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
			else//cur相邻的兄弟结点没有多余的元素可以给父亲结点
			{
				//此时父亲结点被拿走的元素补不回来了
				_deleteElement(parent, parent->_kv[lent]);
				Node* newNode = _mergeNode(cur, curBother);
				if (parent->_num > 0)
					return true;
				else//父亲结点被借空了
				{
					//cur作为被借空的结点，进行处理
					cur = parent;
					while ( cur != _root && cur->_num == 0)//根结点被借空/cur没有被借空 退出
					{
						//向父亲结点借元素
						parent = cur->_parent;
						_lent(cur, parent);

						//cur与cur相邻兄弟结点合并
						curBother = _neighboringBother(cur);
						Node* newNode = _mergeNode(cur, curBother);

						//1 合并以后，可能会发生裂变情况，裂变完成后全部调整完成
						if (newNode->_num == 4)
						{
							_fission(newNode);
							return true;
						}

						//2 合并以后，没有裂变，继续看父亲结点的元素数目是否 > 0.
						cur = newNode->_parent;
					}
					if (cur->_num > 0)
						return true;
					else//说明根结点的元素被借空了，需要更换根了
					{
						//此时cur == _root
						//_root应该被修改
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
		
		//深度优先遍历
		//每个结点的元素数目只能是1/2/3，非叶子结点对应的孩子数必须是2/3/4

		stack<Node*> st;
		st.push(_root);
		while (!st.empty())
		{
			//处理当前结点
			Node* top = st.top();
			if (top->_num >= 4 || top->_num <= 0)
			{
				cout << "有结点的元素数目非法" << endl;
				return false;
			}

			if (top->_child[0] == nullptr)//如果是叶子结点
				assert(top->_childNum == 0);
			else//不是叶子结点
				assert(top->_childNum == top->_num + 1);
			
			st.pop();

			//从最后一个孩子开始依次入栈，保证后进先出
			for (int i = top->_childNum - 1; i >= 0; --i)
				st.push(top->_child[i]);
		}
		return true;
	}

	//层序遍历
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
	//让一个结点node，新增一个元素
	//返回合并完后，元素插入的下标位置
	size_t _mergeElement(Node* node, const pair<K, V>& p)
	{
		assert(node);

		int pos = 0;
		//找到插入位置
		while (pos < node->_num && p.first > node->_kv[pos].first)
			++pos;

		if (node->_kv[pos].first == p.first)
			return -1;

		//往后挪动元素
		for (int begin = node->_num - 1; begin >= pos; --begin)
			node->_kv[begin + 1] = node->_kv[begin];
		
		//正式插入，同时增加node->_num
		node->_kv[pos] = p;
		++node->_num;

		return pos;
	}


	//前提：node1和node2是兄弟结点，且node1->_kv[0] < node2->_kv[0]
	//合并node1和node2,同时释放掉node2的结点空间,node1是合并的结点
	//返回合并完成的结点
	Node* _mergeNode(Node* node1, Node* node2)
	{
		Node* min = node1;
		Node* max = node2;
		if (min->_kv[0].first > max->_kv[0].first)
			swap(min, max);

		//将max的元素全部尾插到min元素后面，每次尾插都要 ++min->_num
		for (int i = 0; i < max->_num; ++i)
			min->_kv[ min->_num++ ] = max->_kv[i];
		
		//将max的孩子结点依次交给min，每次都要增加min的孩子结点数目
		for (int i = 0; i < max->_childNum; ++i)
		{
			min->_child[min->_childNum++] = max->_child[i];
			max->_child[i]->_parent = min;
		}
		//max和min的父亲结点，孩子需要更新
		Node* parent = max->_parent;

		//min和max是兄弟结点，但它们居然没有父亲结点，不可能
		if (parent == nullptr) assert(false);

		//先判断min是parent的第几个孩子
		int pos1 = -1;
		for (int i = 0; i < parent->_childNum; ++i)
		{
			if (parent->_child[i] == min)
			{
				pos1 = i;
				break;
			}
		}

		//覆盖删除pos1位置的孩子结点
		for (int begin = pos1+1; begin <= parent->_childNum-1; ++begin)
			parent->_child[begin-1] = parent->_child[begin];
		--parent->_childNum;
		
		//该位置的孩子结点改为合并完成的结点node1
		parent->_child[pos1] = min;
		delete max;
		
		return min;
	}

	//裂变(传的结点，元素数目必须为4),返回父亲结点
	Node* _fission(Node* node)
	{
		//用node的左边元素 新建一个结点
		Node* newLeft = new Node(node->_kv[0]);
		if (node->_childNum == 0)//叶子结点发生的裂变
		{
			newLeft->_num = 1;
			newLeft->_childNum = 0;
		}
		else if (node->_childNum != 0)//非叶子结点发生的裂变
		{
			newLeft->_child[0] = node->_child[0];
			newLeft->_child[1] = node->_child[1];
			newLeft->_childNum = 2;

			//注意父子关系的调整
			newLeft->_child[0]->_parent = newLeft;
			newLeft->_child[1]->_parent = newLeft;
		}

		//用node的右边元素 新建一个结点
		Node* newRight = new Node(node->_kv[2]);
		_mergeElement(newRight,node->_kv[3]);
		if (node->_childNum == 0)//叶子结点发生的裂变
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

		//node的中间元素与父亲结点合并
		Node* parent = node->_parent;

		//父亲结点为空，新的根诞生
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

		//父亲结点不为空

		//裂变结点的第二个元素 和 parent 合并
		size_t pos = _mergeElement(parent, node->_kv[1]);

		//newLeft和newRight插入在pos和pos+1的位置，pos+1及后面的孩子向后挪一格
		for (int end = parent->_childNum - 1; end >= pos+1; --end)
			parent->_child[end + 1] = parent->_child[end];
		++parent->_childNum;
		//链接parent 和 newLeft/newRight
		parent->_child[pos] = newLeft;
		parent->_child[pos+1] = newRight;
		newLeft->_parent = parent;
		newRight->_parent = parent;
		
		return parent;
	}

	//结点里删除一个元素
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

	//求相邻的兄弟结点
	Node* _neighboringBother(Node* cur)
	{
		Node* parent = cur->_parent;
		
		//没有兄弟结点，cur就是根
		if (parent == nullptr) return nullptr;

		//cur是第pos个孩子结点
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

	//cur元素为空，向parent借元素
	//--parent->_num
	void _lent(Node* cur, Node* parent)
	{
		//cur是parent的第几个孩子
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


