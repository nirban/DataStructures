#include <iostream>
#include <algorithm>
#include <cstdlib>


using namespace std;

template <class GenType> 
class AVLTree;

template <class GenType> 
class TreeNode
{
	public:
		GenType item;
		int height;
		TreeNode<GenType> *left;
		TreeNode<GenType> *right;
		TreeNode<GenType> *parent;
		
		friend class AVLTree<GenType>;
};


template <class GenType> 
class AVLTree
{
	private:
		TreeNode<GenType>* newNode(TreeNode<GenType> *leaf, GenType data);
		int height(TreeNode<GenType> *leaf);
		void clear(TreeNode<GenType> *leaf);
		int size(TreeNode<GenType> *leaf);
		
		int getBalance(TreeNode<GenType> *leaf);
		
		GenType& findMin(TreeNode<GenType> *leaf);
		GenType& findMax(TreeNode<GenType> *leaf);
		
		TreeNode<GenType>* rightRotate(TreeNode<GenType> *node);
		TreeNode<GenType>* leftRotate(TreeNode<GenType> *node);
		TreeNode<GenType>* insert(TreeNode<GenType> *leaf, GenType data);
		TreeNode<GenType>* remove(TreeNode<GenType> *leaf, GenType val);
		
		bool isMember(TreeNode<GenType> *leaf, GenType val);
		TreeNode<GenType>* search(TreeNode<GenType> *leaf, GenType val);
		
		TreeNode<GenType>* minValueNode(TreeNode<GenType>* node);
		
		void inOrder(TreeNode<GenType> *leaf);
		void preOrder(TreeNode<GenType> *leaf);
		void postOrder(TreeNode<GenType> *leaf);		
		
	public:
		TreeNode<GenType> *root;
		AVLTree();
		~AVLTree();
		bool isEmpty();
		int size();
		void clear();
		int height();
		
		GenType& findMin();
		GenType& findMax();
		
		void insert(GenType data);
		TreeNode<GenType>* remove(GenType val);
		TreeNode<GenType>* search(GenType val);
		bool isMember(GenType val);
		void inOrder();
		void preOrder();
		void postOrder();
};

template <class GenType>
AVLTree<GenType>::AVLTree()
{
	root = NULL;
}

template <class GenType> 
AVLTree<GenType>::~AVLTree()
{
	clear();
}

template <class GenType> 
TreeNode<GenType>* AVLTree<GenType>::newNode(TreeNode<GenType> *leaf, GenType data)
{
	TreeNode<GenType> *temp = new TreeNode<GenType>;
	
	temp->item = data;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;
	temp->parent = leaf;
	
	return temp;
}

template <class GenType> 
bool AVLTree<GenType>::isEmpty()
{
	return root == NULL;
}

template <class GenType> 
int AVLTree<GenType>::size(TreeNode<GenType> *leaf)
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
int AVLTree<GenType>::size()
{
	return size(root);
}

template <class GenType>
void AVLTree<GenType>::clear(TreeNode<GenType> *leaf)
{
	if(leaf != NULL)
	{
		clear(leaf->left);
		clear(leaf->right);
		delete leaf;
	}
}

template <class GenType>
void AVLTree<GenType>::clear()
{
	clear(root);
}

template <class GenType>
int AVLTree<GenType>::height()
{
	return height(root);
}

template <class GenType>
int AVLTree<GenType>::height(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
	{
		return 0;
	}
	else
	{
		return leaf->height;
	}	
}

template <class GenType>
int AVLTree<GenType>::getBalance(TreeNode<GenType> *leaf)
{
	if(leaf == NULL)
	{
		return 0;
	}
	else
	{
		return height(leaf->left) - height(leaf->right);
	}
}


template <class GenType> 
bool AVLTree<GenType>::isMember(TreeNode<GenType> *leaf, GenType val)
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
bool AVLTree<GenType>::isMember(GenType val)
{
	return isMember(root, val);
}


template <class GenType> 
GenType& AVLTree<GenType>::findMin(TreeNode<GenType> *leaf)
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
GenType& AVLTree<GenType>::findMin()
{
	return findMin(root);
}

template <class GenType> 
GenType& AVLTree<GenType>::findMax(TreeNode<GenType> *leaf)
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
GenType& AVLTree<GenType>::findMax()
{
	return findMax(root);
}

template <class GenType>
TreeNode<GenType>* AVLTree<GenType>::minValueNode(TreeNode<GenType>* node)
{
	TreeNode<GenType>* temp = node;
	while(temp->left != NULL)
	{
		temp = temp->left;
	}
	return temp;
}

template <class GenType> 
TreeNode<GenType>* AVLTree<GenType>::remove(TreeNode<GenType> *leaf, GenType val)
{
	//perform standerd BST delete
	if(leaf == NULL)
	{
		return leaf;
	}
	if(val < leaf->item)
	{
		leaf->left = remove(leaf->left,val);
	}
	if(val > leaf->item)
	{
		leaf->right = remove(leaf->right,val);
	}
	else
	{	
		
		//case 1; leaf node
		if(leaf->right == NULL && leaf->left == NULL)
		{
			TreeNode<GenType> *temp = leaf;
			leaf = NULL;
			delete temp;
		}
		else if(leaf->left == NULL)  // case 2: one child
		{
			TreeNode<GenType> *temp = leaf;
			leaf = leaf->right;			
			//temp = leaf->right;
			//*leaf = *temp;
			leaf->parent = temp->parent;
			delete temp;
		}
		else if(leaf->right == NULL)
		{
			TreeNode<GenType> *temp = leaf;
			leaf = leaf->left;			
			//temp = leaf->left;
			//*leaf = *temp;
			leaf->parent = temp->parent;
			delete temp;
		}
		else // case 3: two child
		{
			TreeNode<GenType> *temp = search(findMin(leaf->right));
			//TreeNode<GenType> *temp = minValueNode(leaf->right);
			leaf->item = temp->item;
			leaf->right = remove(leaf->right, temp->item);
		}
	}
	
	
	if(leaf == NULL)
	{
		return leaf;
	}
	
	leaf->height = 1 + max(height(leaf->left), height(leaf->right));
	
	int balance = getBalance(leaf);
	
	//cout<<" Balance on Node : "<<leaf->item<<" and Height is "<<leaf->height<<" Balance Factor is "<<balance<<endl;
	
	if(balance > 1 && getBalance(leaf->left) >= 0)
	{
		return rightRotate(leaf);
	}
	else if( balance > 1 && getBalance(leaf->left) < 0)
	{
		leaf->left =  leftRotate(leaf->left);
        return rightRotate(leaf);
	}
	else if(balance < -1 && getBalance(leaf->right) <= 0)
	{
		return leftRotate(leaf);
	}
	else if(balance < -1 && getBalance(leaf->right) > 0)
	{
		leaf->right = rightRotate(leaf->right);
		return leftRotate(leaf);
	}
	
	return leaf;	
}

template <class GenType>
TreeNode<GenType>* AVLTree<GenType>::remove(GenType val)
{
	root = remove(root, val);
	return root;
}

template <class GenType> 
TreeNode<GenType>* AVLTree<GenType>::search(TreeNode<GenType> *leaf, GenType val)
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
TreeNode<GenType>* AVLTree<GenType>::search(GenType val)
{
	return search(root,val);
}


template <class GenType>
TreeNode<GenType>* AVLTree<GenType>::rightRotate(TreeNode<GenType>* node)
{
	TreeNode<GenType> *newNode = node->left;

	newNode->parent = node->parent;
	node->left = node->left->right;

	newNode->right = node;
	
	node->parent = newNode;
	
	node->height = max(height(node->left), height(node->right)) + 1;
	newNode->height = max(height(newNode->left), height(newNode->right)) + 1;
	
	return newNode;
}

template <class GenType>
TreeNode<GenType>* AVLTree<GenType>::leftRotate(TreeNode<GenType>* node)
{
	TreeNode<GenType> *newNode = node->right;
	
	newNode->parent = node->parent; //change the parent of newnode
	node->right = node->right->left;
	
	newNode->left = node;

	node->parent = newNode;
	
	node->height = max(height(node->left), height(node->right)) + 1;
	newNode->height = max(height(newNode->left), height(newNode->right)) + 1;

	return newNode;
}


template <class GenType> 
void AVLTree<GenType>::insert(GenType data)
{	
	if(isEmpty())
	{
		TreeNode<GenType> *temp = new TreeNode<GenType>;
	
		temp->item = data;
		temp->left = NULL;
		temp->right = NULL;
		temp->height = 1;
		root = temp;
		root->parent = NULL;
	}
	else
	{
		root = insert(root,data);
	}
}

template <class GenType> 
TreeNode<GenType>* AVLTree<GenType>::insert(TreeNode<GenType> *leaf, GenType data)
{
	//TreeNode<GenType> *temp = new TreeNode<GenType>;
	//TreeNode<GenType> *p = new TreeNode<GenType>;
	
	/*if(leaf == NULL)
	{
		return newNode(leaf, data);
	}*/
	if(data < leaf->item)
	{		
		if(leaf->left == NULL)
		{
		    TreeNode<GenType> *temp = new TreeNode<GenType>;
			temp->item = data;
			temp->left = temp->right = NULL;
			temp->height = 1;
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
			temp->height = 1;
			temp->parent = leaf;
			leaf->right = temp;
		}
		else
		{
			leaf->right = insert(leaf->right, data);
		}
	}
	
	//update the height parent node
	leaf->height = 1 + max(height(leaf->left), height(leaf->right));
	
	//get the balance factor
	int balance = getBalance(leaf);
	
	if(balance > 1 && data < leaf->left->item) //left left case
	{	
		//cout<<" Right Rotate on : "<<leaf->item<<endl;
		return rightRotate(leaf);
	}
	else if(balance < -1 && data > leaf->right->item) // right right case
	{
		//out<<" left Rotate on : "<<leaf->item<<endl;
		return leftRotate(leaf);
	}
	else if(balance > 1 && data > leaf->left->item) //left right case
	{
		//cout<<" left Rotate on : "<<leaf->left->item<<endl;
		leaf->left =  leftRotate(leaf->left);
		//cout<<" Right Rotate on : "<<leaf->item<<endl;
        return rightRotate(leaf);
	}
	else if(balance < -1 && data < leaf->left->item) //right left case
	{
		//cout<<" Right Rotate on : "<<leaf->right->item<<endl;
		leaf->right =  rightRotate(leaf->right);
		//cout<<" left Rotate on : "<<leaf->item<<endl;
        return leftRotate(leaf);
	}
		
	return leaf;
}

template <class GenType>
void AVLTree<GenType>::inOrder(TreeNode<GenType> *leaf)
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
void AVLTree<GenType>::inOrder()
{
	inOrder(root);
}


template <class GenType>
void AVLTree<GenType>::preOrder(TreeNode<GenType> *leaf)
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
void AVLTree<GenType>::preOrder()
{
	preOrder(root);
	cout<<endl;
	//cout<<root->height<<endl;
	
}

template <class GenType>
void AVLTree<GenType>::postOrder(TreeNode<GenType> *leaf)
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
void AVLTree<GenType>::postOrder()
{
	postOrder(root);
}

int main()
{
	AVLTree<int> T;
	
	T.insert(9);
	T.insert(5);
	T.insert(10);
	T.insert(0);
	T.insert(6);
	T.insert(11);
	
	T.insert(-1);
	T.insert(1);
	T.preOrder();
	T.insert(2);
	
	T.preOrder();
	
	TreeNode<int> *temp = T.root;
	temp = temp->left->right;
	cout<<temp->item<<endl;
	
	temp = temp->parent;
	cout<<temp->item<<endl;
	T.remove(10);
	T.preOrder();
	
	return 0;
}
