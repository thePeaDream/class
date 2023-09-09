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
	//����Ľ��
	template<class T>
	struct ListNode
	{
		//���ĳ�Ա����
		typedef ListNode<T> Node;
		T _date;
		Node* _next;
		Node* _pre;

		//Ĭ�Ϲ��캯��
		ListNode(const T& date = T( ) )
			:_date(date)
			,_next(nullptr)
			,_pre(nullptr)
		{}
	};


	//����������
	//const����������ͨ������������const������������*����->�޸����ݣ�����ͨ���������ԣ�
	// ����*ֻ�з���ֵT&��const T&��ͬ��->ֻ�з���ֵT*��const T*��ͬ
	//�ѷ���ֵ��Ϊģ��������룬������list��ͨ����T&����const T&ȷ������������
	
	template<class T,class Reference, class Pointer>
	struct ListIterator
	{
		typedef ListNode<T> Node;                                    //�򻯽������
		typedef ListIterator<T,Reference, Pointer> Iterator; //�򻯵���������
		
		Node* _node;


		ListIterator(Node* x)
			:_node(x)
		{}

		//Ҫ����!= ++ �� *���ڵ�����������������Щ�����
		bool operator!=(const Iterator& it)
		{
			//�ȽϽ���ַ�Ƿ���ͬ
			return this->_node != it._node;
		}

		//ǰ��++
		//�õ�ǰ������ָ����һ�����
		Iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		//����++
		//�õ�ǰ������ָ����һ����㣬����++֮ǰ�ĵ�����
		Iterator operator++(int)
		{
			Iterator ret = *this;
			_node = _node->_next;
			return ret;
		}

		//ǰ��--
		//�õ�ǰ������ָ��ǰһ�����
		Iterator& operator--()
		{
			_node = _node->_pre;
			return *this;
		}

		//����--
		//�õ�ǰ������ָ��ǰһ����㣬����--֮ǰ�ĵ�����
		Iterator operator--(int)
		{
			Iterator tmp = *this;
			_node = _node->_pre;
			return tmp;
		}

		//�Ե��������ͽ���*�����ص��ǽ�㱣�����������
		Reference operator*()
		{
			return  _node->_date;
		}

		//it->����it.operator->()
		//�������ݵ�ָ�룬����T�ǽṹ�����͵����
		Pointer operator->()
		{
			return &( operator*() );
		}
	};


	//����
	template<class T>
	class list
	{
	private:
		typedef ListNode<T> Node;
		Node* _head;//��ͷ˫��ѭ�������ͷ���ָ��

	public:
		//���캯������ʼ��ͷ��㣬����next��preָ���Լ�
		list()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_pre = _head;
		}

		//��һ�ε�������������������
		template<class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			//������ģ�壬������vector��list��string������������
			_head = new Node;
			_head->_next = _head;
			_head->_pre = _head;

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		
		//��������
		list(const list<T>& lt)
		{
			_head = new Node;
			_head->_next = _head;
			_head->_pre = _head;

			list<T> tmp(lt.begin(), lt.end());

			//ֱ�ӽ����ڱ�λͷ���
			std::swap(tmp._head, _head);
		}

		//=���������
		list<T>& operator=(list<T> lt)
		{
			//�����ڱ�λͷ���
			std::swap(lt._head, _head);
			return *this;
		}

		//��������
		~list()
		{
			clear();
			delete _head;
		}

		//��ս�㣬ͷ������
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
		
		//const����������ͨ����������ͬһ�����������ͣ�����ͬ�ķ���ֵ��Ϊģ���������
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
			//�����½��
			Node* newNode = new Node;

			//�ҵ�β��
			Node* tail = _head->_pre;

			//β����
			tail->_next = newNode;

			//�޸��²�����ĳ�Ա
			newNode->_pre = tail;
			newNode->_next = _head;
			newNode->_date = val;

			//�޸�β��
			_head->_pre = newNode;
		}*/
		void push_back(const T& val)
		{
			insert(end(), val);
		}

		//ɾ��posλ�õĽ�㣬����ɾ��������һ�����λ��
		iterator erase(iterator pos)
		{
			assert(pos != _head);
			Node* cur = pos._node;//��ǰҪɾ���Ľ��
			Node* pre = cur->_pre;
			Node* next = cur->_next;
			
			//����pre��next
			pre->_next = next;
			next->_pre = pre;
			
			//ɾ�����
			delete cur;

			return iterator(next);
		}

		//��posλ��ǰ����val�������²�����ĵ�����λ��
		iterator insert(iterator pos, const T& val)
		{
			Node* newNode = new Node(val);
			Node* next = pos._node;
			Node* pre = next->_pre;

			//����newNode��pre
			newNode->_pre = pre;
			pre->_next = newNode;

			//����newNode��next
			newNode->_next = next;
			next->_pre = newNode;

			return iterator(newNode);
		}

	

	};
}