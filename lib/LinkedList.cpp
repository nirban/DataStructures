#include <iostream>
#include <cassert>

using namespace std;

template <class GenType>
class SLinkedList;

template <class GenType>
class Iterator;

//a templete class to implement Singly Linked List
template <class GenType> //friend class SLinkedList<GenType>
class Node
{
	private:
		GenType item;
		Node<GenType> *next;
		friend class SLinkedList<GenType>;
		friend class Iterator<GenType>;
};

template <class GenType>
class Iterator
{	

	private:
		Node<GenType> *pointer;
		Iterator(Node<GenType> *p):pointer(p) {}
	public:
		friend class SLinkedList<GenType>;
		GenType& operator*();		
		const Iterator<GenType>& operator++();	//prefix operation
		const Iterator<GenType>& operator++(int);	//postfix operation
		const Iterator<GenType>& operator--();	
		bool operator!=(const Iterator<GenType>& other) const;
};

template <class GenType>
GenType& Iterator<GenType>::operator*()
{
	return pointer->item;
}

template <class GenType>
const  Iterator<GenType>& Iterator<GenType>::operator++()
{
	assert(pointer != NULL);
	pointer = pointer->next;
	return *this;
}

template <class GenType>
const  Iterator<GenType>& Iterator<GenType>::operator++(int)
{
	assert(pointer != NULL);
	pointer = pointer->next;
	return *this;
}


template <class GenType>
bool Iterator<GenType>::operator!=(const Iterator<GenType>& other) const
{
	return this->pointer != other.pointer;
}


//singly linked List ADT class
template <class GenType>
class SLinkedList
{
	private:
		Node<GenType> *head;
	
	public:
		typedef Iterator<GenType> Iter;
		
		SLinkedList();
		~SLinkedList();
		
		bool isEmpty() const;
		int size();
		
		Iter begin(){ return Iterator<GenType>(head); }
		Iter end(){ return Iterator<GenType>(NULL);  }
		
		void addFront(GenType element);
		void push_back(GenType element);
		
		GenType& getFirst();
		GenType& getLast();
		
		void removeFirst();
		void removeLast();	
		
		void clear();
		void print();
};

template <class GenType>
SLinkedList<GenType>::SLinkedList()
{
	head = NULL;
	//cout<< " SLinkedList Object created Success"<<endl;
}

template <class GenType>
SLinkedList<GenType>::~SLinkedList()
{
	Node<GenType> *temp;
	while(head != NULL)
	{
		temp = head->next;
		delete head;
		head = temp;
	}
}

template <class GenType>
bool SLinkedList<GenType>::isEmpty() const
{
	return head == NULL;
}

template <class GenType>
int SLinkedList<GenType>::size()
{
	static int count = 0;
	Node<GenType> *temp = new Node<GenType>;
	temp = head;
	while(temp->next != NULL)
	{
		count++;
	}
	//delete temp;	
	return count;
}

template <class GenType>
void SLinkedList<GenType>::addFront(GenType element)
{
	Node<GenType> *temp = new Node<GenType>;
	
	temp->item = element;
	temp->next = head;
	head = temp;
	//cout<<element<<" Inserted"<<endl;
	//delete temp;
}

template <class GenType>
void SLinkedList<GenType>::push_back(GenType element)
{
	//cout<< " test"<<endl;
	Node<GenType> *temp = new Node<GenType>;
	Node<GenType> *newN = head;
	
	temp->item = element;
	temp->next = NULL;
	
	if(isEmpty())
	{
		//cout<<element<<" Inserted"<<endl;
		head = temp;
	}
	else
	{
		//cout<<element <<" test"<<endl;
		while(newN->next != NULL)
		{
			newN = newN->next;
		}
		newN->next = temp;
	}
}

template <class GenType>
void SLinkedList<GenType>::removeFirst()
{
	Node<GenType> *temp = head;
	head = temp->next;
	delete temp;
}

template <class GenType>
void SLinkedList<GenType>::removeLast()
{
	Node<GenType> *temp = head;
	Node<GenType> *curr;
	
	if(head != NULL)
	{
		while(temp->next != NULL)
		{
			curr = temp;
			temp = temp->next;
		}
		curr->next= NULL;
		delete temp;
	}
}

template <class GenType>
GenType& SLinkedList<GenType>::getFirst()
{
	Node<GenType> *temp = head;
	return temp->item;
}

template <class GenType>
GenType& SLinkedList<GenType>::getLast()
{
	Node<GenType> *temp = head;
	while(temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp->item;
}

template <class GenType>
void SLinkedList<GenType>::print()
{
	Node<GenType> *temp = new Node<GenType>;
	temp = head;
	while(temp!=NULL)
	{
		cout<<temp->item<<endl;
		temp = temp->next;
	}
	//delete temp;
}

/*
int main()
{
	SLinkedList<int> a;
	//a.push_back(5);
	//a.push_back(1);
	a.addFront(7);
	a.addFront(4);
	a.push_back(5);
	a.push_back(15);
	a.push_back(73);
	a.removeLast();
	a.print();
	
	cout<<" Last Element "<<a.getLast() <<endl; 
	cout<<" first Element "<<a.getFirst() <<endl;
	Iterator<int> it = a.begin();
	
	for(it = a.begin(); it != a.end(); it++)
	{
		cout<<*it<<endl;
	}
	
	return 0;
}
*/
