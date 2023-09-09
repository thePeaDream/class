#pragma once
//��һ�����������ͣ����췴�������
//�����������һ��������������
//�ṩlist�ĵ����������������list�ķ��������
//�ṩvector�ĵ����������������vector�ķ��������
namespace yh
{
	template<class Iterator, class Ref, class Ptr>
	class Reverse_Iterator
	{
	private:
		//��Ա����
		Iterator _it;
		typedef Reverse_Iterator<Iterator,Ref, Ptr> RIterator;
	public:
		Reverse_Iterator(Iterator it)
			:_it(it)
		{}

		RIterator& operator++()
		{
			//���������++����--��װ��_it
			--_it;
			return *this;
		}

		RIterator& operator--()
		{
			//���������--����++��װ��_it
			++_it;
			return *this;
		}

		Ref operator*()const
		{
			//ʵ�� �����������rbegin() ���� �����������end()
			// �����������rend() ���� �����������begin()
			// �����������ָ��λ�� ��ʵ�� ǰһ��Ԫ��
			Iterator tmp = _it;
			--tmp;
			return *tmp;
		}

		Ptr operator->()
		{
			return _it.operator->();
		}

		bool operator!=(const RIterator& rit)//��Ϊconst��Ա�����ᱨ��û���ҵ����ܡ�const Iterator�����͵���������������(��û�пɽ��ܵ�ת��)
		{
			return _it != rit._it;
		}
		bool operator==(const RIterator& rit)
		{
			return _it == rit._it;
		}

	};
}