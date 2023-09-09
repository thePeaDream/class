#pragma once
#include <iostream>
#include<list>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include<vector>
#include<assert.h>
#include "ReverseIterator.hpp"
namespace yh
{
	//链表的结点
	template<class T>
	struct ListNode
	{
		//结点的成员变量
		typedef ListNode<T> Node;
		T _date;
		Node* _next;
		Node* _pre;

		//默认构造函数
		ListNode(const T& date = T( ) )
			:_date(date)
			,_next(nullptr)
			,_pre(nullptr)
		{}
	};


	//迭代器类型
	//const迭代器和普通迭代器区别是const迭代器不能用*或者->修改数据，但普通迭代器可以，
	// 所以*只有返回值T&和const T&不同，->只有返回值T*和const T*不同
	//把返回值作为模板参数传入，可以在list中通过传T&或者const T&确定迭代器类型
	
	template<class T,class Reference, class Pointer>
	struct ListIterator
	{
		typedef ListNode<T> Node;                                    //简化结点类型
		typedef ListIterator<T,Reference, Pointer> Iterator; //简化迭代器类型
		
		Node* _node;


		ListIterator(Node* x)
			:_node(x)
		{}

		//要控制!= ++ 和 *，在迭代器类型里重载这些运算符
		bool operator!=(const Iterator& it)
		{
			//比较结点地址是否相同
			return this->_node != it._node;
		}

		//前置++
		//让当前迭代器指向下一个结点
		Iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//后置++
		//让当前迭代器指向下一个结点，返回++之前的迭代器
		Iterator operator++(int)
		{
			Iterator ret = *this;
			_node = _node->_next;
			return ret;
		}

		//前置--
		//让当前迭代器指向前一个结点
		Iterator& operator--()
		{
			_node = _node->_pre;
			return *this;
		}

		//后置--
		//让当前迭代器指向前一个结点，返回--之前的迭代器
		Iterator operator--(int)
		{
			Iterator tmp = *this;
			_node = _node->_pre;
			return tmp;
		}

		//对迭代器类型进行*，返回的是结点保存的数据引用
		Reference operator*()
		{
			return  _node->_date;
		}

		//it->调用it.operator->()
		//返回数据的指针，用于T是结构体类型的情况
		Pointer operator->()
		{
			return &( operator*() );
		}
	};


	//链表
	template<class T>
	class list
	{
	private:
		typedef ListNode<T> Node;
		Node* _head;//带头双向循环链表的头结点指针

	public:
		//构造函数，初始化头结点，并让next和pre指向自己
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_pre = _head;
		}

		//用一段迭代器区间来构造链表
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			//由于是模板，可以用vector、list、string等区间来构造
			_head = new Node;
			_head->_next = _head;
			_head->_pre = _head;

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		
		//拷贝构造
		list(const list<T>& lt)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_pre = _head;

			list<T> tmp(lt.begin(), lt.end());

			//直接交换哨兵位头结点
			std::swap(tmp._head, _head);
		}

		//=运算符重载
		list<T>& operator=(list<T> lt)
		{
			//交换哨兵位头结点
			std::swap(lt._head, _head);
			return *this;
		}

		//析构函数
		~list()
		{
			clear();
			delete _head;
		}

		//清空结点，头结点除外
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
		
		//const迭代器和普通迭代器复用同一个迭代器类型，将不同的返回值作为模板参数传入
		typedef ListIterator<T,T&, T*> iterator;
		typedef ListIterator<T, const T&, const T*> const_iterator;
		typedef Reverse_Iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_Iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		iterator begin()
		{
			return iterator(_head->_next);
		}
		
		const_iterator begin()const
		{
			return const_iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator end()const
		{
			return const_iterator(_head);
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin()const
		{
			return const_reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend()const
		{
			return const_reverse_iterator(begin());
		}

	

		/*void push_back(const T& val)
		{
			//创建新结点
			Node* newNode = new Node;

			//找到尾部
			Node* tail = _head->_pre;

			//尾插结点
			tail->_next = newNode;

			//修改新插入结点的成员
			newNode->_pre = tail;
			newNode->_next = _head;
			newNode->_date = val;

			//修改尾部
			_head->_pre = newNode;
		}*/
		void push_back(const T& val)
		{
			insert(end(), val);
		}

		//删除pos位置的结点，返回删除结点的下一个结点位置
		iterator erase(iterator pos)
		{
			assert(pos != _head);
			Node* cur = pos._node;//当前要删除的结点
			Node* pre = cur->_pre;
			Node* next = cur->_next;
			
			//链接pre和next
			pre->_next = next;
			next->_pre = pre;
			
			//删除结点
			delete cur;

			return iterator(next);
		}

		//在pos位置前插入val，返回新插入结点的迭代器位置
		iterator insert(iterator pos, const T& val)
		{
			Node* newNode = new Node(val);
			Node* next = pos._node;
			Node* pre = next->_pre;

			//链接newNode和pre
			newNode->_pre = pre;
			pre->_next = newNode;

			//链接newNode和next
			newNode->_next = next;
			next->_pre = newNode;

			return iterator(newNode);
		}

	

	};
}