#include <iostream>
using namespace std;
enum COLOR {RED=1, BLACK=0, DOUBLEBLACK=2};

struct node
{
   int data;
   COLOR color;
   node *left;
   node *right;
   node *parent;
   node(int d)
   {
      data = d;
      color = RED;
      left = right = parent = NULL;
   }
};
class RBTree
{
   node *root;

   public:
     RBTree()
     {
		 root= nil();
     }
     void insert(int data)
     {
		 node *x = new node(data);
		 x->left = nil();
		 x->right = nil();
		 root = insertnode(x, root);
		 RB_Fixup(x);
     }

     node* nil()
     {
		 node *nilnode = new node(0);
		 nilnode->color = BLACK;
		 nilnode->left = NULL;
		 nilnode->right = NULL;
		 nilnode->parent = NULL;
		 return nilnode;
     }

     node* insertnode(node *x, node *p)
     {
       if (p->data == 0)
	  		 return x;
       if (x->data < p->data)
       {
	 		 cout << "Move to Left Child of " << p->data << endl;
	 		 p->left = insertnode(x, p->left);
			 p->left->parent = p;
       }
       else if (x->data > p->data)
       {
			 cout << "Move to Right Child of " << p->data << endl;
			 p->right = insertnode(x, p->right);
			 p->right->parent = p;
       }
       else
       {
			 cout << "Duplicate keys. Can't Insert" << endl;
			 return NULL;
       }
       return p;
     }

     void search(int x)
     {
       int count = 0;
       if (root == NULL)
       {
	 	 cout << "Empty RB tree." << endl;
		 return;
       }
       node *temp=root;
       while (temp->data != 0)
       {
		  count++;
		  if (temp->data > x)
		     temp = temp->left;
		  else if (temp->data < x)
		     temp = temp->right;
		  else
		  {
	    	 cout << "The element is found after " << count <<" comparisons." << endl;
	    	 return;
	   	  }
       }
       cout << "The element is not found" << endl;
     }

     void RB_Fixup(node *z)
     {
       while (z->parent != NULL && z->color != BLACK && z->parent->color == RED)
       {
		 if (z->parent == z->parent->parent->left)  // if P is left child of G
		 {
		  	 node *y = z->parent->parent->right;
		  	 if (y->color == RED)					//If uncle y is RED
		  	 {
		  	   	 z->parent->color = BLACK;			// Change color of P, G, & y
	    		 y->color = BLACK;
	    		 z->parent->parent->color = RED;
	    		 z = z->parent->parent;				// Take G as new Z
	   	     }
	   	   	 else									// if uncle y is BLACK
	   		 {
	    	 	 if (z == z->parent->right)		    // If you are in case 2
	    		 {
	    		     z = z->parent;
	    		     LeftRotate(z);
	     		 }	
	    		 z->parent->color = BLACK;			// case - 3
	    		 z->parent->parent->color = RED;
	    		 RightRotate(z->parent->parent);
	    		 z = z->parent;
	   		 }
	 	 }
		 else										// If P is right child of G
		 {
		   	 node *y = z->parent->parent->left;		// Uncle y is left child of P
		  	 if (y->color == RED)					// If uncle y is RED
	  		 {
	    		 z->parent->color = BLACK;			// Change colors of P, G, & y
	    		 y->color = BLACK;
	    		 z->parent->parent->color = RED;
	    		 z = z->parent->parent;				// Take G as new z
	  		 }
	   		 else									// Uncle y is BLACK
	   		 {
	    	 	 if (z == z->parent->left)			// If you are in case 2
	    		 {
	    			 z = z->parent;
	    		     RightRotate(z);				// Right rotate on P
	   			 }
	    		 z->parent->color = BLACK;			// case - 3
	    		 z->parent->parent->color = RED;	// Change color of P & G Left Rotate on G
	    		 LeftRotate(z->parent->parent);
	    		 z = z->parent;
	   		}
	 	 }
       }
       root->color = BLACK;
     }
     void LeftRotate(node *x)
     {
      	 cout << "Left Rotate on : " << x->data << endl;
      	 node *y = x->right;
      	 node *par = x->parent;
      	 x->right = y->left;
      	 if (x->right->parent != NULL)
       		 x->right->parent = x;
      	 y->parent = par;
      	 if (par == NULL)
	 		 root = y;
      	 else if (x == par->left)
			 par->left = y;
      	 else
			 par->right = y;
    	 y->left = x;
      	 x->parent = y;
     }

     void RightRotate(node *x)
     {
       	 cout << "Right Rotate on : " << x->data << endl;
      	 node *y = x->left;
      	 node *par = x->parent;
      	 x->left = y->right;
      	 if (x->left != NULL)
      		 x->left->parent = x;
      	 y->parent = par;
       	 if (x->parent == NULL)
	  		 root = y;
      	 else if (x == par->left)
	  		 par->left = y;
       	 else
	 		 par->right = y;
      	 y->right = x;
      	 x->parent = y;
     }

     void deletenode(int d)
     {
       	 if (root == NULL || root->data == 0)
      	 {
			 cout << "Empty Red-Black Tree. " << endl;
			 return;
      	 }
       	 node *v;
      	 node *auxnode = nil();
      	 auxnode->left = root;
      	 auxnode->right = nil();
      	 root->parent = auxnode;
      	 root =  remove(d, root);
     }

     node* remove(int d, node *x)
     {
      	 if (d < x->data)
      	 {
	 		 if (x->left->data != 0)
	 		 {
			  
	    		 x->left = remove(d, x->left);
	    		 return x;
	    	 }
	 		 else
	 		 {
			   	 cout << "Element Not Found" << endl;
			  	 return x;
			 }
       	 }
      	 else if (d > x->data)
      	 {
			 if (x->right->data != 0)
			 {
			 	 x->right = remove(d, x->right);
			 	 return x;
			 }
			 else
			 {
			   	 cout << "Element Not Found" << endl;
			  	 return x;
			 }	
      	 }
      	 else
      	 {
	 		 if (x->left->data != 0 && x->right->data != 0)
	 		 {
	  			 x->data = inpred(x->left);
	   			 x->left = remove(x->data, x->left);
	   			 return x;
	 		 } 
			 else
	 	 	 {
	 		  	 if (x->parent->left == x)
	   		 	 {
	    			 node *p = x->parent;
	    			 p->left = (x->left->data != 0) ? x->left : x->right;
	    			 p->left->parent = p;
	   				 DeleteFix(p->left, x);
	    			 return p->left;
	   		 	 }
	   			 else //if (x->parent->right == x)
	   			 {
	    			 node *p = x->parent;
	    			 p->right = (x->left->data != 0) ? x->left : x->right;
	    			 p->right->parent = p;
	    			 DeleteFix(p->right, x);
	   				 return p->right;
	   			 }
	 	 	 }
         }
     }

     int inpred(node *y)
     {
       while (y->right->data != 0)
		 y = y->right;
       return y->data;
     }

     void DeleteFix(node *u, node *v)      // v is the node deleted, u is the node replaced it
      {
		 if (u == root || u->color == RED || v->color == RED)
		 {
	  		 u->color = BLACK;
	  		 return;
		 }
	 	 if (u->color == BLACK && v->color == BLACK)
		 {
	 		 u->color = DOUBLEBLACK;
		 	 DBFix(u);
		 }
		 root->color = BLACK;
     }

     void DBFix(node *u)
     {
	 	 node *s, *r;
	 	 if (u == root)
	 	 {
	    	 u->color = BLACK;
	    	 return;
	 	 }
	 	 if (u->parent->left == u)		// Find sibling s
	    	 s = u->parent->right;
	  	 else
	   		 s = u->parent->left;
	 	 if (s->data == 0)
	    	  return;  
	 	 if (s->color == BLACK)			// if sibling s is BLACK
	 	 {
	   		 if (s->left->color == RED)  // if sibling s has left child RED 
	  		 {
	     		 r = s->left;
	     		 if (s->parent->left == s)  
			 		 RightRotate(s->parent);
	     		 else
	     		 {
					 RightRotate(s);
					 LeftRotate(r->parent);
	      		 }
	     		 r->color = BLACK;
	   		 }
	   		 else if (s->right->color == RED)	// if sibling s has right child RED
	   		 {
	     		 r = s->right;
	     		 if (s->parent->right == s)
				 	 LeftRotate(s->parent);
	     		 else
	     		 {
					 LeftRotate(s);
					 RightRotate(r->parent);
	     		 }
	     		 r->color = BLACK;
	   		 }
	   		 else									// if sibling s has both children BLACK
	   		 {
	     		 s->color = RED;					// Change color of s
	     		 if (s->parent->color == BLACK)		// if parent is BLACK
	     		 {
					 s->parent->color=DOUBLEBLACK;	// move up extra BLACK to parent
					 DBFix(s->parent);				// Fix DOUBLE BLACK
	     		 }
	     		 else
					 s->parent->color = BLACK;		// if parent os RED, change it to BLACK
	   		 }
	  	 }
	  	 else									// if sibling s is RED
	 	 {
	   		 if (s->parent->right == s)			// Rotate around parent , change color of s and parent
	   		 {
	     		 LeftRotate(s->parent);
	     		 s->color=BLACK;
	     		 s->left->color=RED;
	   		 }
	   		 else
	   		 {
	     		 RightRotate(s->parent);
	     		 s->color = BLACK;
	     		 s->right->color = RED;
	   		 }
	  	 }
     }

     void preorder()
     {
       if (root != NULL)
	 	 preorder(root);
     }

     void inorder()
     {
       if (root!=NULL)
	 	 inorder(root);
     }

     void preorder(node *temp)
     {
       	 if (temp->data != 0)
      	 {
	 		 cout << "(" << temp->data << ", " << temp->color <<") ";
	 		 preorder(temp->left);
	 		 preorder(temp->right);
         }
     }
     void inorder(node *temp)
     {
     	 if (temp->data != 0)
       	 {
	 		 inorder(temp->left);
	 		 cout << "(" << temp->data << ", " << temp->color <<") ";
	 		 inorder(temp->right);
         }
     }

};
int main()
{
  	 RBTree tree;
  	 int d, op;
     do
   	 {
    	 cout << "1. Insert Element\n2. Search Element\n3. Delete Element\n4. Exit" << endl;
   		 cin >> op;
   		 switch (op)
  		 {
     		 case 1: {
				 cout << "Enter element to insert ";
				 cin >> d;
				 tree.insert(d);
				 cout << "Preorder : ";
				 tree.preorder();
				 cout <<endl << "Inorder : ";
				 tree.inorder();
				 cout << endl;
				 break;
	     	 }
    		 case 2: {
			 	 cout << "Enter element to search ";
				 cin >> d;
				 tree.search(d);
	 		 	 cout << "Preorder : ";
				 tree.preorder();
				 cout <<endl << "Inorder : ";
				 tree.inorder();
		  		 cout << endl;
				 break;
	      	 }
      		 case 3: {
				 cout << "Enter element to delete ";
				 cin >> d;
				 tree.deletenode(d);
				 cout << "Preorder : ";
				 tree.preorder();
				 cout <<endl << "Inorder : ";
		 		 tree.inorder();
				 cout << endl;
				 break;
	      	 }
    	 }
     }
     while (op < 4);
     return 0;
}
