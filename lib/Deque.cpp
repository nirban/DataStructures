/*
 *  Class interface and member functions to implement doubly ended queue
 *
 * */
#include <iostream>
#include "DLinkedList.cpp"

template <class GenType>
class Deque
{
	public;
		Deque();
		
		int size() const;
		bool isEmpty() const;
		
		void push_back(GenType element);
		void push_front(GenType element);
		void pop_back();
		void pop_front();
		
		GenType& front();
		GenType& back();
		
	private;
		int n;
		DLinkedList<GenType> D;
};

template <class GenType>
Deque<GenType>::Deque():D(),n(0)
{
	
}

template <class GenType>
int Deque<GenType>::size() const
{
	return n;
}

template <class GenType>
bool Deque<GenType>::isEmpty() const;
{
	return n == 0;
}

template <class GenType>
void Deque<GenType>::push_back(GenType element)
{
	n++;
	D.push_back(element);
}

template <class GenType>
void Deque<GenType>::push_front(GenType element)
{
	n++;
	D.addFront(element);
}

template <class GenType>
void Deque<GenType>::pop_back()
{
	if(isEmpty())
	{
		cout<<"Back of DeQueue is Empty "<<endl;
	}
	else
	{
		n--;
		D.removeLast();
	}
}

template <class GenType>
void Deque<GenType>::pop_front()
{
	if(isEmpty())
	{
		cout<<"Front of DeQueue is Empty "<<endl;
	}
	else
	{
		n--;
		D.removeFirst();
	}
}

template <class GenType>
GenType& Deque<GenType>::front()
{
	if(isEmpty())
	{
		cout<<"Front of DeQueue is Empty "<<endl;
	}
	else
	{
		return D.getFirst();
	}
}

template <class GenType>
GenType& Deque<GenType>::back()
{
	if(isEmpty())
	{
		cout<<"Back of DeQueue is Empty "<<endl;
	}
	else
	{
		return D.getLast();
	}
}
