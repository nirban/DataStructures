#include <iostream>
#include "CLinkedList.cpp"

using namespace std;

template <class GenType>
class Queue
{
	public:
		Queue();
		
		void enqueue(GenType element);
		void dequeue();
		GenType& front();
		bool isEmpty();
		int size();
	
	private:
		int n;
		CLinkedList<GenType> C;
};

template <class GenType>
Queue<GenType>::Queue():C(),n(0)
{
	
}

template <class GenType>
bool Queue<GenType>::isEmpty()
{
	return n==0;
}

template <class GenType>
int Queue<GenType>::size()
{
	return n;
}

template <class GenType>
void Queue<GenType>::enqueue(GenType element)
{
	n++;
	C.addFront(element);
	C.advance();
}

template <class GenType>
void Queue<GenType>::dequeue()
{
	if(isEmpty())
	{
		cout<<"Queue is Empty "<<endl;
	}
	else
	{
		n--;
		C.removeFirst();
	}
}

template <class GenType>
GenType& Queue<GenType>::front()
{
	if(isEmpty())
	{
		cout<<"Front Queue is Empty "<<endl;
	}
	else
	{
		return C.getFirst();
	}
}

int main()
{
	Queue<int> q;
	
	q.enqueue(7);
	q.enqueue(9);
	q.enqueue(4);
	q.enqueue(5);
	
	cout<<"Queue Size "<<q.size()<<endl;
	cout<<" BOOL Value "<<q.isEmpty()<<endl;
	cout<<"Queue Top "<<q.front()<<endl;
	
	while(!q.isEmpty())
	{
		cout<<q.front()<<endl;
		q.dequeue();
	}
}
