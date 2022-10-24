// insert, search, delete and inorder display
#include <iostream>

using namespace std;

template <typename T>
struct TreeNode
{
	T data;
	TreeNode *left;
	TreeNode *right;
};

template <typename T>
class BST
{
private:
	TreeNode<T> *R;
	int size;

public:
	BST();
	bool insert(T);
	void display();
	void inorder(TreeNode<T> *);
	void preorder(TreeNode<T> *);
	void postorder(TreeNode<T> *);
	bool search(T);
	bool deleteele(T);
	bool findmin(T &x);
	bool findmax(T &x);
};

template <typename T>
BST<T>::BST()
{
	R = NULL;
	size = 0;
}

template <typename T>
bool BST<T>::insert(T x)
{
	// New Node Creation
	TreeNode<T> *n;
	n = new TreeNode<T>;

	if (n == NULL) // memory space is created or not for the treenode
	{
		return false;
	}

	// Initialization; fill the treenode with value
	n->data = x;
	n->left = NULL;
	n->right = NULL;

	// if newtree node is root
	if (R == NULL)
	{
		R = n;
		return true;
	}

	TreeNode<T> *t, *p;
	t = new TreeNode<T>;
	p = new TreeNode<T>;

	p = NULL; // initially root parent node is Null
	t = R;	  // temp will be pointed by root node

	////Search the correct poition for the New Node
	while (t != NULL)
	{
		p = t;			 // parent will point t beforme moving to left or right
		if (x < t->data) // true then move to left tree
		{
			t = t->left;
		}
		else if (x > t->data) // true then move to left tree
		{
			t = t->right;
		}
		else
		{
			return false; // duplicate values
		}
	}

	// Link the New Node in the proper position
	if (n->data < p->data)
	{
		p->left = n;
		return true;
	}
	else
	{
		p->right = n;
		return true;
	}
}

template <typename T>
bool BST<T>::search(T x)
{
	TreeNode<T> *t;
	t = R;
	while (t != NULL)
	{
		if (x == t->data)
		{
			return true;
		}
		else if (x < t->data)
		{
			t = t->left;
		}
		else
		{
			t = t->right;
		}
	}
	return false;
}

template <typename T>
bool BST<T>::deleteele(T x)
{

	TreeNode<T> *t, *p;
	t = new TreeNode<T>;
	p = new TreeNode<T>;
	int d; // direction 1-left and 2-right

	p = NULL; // initially root parent node is Null
	t = R;	  // temp will be pointed by root node
	d = 0;	  // initially direction is neither left nor right
	while (t != NULL)
	{
		if (x < t->data)
		{
			p = t;
			t = t->left;
			d = 1; // direction is left
		}
		else if (x > t->data)
		{
			p = t;
			t = t->right;
			d = 2; ////direction is right
		}
		else if (x == t->data) // 3 cases for deletion
		{
			if (t->left == NULL) // case 1-t is leaf node or t is having only right subtree or root
			{
				if (d == 1) // case 1.1
					p->left = t->right;
				else if (d == 2) // case 1.2
					p->right = t->right;
				else if (t == R) // case 1.3
					R = t->right;
				delete (t);
				return true;
			}
			else if (t->right == NULL) // case 2-t is leaf node or t is having only left subtree or root
			{
				if (d == 1) // case 2.1
					p->left = t->left;
				else if (d == 2) // case 2.2
					p->right = t->left;
				else if (t == R) // case 2.3
					R = t->left;
				delete (t);
				return true;
			}
			else // case 3 - t is having both left and right
			{	 // select biggest number from left subtree or smallest number from right subtree
				// leftmost from the right subtree i.e smallest no from right subtree
				TreeNode<T> *m; // temp node
				m = new TreeNode<T>;
				m = t->right;

				while (m->left != NULL)
				{
					m = m->left;
				}
				int tmp;
				tmp = t->data;
				t->data = m->data;
				m->data = tmp;

				p = t;
				t = t->right;
				d = 2;
			} // delete case 1,2 and 3
		}	  // left,right,equal
	}		  // while
	return false;
}

template <typename T>
bool BST<T>::findmin(T &x)
{
	if (R == NULL)
	{
		x = -1;
		return false;
	}
	TreeNode<T> *t; // temp node
	t = new TreeNode<T>;
	t = R;
	while (t->left != NULL)
	{
		t = t->left;
	}
	x = t->data;
	return true;
}

template <typename T>
bool BST<T>::findmax(T &x)
{
	if (R == NULL)
	{
		x = -1;
		return false;
	}
	TreeNode<T> *t; // temp node
	t = new TreeNode<T>;
	t = R;
	while (t->right != NULL)
	{
		t = t->right;
	}
	x = t->data;
	return true;
}

template <typename T>
void BST<T>::display()
{
	cout << "\nInorder display : \n";
	inorder(R);

	cout << "\nPreorder display : \n";
	preorder(R);

	cout << "\nPostorder display : \n";
	postorder(R);
}

template <typename T>
void BST<T>::inorder(TreeNode<T> *R)
{
	if (R == NULL)
	{
		return;
	}
	inorder(R->left);
	cout << R->data << "\t";
	inorder(R->right);
}

template <typename T>
void BST<T>::preorder(TreeNode<T> *R)
{
	if (R == NULL)
	{
		return;
	}
	cout << R->data << "\t";
	preorder(R->left);
	preorder(R->right);
}

template <typename T>
void BST<T>::postorder(TreeNode<T> *R)
{
	if (R == NULL)
	{
		return;
	}
	postorder(R->left);
	postorder(R->right);
	cout << R->data << "\t";
}
int main()
{
	BST<int> m;
	bool r;
	int x = 0;

	m.insert(45);
	m.insert(65);
	m.insert(25);
	m.insert(57);
	m.insert(60);
	m.insert(35);
	m.insert(38);
	m.insert(29);
	m.insert(15);
	/*
		m.insert(95);
		m.insert(44);
		m.insert(70);
		m.insert(20);
	*/
	m.display();
	/*
		r=m.search(57);
		if(r)
			cout<<"\n57 is found in BST\n";
		else
			cout<<"\n57 is not found in BST\n";

		r=m.search(12);
		if(r)
			cout<<"\n12 is found in BST\n";
		else
			cout<<"\n12 is not found in BST\n";

		m.deleteele(35);
		cout<<"\nAfter deleting 35 in BST\n";
		m.display();

		m.findmin(x);
		cout<<"\nMinimum = "<<x;

		m.insert(11);
		cout<<"\nAfter inserting 11 in BST\n";
		m.display();

		m.findmin(x);
		cout<<"\nMinimum = "<<x;

		m.findmax(x);
		cout<<"\nMaximum = "<<x;
	*/
}
