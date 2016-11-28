#include <iostream>
#include <iterator>
#include <cassert>

using namespace std;

template <class GenType>
class DLinkedList;

template <class GenType>
class Iterator;

//a templete class to implement Doubly Linked List Node
template <class GenType> 
class Node
{
	private:
		GenType item;
		Node<GenType> *next;
		Node<GenType> *prev;
		friend class DLinkedList<GenType>;
		friend class Iterator<GenType>;
};

/*
 * class to devine Iterator 
 * for the Doubly linked List
 **/
 //:public iterator<forward_iterator_tag, GenType>
template <class GenType>
class Iterator
{	

	private:
		Node<GenType> *pointer;
		Iterator(Node<GenType> *p):pointer(p) {}
	public:
		friend class DLinkedList<GenType>;
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



template <class GenType>
class DLinkedList
{	
	private:
		Node<GenType> *head;
		Node<GenType> *tail;
		
	protected:
		void add(Node<GenType> *v, GenType element);
		void remove(Node<GenType> *v);
	
	public:
		typedef Iterator<GenType> Iter;
	
		DLinkedList();
		~DLinkedList();
		
		Iter begin(){ return Iterator<GenType>(head->next); }
		Iter end(){ return Iterator<GenType>(tail);  }
		
		bool isEmpty() const;
		int size();
		
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
DLinkedList<GenType>::DLinkedList()
{
	head = new Node<GenType>;
	tail = new Node<GenType>;
	head->next = tail;
	tail->prev = head;
	//cout<< " SLinkedList Object created Success"<<endl;
}

template <class GenType>
DLinkedList<GenType>::~DLinkedList()
{
	while(!isEmpty())
	{
		removeFirst();
	}
	delete head;
	delete tail;
}

template <class GenType>
int DLinkedList<GenType>::size()
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
bool DLinkedList<GenType>::isEmpty() const
{
	return head->next == tail;
}

template <class GenType>
GenType& DLinkedList<GenType>::getFirst()
{
	return head->next->item;
}

template <class GenType>
GenType& DLinkedList<GenType>::getLast()
{
	return tail->prev->item;
}

template <class GenType>
void DLinkedList<GenType>::remove(Node<GenType> *v)
{
	Node<GenType> *pred = v->prev;
	Node<GenType> *succ = v->next;
	pred->next = succ;
	succ->prev = pred;
	delete v;
}

template <class GenType>
void DLinkedList<GenType>::removeFirst()
{
	remove(head->next);
}

template <class GenType>
void DLinkedList<GenType>::removeLast()
{
	remove(tail->prev);
}

template <class GenType>
void DLinkedList<GenType>::add(Node<GenType> *v, GenType element)
{
	Node<GenType> *temp = new Node<GenType>;
	temp->item = element;
	temp->next = v;
	temp->prev = v->prev;
	v->prev->next = v->prev = temp;
}

template <class GenType>
void DLinkedList<GenType>::addFront(GenType element)
{
	add(head->next, element);
}

template <class GenType>
void DLinkedList<GenType>::push_back(GenType element)
{
	add(tail, element);
}

template <class GenType>
void DLinkedList<GenType>::print()
{
	Node<GenType> *temp = new Node<GenType>;
	temp = head->next;
	while(temp!=NULL)
	{
		cout<<temp->item<<endl;
		temp = temp->next;
		if(temp == tail)
		{
			break;
		}
	}
	//delete temp;
}

int main()
{
	DLinkedList<int> a;
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
	//a.print();
	Iterator<int> it = a.begin();
	
	for(it = a.begin(); it != a.end(); it++)
	{
		cout<<*it<<endl;
	}
	cout<<endl;
	for(int w : a)
	{
		cout<<w<<endl;
	}
	return 0;
}
