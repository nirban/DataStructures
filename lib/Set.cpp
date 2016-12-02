#include <iostream>
#include "AVLTree.cpp"

template <class GenType>
class Set
{
	private;
		AVLTree<GenType> Tree;
	public:
		Set();
		bool isEmpty(){ return Tree.isEmpty();}
		void insert(GenType val){ Tree.insert(val);}
		void remove(GenType val){Tree.remove(val);}
		void clear(){Tree.clear();}
		bool contains(GenType val){return Tree.isMember(val);}
		bool equals(Set<GenType> S){ return S.Tree == Tree ; }
		
		
};

