#include <iostream>
#include <algorithm>

using namespace std;

template <class GenType> 
class BinarySearchTree;

template <class GenType> 
class TreeNode
{
	public:
		GenType item;
		TreeNode<GenType> *left;
		TreeNode<GenType> *right;
		TreeNode<GenType> *parent;
		friend class BinarySearchTree<GenType>;
};

template <class GenType> 
class BinarySearchTree
{
	private:
		TreeNode<GenType> *root;
		void insert(TreeNode<GenType> *leaf, GenType data);
		TreeNode<GenType>* search(TreeNode<GenType> *leaf, GenType val);
		bool isMember(TreeNode<GenType> *leaf, GenType val);
		int size(TreeNode<GenType> *leaf);
		
		TreeNode<GenType>* remove(TreeNode<GenType> *leaf, GenType val);
		int height(TreeNode<GenType> *leaf);
		void clear(TreeNode<GenType> *leaf);
		
		GenType& findMin(TreeNode<GenType> *leaf);
		GenType& findMax(TreeNode<GenType> *leaf);
		
		void inOrder(TreeNode<GenType> *leaf);
		void preOrder(TreeNode<GenType> *leaf);
		void postOrder(TreeNode<GenType> *leaf);
		
	public:
		BinarySearchTree();
		~BinarySearchTree();
		bool isEmpty();
		int size();
		void insert(GenType data);
		TreeNode<GenType>* search(GenType val);
		bool isMember(GenType val);
		int height();
		int depth();
		bool isRoot(GenType val);
		
		GenType& findMin();
		GenType& findMax();
		void clear();
		TreeNode<GenType>* remove(GenType val);
		
		void inOrder();
		void preOrder();
		void postOrder();
};

template <class GenType> 
BinarySearchTree<GenType>::BinarySearchTree()
{
	root = NULL;
}

template <class GenType> 
BinarySearchTree<GenType>::~BinarySearchTree()
{
	clear();
}

template <class GenType> 
bool BinarySearchTree<GenType>::isEmpty()
{
	return root == NULL;
}

template <class GenType> 
int BinarySearchTree<GenType>::size()
{
	return size(root);
}

template <class GenType> 
int BinarySearchTree<GenType>::size(TreeNode<GenType> *leaf)
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
bool BinarySearchTree<GenType>::isRoot(GenType val)
{
	TreeNode<GenType> *temp;
	
	if(isMember(val))
	{
		temp = search(val);
		if(temp->parent == NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

template <class GenType>
void BinarySearchTree<GenType>::clear(TreeNode<GenType> *leaf)
{
	if(leaf != NULL)
	{
		clear(leaf->left);
		clear(leaf->right);
		delete leaf;
	}
}

template <class GenType>
void BinarySearchTree<GenType>::clear()
{
	clear(root);
}

template <class GenType>
int BinarySearchTree<GenType>::height(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
	{
		return -1;
	}
	else
	{
		return 1 + max(height(leaf->left), height(leaf->right));
	}	
}

template <class GenType>
int BinarySearchTree<GenType>::height()
{
	return height(root);
}

template <class GenType> 
void BinarySearchTree<GenType>::insert(GenType data)
{
	TreeNode<GenType> *temp = new TreeNode<GenType>;
	
	temp->item = data;
	temp->left = NULL;
	temp->right = NULL;
		
	if(isEmpty())
	{
		root = temp;
		root->parent = NULL;
	}
	else
	{
		insert(root,data);
	}
}

template <class GenType> 
void BinarySearchTree<GenType>::insert(TreeNode<GenType> *leaf, GenType data)
{
	TreeNode<GenType> *temp = new TreeNode<GenType>;
	//TreeNode<GenType> *p = new TreeNode<GenType>;
	
	if(data < leaf->item)
	{
		if(leaf->left == NULL)
		{
			temp->item = data;
			temp->left = temp->right = NULL;
			temp->parent = leaf;
			leaf->left = temp;
		}
		else
		{
			insert(leaf->left, data);
		}
	}
	else if(data > leaf->item) //not handling duplicates
	{
		if(leaf->right == NULL)
		{
			temp->item = data;
			temp->left = temp->right = NULL;
			temp->parent = leaf;
			leaf->right = temp;
		}
		else
		{
			insert(leaf->right, data);
		}
	}
	
	return;
}

template <class GenType> 
bool BinarySearchTree<GenType>::isMember(TreeNode<GenType> *leaf, GenType val)
{
	if(leaf == NULL)
	{
		return false;
	}
	else if(leaf->item == val)
	{
		return true;
	}
	else if( val > leaf->item)
	{
		if(leaf->right == NULL)
		{
			return false;
		}
		else
		{
			return isMember(leaf->right, val);
		}
	}
	else if( val < leaf->item)
	{
		if(leaf->left == NULL)
		{
			return false;
		}
		else
		{
			return isMember(leaf->left, val);
		}
	}
}

template <class GenType> 
bool BinarySearchTree<GenType>::isMember(GenType val)
{
	return isMember(root, val);
}

template <class GenType> 
TreeNode<GenType>* BinarySearchTree<GenType>::search(TreeNode<GenType> *leaf, GenType val)
{
	if(leaf == NULL)
	{
		return leaf;
	}
	else if(leaf->item == val)
	{
		return leaf;
	}
	else if( val > leaf->item)
	{
		if(leaf->right == NULL)
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
		if(leaf->left == NULL)
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
TreeNode<GenType>* BinarySearchTree<GenType>::search(GenType val)
{
	return search(root,val);
}

template <class GenType> 
GenType& BinarySearchTree<GenType>::findMin(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
	{
		
	}
	if(leaf->left == NULL)
	{
		return leaf->item;
	}
	else
	{
		return findMin(leaf->left);
	}
}
 
template <class GenType> 
GenType& BinarySearchTree<GenType>::findMin()
{
	return findMin(root);
}

template <class GenType> 
GenType& BinarySearchTree<GenType>::findMax(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
	{
		
	}
	if(leaf->right == NULL)
	{
		return leaf->item;
	}
	else
	{
		return findMax(leaf->right);
	}
}
 
template <class GenType> 
GenType& BinarySearchTree<GenType>::findMax()
{
	return findMax(root);
}

template <class GenType> 
TreeNode<GenType>* BinarySearchTree<GenType>::remove(TreeNode<GenType> *leaf, GenType val)
{
	if(leaf == NULL)
	{
		return leaf;
	}
	else if(val < leaf->item)
	{
		leaf->left = remove(leaf->left,val);
	}
	else if(val > leaf->item)
	{
		leaf->right = remove(leaf->right,val);
	}
	else
	{
		//case 1; leaf node
		if(leaf->right == NULL && leaf->left == NULL)
		{
			delete leaf;
		}
		else if(leaf->left == NULL)  // case 2: one child
		{
			TreeNode<GenType> *temp = leaf;
			leaf = leaf->right;
			leaf->parent = temp->parent;
			delete temp;
		}
		else if(leaf->right == NULL)
		{
			TreeNode<GenType> *temp = leaf;
			leaf = leaf->left;
			leaf->parent = temp->parent;
			delete temp;
		}
		else // case 3: two child
		{
			TreeNode<GenType> *temp = search(findMin(leaf->right));
			leaf->item = temp->item;
			leaf->right = remove(leaf->right, temp->item);
		}
	}
	return leaf;	
}

template <class GenType>
TreeNode<GenType>* BinarySearchTree<GenType>::remove(GenType val)
{
	return remove(root, val);
}

template <class GenType>
void BinarySearchTree<GenType>::inOrder(TreeNode<GenType> *leaf)
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
void BinarySearchTree<GenType>::inOrder()
{
	inOrder(root);
}

template <class GenType>
void BinarySearchTree<GenType>::preOrder(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
	{
		return;
	}
	cout<<leaf->item<<" ";
	preOrder(leaf->left);
	preOrder(leaf->right);
}

template <class GenType>
void BinarySearchTree<GenType>::preOrder()
{
	preOrder(root);
}

template <class GenType>
void BinarySearchTree<GenType>::postOrder(TreeNode<GenType> *leaf)
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
void BinarySearchTree<GenType>::postOrder()
{
	postOrder(root);
}

int main()
{
	BinarySearchTree<int> T;
	T.insert(9);
	T.insert(5);
	T.insert(10);
	T.insert(0);
	T.insert(6);
	T.insert(11);
	T.insert(-1);
	T.insert(1);
	T.insert(2);
	
	T.preOrder();
	
	cout<<endl;
	cout<<T.isMember(11)<<endl;
	cout<<T.size()<<endl;
	
	TreeNode<int> *temp;
	T.search(28);
	//cout<<temp->left->item<<endl;
	cout<<T.findMax()<<endl;
	cout<<T.isRoot(15)<<endl;

	
	cout<<T.isMember(11)<<endl;
	cout<<T.height()<<endl;
	
	return 0;
}
