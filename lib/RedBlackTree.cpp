#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

template <class GenType> 
class RedBlackTree;

//enum Colour { RED, BLACK };

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
		int size(TreeNode<GenType> *leaf);
		void clear(TreeNode<GenType> *leaf);
		
		TreeNode<GenType>* rightRotate(TreeNode<GenType> *node);
		TreeNode<GenType>* leftRotate(TreeNode<GenType> *node);
		bool isRed(TreeNode<GenType> *node);
		
		TreeNode<GenType>* flipColors(TreeNode<GenType> *node);
		
		TreeNode<GenType>* insert(TreeNode<GenType> *leaf, GenType data);
		
		void inOrder(TreeNode<GenType> *leaf);
		void preOrder(TreeNode<GenType> *leaf);
		void postOrder(TreeNode<GenType> *leaf);
		
	public:
		RedBlackTree();
		~RedBlackTree();
		bool isEmpty();
		int size();
		void clear();
		
		void insert(GenType data);
		
		void inOrder();
		void preOrder();
		void postOrder();
};

template <class GenType>
RedBlackTree<GenType>::RedBlackTree()
{
	root = NULL;
}

template <class GenType>
RedBlackTree<GenType>::~RedBlackTree()
{
	clear();
}

template <class GenType> 
bool RedBlackTree<GenType>::isEmpty()
{
	return root == NULL;
}

template <class GenType> 
int RedBlackTree<GenType>::size(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
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
	if(leaf != NULL)
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
TreeNode<GenType>* RedBlackTree<GenType>::rightRotate(TreeNode<GenType>* node)
{
	TreeNode<GenType> *newNode = node->left;

	newNode->parent = node->parent;
	node->left = node->left->right;

	newNode->right = node;
	
	newNode->color = node->color;
	node->color = RED;
	node->parent = newNode;
	
	//node->height = max(height(node->left), height(node->right)) + 1;
	//newNode->height = max(height(newNode->left), height(newNode->right)) + 1;
	
	return newNode;
}

template <class GenType>
TreeNode<GenType>* RedBlackTree<GenType>::leftRotate(TreeNode<GenType>* node)
{
	TreeNode<GenType> *newNode = node->right;
	
	newNode->parent = node->parent; //change the parent of newnode
	node->right = node->right->left;
	
	newNode->left = node;
	
	newNode->color = node->color;
	node->color = RED;
	node->parent = newNode;
	
	//node->height = max(height(node->left), height(node->right)) + 1;
	//newNode->height = max(height(newNode->left), height(newNode->right)) + 1;

	return newNode;
}

template <class GenType>
bool RedBlackTree<GenType>::isRed(TreeNode<GenType> *node)
{
	if(node == NULL)
	{
		return false;
	}
	else
	{
		return node->color == RED;
	}
}

template <class GenType>
TreeNode<GenType>* RedBlackTree<GenType>::flipColors(TreeNode<GenType> *node)
{
	/*
	node->color = ! node->color;
	node->left->color = ! node->left->color;
	node->right->color = ! node->right->color;
	*/
	node->color = RED;
	node->left->color = BLACK;
	node->right->color = BLACK;
	return node;
}

template <class GenType> 
void RedBlackTree<GenType>::insert(GenType data)
{	
	if(isEmpty())
	{
		TreeNode<GenType> *temp = new TreeNode<GenType>;
	
		temp->item = data;
		temp->left = NULL;
		temp->right = NULL;
		temp->color = BLACK;
		root = temp;
		root->parent = NULL;
	}
	else
	{
		root = insert(root,data);
	}
}

template <class GenType> 
TreeNode<GenType>* RedBlackTree<GenType>::insert(TreeNode<GenType> *leaf, GenType data)
{
	if(data < leaf->item)
	{		
		if(leaf->left == NULL)
		{
		    TreeNode<GenType> *temp = new TreeNode<GenType>;
			temp->item = data;
			temp->left = temp->right = NULL;
			temp->color = RED;
			temp->parent = leaf;
			leaf->left = temp;
		}
		else
		{
			leaf->left = insert(leaf->left, data);
		}		
	}
	else if(data > leaf->item) //not handling duplicates
	{	
		if(leaf->right == NULL)
		{
			TreeNode<GenType> *temp = new TreeNode<GenType>;
			temp->item = data;
			temp->left = temp->right = NULL;
			temp->color = RED;
			temp->parent = leaf;
			leaf->right = temp;
		}
		else
		{
			leaf->right = insert(leaf->right, data);
		}
	}
	
	if(isRed(leaf->right) && !isRed(leaf->left))
	{
		cout<<" Left Rotate "<<leaf->item<<endl;
		leaf = leftRotate(leaf);
	}
	if(isRed(leaf->left) && isRed(leaf->left->left))
	{
		cout<<" Right Rotate "<<leaf->item<<endl;
		leaf = rightRotate(leaf);
	}
	if(isRed(leaf->left) && isRed(leaf->right))
	{
		cout<<" Flip Colors "<<leaf->item<<" Color : "<<leaf->color<<endl;
		flipColors(leaf);
	}
	
	return leaf;
}

template <class GenType>
void RedBlackTree<GenType>::inOrder(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
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
	if(leaf == NULL)
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
	preOrder(root);
	cout<<endl;
	//cout<<root->height<<endl;
	
}

template <class GenType>
void RedBlackTree<GenType>::postOrder(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
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
	RedBlackTree<int> t;
	t.insert(19);
	t.insert(5);
	t.insert(1);
	t.insert(11);
	
	t.preOrder();
	t.inOrder();
	return 0;
}
