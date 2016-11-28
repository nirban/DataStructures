#include <iostream>
#include "SLinkedList.cpp"

using namespace std;

class RuntimeException
{
	private:
		string errorMsg;
	public:
		RuntimeException(const string& err)
		{
			errorMsg = err;
		}
		string getMessage() const
		{
			return errorMsg;
		}
};

class StackEmpty: public RuntimeException
{
	public:
		StackEmpty(const string& err):RuntimeException(err){}
};

template <class GenType>
class Stack
{
	public:
		Stack();
		~Stack();
		int size() const;
		GenType& top();  //  throw(StackEmpty);
		void push(GenType element);
		void pop();  // throw(StackEmpty);
		bool isEmpty();
	private:
		int n;
		SLinkedList<GenType> S;
};

template <class GenType>
Stack<GenType>::Stack():S(),n(0)
{
	
}

template <class GenType>
Stack<GenType>::~Stack()
{
	
}

template <class GenType>
int Stack<GenType>::size() const
{
	return n;
}

template <class GenType>
GenType& Stack<GenType>::top() //throw(StackEmpty)
{	
	if(isEmpty())
	{
		//throw StackEmpty("Top of Empty Stack");
		cout<<"Top of Empty Stack"<<endl;
	}
	else
	{
		return S.getFirst();
	}
}

template <class GenType>
void Stack<GenType>::push(GenType element)
{
	n++;
	S.addFront(element);
}

template <class GenType>
void Stack<GenType>::pop() //throw(StackEmpty)
{
	if(isEmpty())
	{
		//throw StackEmpty("Pop of Empty Stack");
		cout<<"Pop of Empty Stack"<<endl;
	}
	else
	{
		n--;
		S.removeFirst();
	}
	
}

template <class GenType>
bool Stack<GenType>::isEmpty()
{
	return n == 0;
}

int main()
{
	Stack<int> a;
	a.push(7);
	a.push(9);
	a.push(4);
	a.push(5);
	cout<<"Stack Size "<<a.size()<<endl;
	cout<<" BOOL Value "<<a.isEmpty()<<endl;
	cout<<"Stack Top "<<a.top()<<endl;
	
	while(!a.isEmpty())
	{
		cout<<a.top()<<endl;
		a.pop();
	}
	return 0;
}
