#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left;
    node *right;
    node *parent;
};
class SplayTree
{
    node *root;

public:
    SplayTree()
    {
        root = NULL;
    }

    void insertnode(int x)
    {
        node *newnode = new node;
        newnode->data = x;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->parent = NULL;

        if (root == NULL)
        {
            root = newnode;
            return;
        }

        node *temp = root;
        while (temp != NULL)
        {
            if (temp->data > x)
            {
                if (temp->left == NULL)
                {
                    temp->left = newnode;
                    newnode->parent = temp;
                    Splay(newnode); // splaying
                    return;
                }
                else
                    temp = temp->left;
            }
            else if (temp->data < x)
            {
                if (temp->right == NULL)
                {
                    temp->right = newnode;
                    newnode->parent = temp;
                    Splay(newnode); // splaying
                    return;
                }
                else
                    temp = temp->right;
            }
            else
            {
                cout << "There is duplicate element. Can't insert" << endl;
                return;
            }
        }
    }

    void search(int x)
    {
        int count = 0;
        if (root == NULL)
        {
            cout << "Empty splay tree." << endl;
            return;
        }
        if (root->data == x)
        {
            cout << "The element is found at root." << endl;
            return;
        }
        node *temp = root;
        node *prev = NULL;
        while (temp != NULL)
        {
            count++;
            if (temp->data > x)
            {
                prev = temp;
                temp = temp->left;
            }
            else if (temp->data < x)
            {
                prev = temp;
                temp = temp->right;
            }
            else
            {
                cout << "The element is found after " << count << " comparisons." << endl;
                Splay(temp); // splaying
                return;
            }
        }
        cout << "The element is not found" << endl;
        Splay(prev); // splaying
    }

    void Splay(node *temp)
    {

        node *x = temp;
        node *p = temp->parent;
        node *g;
        cout << "Splaying : " << temp->data << endl;
        cout << "X : " << temp->data << "  Parent : " << p->data;
        while (p != NULL)
        {
            g = p->parent;
            if (g == NULL)
            {
                if (p->left == x) // Zig
                {
                    cout << endl
                         << "Performing Zig Operation." << endl;
                    p->left = x->right;
                    if (x->right != NULL)
                        x->right->parent = p;
                    x->right = p;
                    p->parent = x;
                    x->parent = NULL;
                    root = x;
                    return;
                }
                else if (p->right == x) // Zag
                {
                    cout << endl
                         << "Performing Zag Operation." << endl;
                    p->right = x->left;
                    if (x->left != NULL)
                        x->left->parent = p;
                    x->left = p;
                    p->parent = x;
                    x->parent = NULL;
                    root = x;
                    return;
                }
            }
            else
            {
                cout << " GP : " << g->data << endl;
                node *gg = g->parent;
                if (p->left == x && g->left == p) // Zig-Zig
                {
                    cout << "Performing Zig-Zig Operation." << endl;
                    g->left = p->right;
                    if (p->right != NULL)
                        p->right->parent = g;
                    p->left = x->right;
                    if (x->right != NULL)
                        x->right->parent = p;
                    p->right = g;
                    g->parent = p;
                    x->right = p;
                    p->parent = x;
                    x->parent = gg;
                    if (x->parent == NULL)
                    {
                        root = x;
                        return;
                    }
                    else if (gg->left == g)
                        gg->left = x;
                    else
                        gg->right = x;
                }
                else if (p->right == x && g->left == p) // Zig-Zag
                {
                    cout << "Performing Zig-Zag Operation." << endl;
                    p->right = x->left;
                    if (x->left != NULL)
                        x->left->parent = p;
                    g->left = x->right;
                    if (x->right != NULL)
                        x->right->parent = g;
                    x->left = p;
                    p->parent = x;
                    x->right = g;
                    g->parent = x;
                    x->parent = gg;
                    if (x->parent == NULL)
                    {
                        root = x;
                        return;
                    }
                    else if (gg->left == g)
                        gg->left = x;
                    else
                        gg->right = x;
                }
                else if (p->left == x && g->right == p) // Zag-Zig
                {
                    cout << "Performing Zag-Zig Operation." << endl;
                    g->right = x->left;
                    if (x->left != NULL)
                        x->left->parent = g;
                    p->left = x->right;
                    if (x->right != NULL)
                        x->right->parent = p;
                    x->left = g;
                    g->parent = x;
                    x->right = p;
                    p->parent = x;
                    x->parent = gg;
                    if (x->parent == NULL)
                    {
                        root = x;
                        return;
                    }
                    else if (gg->left == g)
                        gg->left = x;
                    else
                        gg->right = x;
                }
                else if (p->right == x && g->right == p) // Zag-Zag
                {
                    cout << "Performing Zag-Zag Operation." << endl;
                    g->right = p->left;
                    if (p->left != NULL)
                        p->left->parent = g;
                    p->right = x->left;
                    if (x->left != NULL)
                        x->left->parent = p;
                    p->left = g;
                    g->parent = p;
                    x->left = p;
                    p->parent = x;
                    x->parent = gg;
                    if (x->parent == NULL)
                    {
                        root = x;
                        return;
                    }
                    else if (gg->left == g)
                        gg->left = x;
                    else
                        gg->right = x;
                }
            }
            p = x->parent;
            if (p != NULL)
                g = p->parent;
        }
    }

    void preorder()
    {
        if (root != NULL)
            preorder(root);
    }

    void inorder()
    {
        if (root != NULL)
            inorder(root);
    }

    void preorder(node *temp)
    {
        if (temp != NULL)
        {
            cout << temp->data << " ";
            preorder(temp->left);
            preorder(temp->right);
        }
    }
    void inorder(node *temp)
    {
        if (temp != NULL)
        {
            inorder(temp->left);
            cout << temp->data << " ";
            inorder(temp->right);
        }
    }
    void deletenode(int d)
    {
        node *temp = root;
        node *parent = NULL;
        char dir = 'L';
        if (root == NULL)
        {
            cout << "Empty Tree. Can't Delete" << endl;
            return;
        }
        else
        {
            while (temp != NULL && temp->data != d)
            {
                if (temp->data > d)
                {
                    parent = temp;
                    dir = 'L';
                    temp = temp->left;
                }
                else
                {
                    parent = temp;
                    dir = 'R';
                    temp = temp->right;
                }
            }
            if (temp == NULL)
            {
                cout << "Element Not Found." << endl;
                if (parent != root)
                    Splay(parent); // splaying
                return;
            }
            else
            {
                node *z = temp;
                node *x;
                if (temp->left == NULL)
                    x = temp->right;
                else if (temp->right == NULL)
                    x = temp->left;
                else
                {
                    node *predparent = temp;
                    node *in_pred = temp->left;
                    while (in_pred->right != NULL)
                    {
                        predparent = in_pred;
                        in_pred = in_pred->right;
                    }
                    if (predparent != z)
                    {
                        predparent->right = in_pred->left;
                        in_pred->left = z->left;
                    }
                    in_pred->right = z->right;
                    x = in_pred;
                }
                if (parent != NULL)
                {
                    if (dir == 'L')
                        parent->left = x;
                    else
                        parent->right = x;
                    Splay(parent); // splaying
                }
                else
                    root = x;
            }
        }
    }
};
int main()
{
    SplayTree tree;
    int d, op;
    do
    {
        cout << "1. Insert Element \n2. Search Element \n3. Delete Element \n4. Exit" << endl;
        cin >> op;
        switch (op)
        {
        case 1:
        {
            cout << "Enter element to insert ";
            cin >> d;
            tree.insertnode(d);
            cout << "Preorder : ";
            tree.preorder();
            cout << endl
                 << "Inorder : ";
            tree.inorder();
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "Enter element to search ";
            cin >> d;
            tree.search(d);
            cout << "Preorder : ";
            tree.preorder();
            cout << endl
                 << "Inorder : ";
            tree.inorder();
            cout << endl;
            break;
        }
        case 3:
        {
            cout << "Enter element to delete ";
            cin >> d;
            tree.deletenode(d);
            cout << "Preprder : ";
            tree.preorder();
            cout << endl
                 << "Inorder : ";
            tree.inorder();
            cout << endl;
            break;
        }
        }
    } while (op < 4);
    return 0;
}