#include <iostream>
#define m 5
using namespace std;
struct node
{
  int n;
  int leaf;
  int data[m];
  node *child[m];

  node()
  {
     n = 0;
     leaf = 1;
     for (int i=0; i<m-1; i++)
     {
	     data[i] = 0;
	     child[i] = NULL;
     }
     child[m-1] = NULL;

  }
  void insert_nonfull(int key);
  void split_child(int i, node *y);
  void traverse();
  int search(int key);

};
class BTREE
{
  node *root;
  public:
    BTREE();
    node* allocate_node();
    void insert(int key);
    int search(int key)
    {
      if (root == NULL)
	     return 0;
      else
	     return root->search(key);
    }
    void traverse(){ root->traverse(); }
};
BTREE::BTREE()
{
  root = NULL;
}
int node::search(int key)
{
  int i = 0;
  while (i < n && data[i] < key)
     i = i + 1;
  if (data[i] == key)
     return 1;
  else if (leaf)
     return 0;
  else
     return child[i]->search(key);
}

void node::traverse()
{
  for (int i=0; i<n; i++)
  {
    if (!leaf)
    {
      cout << endl<<"Child - " << i <<":\n";
      child[i]->traverse();
      cout << endl;
    }
    cout << "Data - "<< i << ": "<<data[i] <<"\n";
  }
  if (!leaf)
  {
     cout << endl <<"child - " << n <<":\n";
     child[n]->traverse();
  }
}

void BTREE::insert(int key)
{
  if (root == NULL)
  {
    root = new node();
    root->data[0] = key;
    root->n = 1;
    return;
  }
  if (root->search(key))
  {
     cout << "Duplicate Element. Can't Insert" << endl;
     return;
  }
  if (root->n == m-1)
  {
      node *s = new node();
      int i=0;
      s->leaf = 0;
      s->n = 0;
      s->child[0] = root;
      for (i=root->n-1; i>=0 && root->data[i] > key; i--)
	     root->data[i+1] = root->data[i];
      root->data[i+1] = key;
      s->split_child(0, root);
      root = s;
  }
  else
     root->insert_nonfull(key);
}

void node::insert_nonfull(int key)
{
  int i = n-1;
  if (leaf)
  {
    while (i>=0 && data[i] > key)
    {
      data[i+1] = data[i];
      i--;
    }
    data[i+1] = key;
    n++;
  }
  else
  {
    while (i >=0 && data[i] > key)
         i--;
    if (child[i+1]->n == m-1)
    {
      int j;
      for (j=child[i+1]->n-1; j>=0 && child[i+1]->data[j] > key; j--)
	     child[i+1]->data[j+1] = child[i+1]->data[j];
      child[i+1]->data[j+1] = key;
      split_child(i+1, child[i+1]);
    }
    else
      child[i+1]->insert_nonfull(key);
  }
}
void node::split_child(int i, node *y)
{
  node *z = new node();
  int j;
  z->leaf = y->leaf;
  z->n = m/2;
  for (j=0; j<m/2; j++)
     z->data[j] = y->data[j+m/2+1];
  if (!(y->leaf))
  {
    for (j=0; j<m/2+1;j++)
      z->child[j] = y->child[j+m/2];
  }
  y->n=m/2;
  for (j=n; j>=i+1; j--)
    child[j+1] = child[j];
  child[i+1] = z;
  for (j=n-1; j>=i; j--)
    data[j+1] = data[j];
  data[i] = y->data[m/2];
  n =n + 1;
}
int main()
{
  BTREE btree;
  int ch;
  int key;
  do
  {
     cout << "\n1. Insert\n2. Search\n3.Traverse\n";
     cout << "Enter your choice : ";
     cin >> ch;
     switch (ch)
     {
       case 1: cout << "Enter the element to insert: ";
	       cin >> key;
	       btree.insert(key);
	       btree.traverse();
	       break;
       case 2: cout << "Enter the element to search: ";
	       cin >> key;
	       if (btree.search(key))
		 cout << "Element Present" << endl;
	       else
		 cout << "Element Not Present" << endl;
	       break;
       case 3: btree.traverse();
     }
  }
  while (ch < 4);
  return 0;
}
