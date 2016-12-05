#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

template <class GenType> 
class RedBlackTree;

//typedef enum Colour { RED, BLACK };

const bool RED = true;
const bool BLACK = false;

template <class GenType> 
class TreeNode
{
	public:
		GenType item;
		int height;
		TreeNode<GenType> *left;
		TreeNode<GenType> *right;
		TreeNode<GenType> *parent;
		bool color;
		friend class RedBlackTree<GenType>;
};

template <class GenType>
class RedBlackTree
{	
	private:
		TreeNode<GenType> *root;
		TreeNode<GenType> *NIL;
		
		int size(TreeNode<GenType> *leaf);
		void clear(TreeNode<GenType> *leaf);
		TreeNode<GenType>* search(TreeNode<GenType> *leaf, GenType val);
		void rightRotate(TreeNode<GenType> *node);
		void leftRotate(TreeNode<GenType> *node);
		void transplant(TreeNode<GenType> *u, TreeNode<GenType> *v);
		void insertFixUp(TreeNode<GenType> *node);
		void removeFixUp(TreeNode<GenType> *node);
		GenType& findMin(TreeNode<GenType> *leaf);
		GenType& findMax(TreeNode<GenType> *leaf);
		
		void inOrder(TreeNode<GenType> *leaf);
		void preOrder(TreeNode<GenType> *leaf);
		void postOrder(TreeNode<GenType> *leaf);
		
	public:
		RedBlackTree();
		~RedBlackTree();
		bool isEmpty();
		int size();
		void clear();
		TreeNode<GenType>* search(GenType val);
		void insert(GenType data);
		void remove(GenType data);
		GenType& findMin();
		GenType& findMax();
		
		void inOrder();
		void preOrder();
		void postOrder();
};

template <class GenType>
RedBlackTree<GenType>::RedBlackTree()
{
	root = NULL;
	
	NIL = new TreeNode<GenType>;
	NIL->color = BLACK;
	NIL->left = NIL->right = NIL->parent = NIL;
	
	root = NIL;
	root->color = BLACK;
}

template <class GenType>
RedBlackTree<GenType>::~RedBlackTree()
{
	clear();
}

template <class GenType> 
bool RedBlackTree<GenType>::isEmpty()
{
	return root == NIL;
}

template <class GenType> 
int RedBlackTree<GenType>::size(TreeNode<GenType> *leaf)
{
	if(leaf == NIL)
	{
		return 0;
	}
	else
	{
		return 1 + size(leaf->left) + size(leaf->right);
	} 
}

template <class GenType> 
int RedBlackTree<GenType>::size()
{
	return size(root);
}

template <class GenType>
void RedBlackTree<GenType>::clear(TreeNode<GenType> *leaf)
{
	if(leaf != NIL)
	{
		clear(leaf->left);
		clear(leaf->right);
		delete leaf;
	}
}

template <class GenType>
void RedBlackTree<GenType>::clear()
{
	clear(root);
}


template <class GenType> 
GenType& RedBlackTree<GenType>::findMin(TreeNode<GenType> *leaf)
{
	if(leaf == NIL)
	{
		
	}
	if(leaf->left == NIL)
	{
		return leaf->item;
	}
	else
	{
		return findMin(leaf->left);
	}
}
 
template <class GenType> 
GenType& RedBlackTree<GenType>::findMin()
{
	return findMin(root);
}

template <class GenType> 
GenType& RedBlackTree<GenType>::findMax(TreeNode<GenType> *leaf)
{
	if(leaf == NIL)
	{
		
	}
	if(leaf->right == NIL)
	{
		return leaf->item;
	}
	else
	{
		return findMax(leaf->right);
	}
}
 
template <class GenType> 
GenType& RedBlackTree<GenType>::findMax()
{
	return findMax(root);
}


template <class GenType> 
TreeNode<GenType>* RedBlackTree<GenType>::search(TreeNode<GenType> *leaf, GenType val)
{
	if(leaf == NIL)
	{
		return leaf;
	}
	else if(leaf->item == val)
	{
		return leaf;
	}
	else if( val > leaf->item)
	{
		if(leaf->right == NIL)
		{
			return leaf;
		}
		else
		{
			return search(leaf->right, val);
		}
	}
	else if( val < leaf->item)
	{
		if(leaf->left == NIL)
		{
			return leaf;
		}
		else
		{
			return search(leaf->left, val);
		}
	}
}

template <class GenType> 
TreeNode<GenType>* RedBlackTree<GenType>::search(GenType val)
{
	return search(root,val);
}

template <class GenType>
void RedBlackTree<GenType>::transplant(TreeNode<GenType> *u, TreeNode<GenType> *v)
{
	if(u->parent == NIL)
	{
		root = v;
	}
	else if(u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

template <class GenType>
void RedBlackTree<GenType>::rightRotate(TreeNode<GenType>* node)
{
	TreeNode<GenType> *newNode = node->left;
	node->left = newNode->right;
	
	if(newNode->right != NIL)
	{
		newNode->right->parent = node;
	}
	newNode->parent = node->parent;
	
	if(node->parent == NIL)
	{
		root = newNode;
	}
	else if(node == node->parent->right)
	{
		node->parent->right = newNode;
	}
	else
	{
		node->parent->left = newNode;
	}
	
	newNode->right = node;
	node->parent = newNode;

	return;
}

template <class GenType>
void RedBlackTree<GenType>::leftRotate(TreeNode<GenType>* node)
{
	TreeNode<GenType> *newNode = node->right;
	node->right = newNode->left;
	
	if(newNode->left != NIL)
	{
		newNode->left->parent = node;
	}
	newNode->parent = node->parent;
	
	if(node->parent == NIL)
	{
		root = newNode;
	}
	else if(node == node->parent->left)
	{
		node->parent->left = newNode;
	}
	else
	{
		node->parent->right = newNode;
	}
	
	newNode->left = node;
	node->parent = newNode;

	return;
}

template <class GenType> 
void RedBlackTree<GenType>::insert(GenType data)
{	
	TreeNode<GenType> *z = new TreeNode<GenType>;
	TreeNode<GenType> *x = this->root;
	TreeNode<GenType> *y =this->NIL;
	
	z->item = data;
	while(x != NIL)
	{
		y = x;
		
		if(z->item < x->item)
		{
			x = x->left;
		}
		else if(z->item > x->item)
		{
			x = x->right;
		}
	}
	
	z->parent = y;
	
	if(y == NIL)
	{
		this->root = z;
	}
	else if(z->item < y->item)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	z->left = z->right = NIL;
	z->color = RED;
	
	//cout<<data<<" Inserted "<<endl;
	
	insertFixUp(z);
}

template <class GenType> 
void RedBlackTree<GenType>::insertFixUp(TreeNode<GenType> *node)
{
	while(node->parent->color == RED)
	{
		if(node->parent == node->parent->parent->left)
		{
			TreeNode<GenType> *y = node->parent->parent->right;
			if(y->color == RED)
			{
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else 
			{
				if(node == node->parent->right)
				{
					node = node->parent;
					leftRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				rightRotate(node->parent->parent);
			}
		}
		else
		{
			TreeNode<GenType> *y = node->parent->parent->left;
			if(y->color == RED)
			{
				node->parent->color = BLACK;
				y->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else 
			{
				if(node == node->parent->left)
				{
					node = node->parent;
					rightRotate(node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				leftRotate(node->parent->parent);
			}
		}
	}
	
	root->color = BLACK;

	return;
}

template <class GenType>
void RedBlackTree<GenType>::remove(GenType data)
{
	TreeNode<GenType> *z = search(data);
	TreeNode<GenType> *x = new TreeNode<GenType>;
	if(z->item != data)
	{
		return;
	}
	else
	{
		TreeNode<GenType> *y = z;
		bool yColor = y->color;
		
		if(z->left == NIL)
		{
			x = z->right;
			transplant(z,z->right);
			delete z;
		}
		else if( z->right == NIL)
		{
			x = z->left;
			transplant(z,z->left);
			delete z;
		}
		else
		{
			y = search(findMin(z->right));
			yColor = y->color;
			x = y->right;
			
			if(y->parent == z)
			{
				x->parent = y;
			}
			else
			{
				transplant(y,y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z,y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
			delete z;
		}
		
		if(yColor == BLACK)
		{
			removeFixUp(x);
		}
		
	}
}

template <class GenType> 
void RedBlackTree<GenType>::removeFixUp(TreeNode<GenType> *node)
{
	while(node != root && node->color == BLACK)
	{
		if(node == node->parent->left)
		{
			TreeNode<GenType> *w = node->parent->right;
			if(w->color == RED)
			{
				w->color = BLACK;
				node->parent->color = RED;
				leftRotate(node->parent);
				w = node->parent->right;
			}
			if(w->left->color == BLACK && w->right->color == BLACK)
			{
				w->color = RED;
				node = node->parent;
			}
			else 
			{
				if(w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = node->parent->right;
				}
				w->color = node->parent->color;
				node->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(node->parent);
				node = root;
			}			
		}
		else
		{
			TreeNode<GenType> *w = node->parent->left;
			if(w->color == RED)
			{
				w->color = BLACK;
				node->parent->color = RED;
				rightRotate(node->parent);
				w = node->parent->left;
			}
			if(w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				node = node->parent;
			}
			else 
			{
				if(w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					leftRotate(w);
					w = node->parent->left;
				}
				w->color = node->parent->color;
				node->parent->color = BLACK;
				w->left->color = BLACK;
				rightRotate(node->parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}

template <class GenType>
void RedBlackTree<GenType>::inOrder(TreeNode<GenType> *leaf)
{
	if(leaf == NIL)
	{
		return;
	}
	inOrder(leaf->left);
	cout<<leaf->item<<" ";
	inOrder(leaf->right);
}

template <class GenType>
void RedBlackTree<GenType>::inOrder()
{
	inOrder(root);
}


template <class GenType>
void RedBlackTree<GenType>::preOrder(TreeNode<GenType> *leaf)
{
	if(leaf == NIL)
	{
		return;
	}
	cout<<leaf->item<<" "<<" Color : "<<leaf->color<<" "<<endl;
	preOrder(leaf->left);
	preOrder(leaf->right);
}

template <class GenType>
void RedBlackTree<GenType>::preOrder()
{
	//cout<<root->item;
	preOrder(root);
	cout<<endl;
	//cout<<root->height<<endl;
	
}

template <class GenType>
void RedBlackTree<GenType>::postOrder(TreeNode<GenType> *leaf)
{
	if(leaf == NIL)
	{
		return;
	}
	postOrder(leaf->left);
	postOrder(leaf->right);
	cout<<leaf->item<<" ";
}

template <class GenType>
void RedBlackTree<GenType>::postOrder()
{
	postOrder(root);
}

int main()
{
	//RedBlackTree<int> *t = new RedBlackTree<int>();
	RedBlackTree<int> t;
	t.insert(19);
	t.insert(5);
	t.insert(1);
	t.insert(18);
	t.insert(3);
	t.insert(8);
	t.insert(24);
	t.insert(13);
	t.insert(16);
	t.insert(12);
	
	t.preOrder();
	t.inOrder();
	
	t.remove(8);
	t.preOrder();
	t.inOrder();
	return 0;
}
