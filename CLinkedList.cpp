#include <iostream>

using namespace std;

template <class GenType>
class CLinkedList;

//a templete class to implement Circular Linked List
template <class GenType> //friend class SLinkedList<GenType>
class Node
{
	private:
		GenType item;
		Node<GenType> *next;
		friend class CLinkedList<GenType>;
};

//singly linked List ADT class
template <class GenType>
class CLinkedList
{
	private:
		Node<GenType> *head;
	
	public:
		CLinkedList();
		~CLinkedList();
		
		bool isEmpty() const;
		int size();
		
		void addFront(GenType element);
		void push_back(GenType element);
		
		GenType& getFirst();
		GenType& getLast();
		
		void removeFirst();
		void removeLast();	
		
		void advance();
		void clear();
		void print();
};

template <class GenType>
CLinkedList<GenType>::CLinkedList()
{
	head = NULL;
	//cout<< " SLinkedList Object created Success"<<endl;
}


template <class GenType>
CLinkedList<GenType>::~CLinkedList()
{
	while(!isEmpty())
	{
		removeFirst();
	}
}


template <class GenType>
void CLinkedList<GenType>::advance()
{
	head = head->next;
}

template <class GenType>
bool CLinkedList<GenType>::isEmpty() const
{
	return head == NULL;
}

template <class GenType>
GenType& CLinkedList<GenType>::getFirst()
{
	return head->next->item;
}

template <class GenType>
GenType& CLinkedList<GenType>::getLast()
{
	return head->item;
}

template <class GenType>
int CLinkedList<GenType>::size()
{
	static int count = 0;
	Node<GenType> *temp = new Node<GenType>;
	temp = head;
	if(head == NULL)
	{
		return count;
	}
	else
	{
		while(temp != head)
		{
			count++;
			temp = temp->next;
		}
	}
	//delete temp;	
	return count;
}

template <class GenType>
void CLinkedList<GenType>::addFront(GenType element)
{
	Node<GenType> *temp = new Node<GenType>;
	
	temp->item = element;
	
	if(head == NULL)
	{
		temp->next = temp;
		head = temp;
	}
	else
	{
		temp->next = head->next;
		head->next = temp;
	}
}
	
template <class GenType>
void CLinkedList<GenType>::removeFirst()
{
	Node<GenType> *temp = head->next;

	if(temp == head)
	{
		head = NULL;
	}
	else
	{
		head->next = temp->next;
	}
	
	delete temp;
}
