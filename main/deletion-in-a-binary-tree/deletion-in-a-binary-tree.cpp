#include "deletion-in-a-binary-tree.h" //#include <bits/stdc++.h>
using namespace std;

struct Node
{
	int key;
	Node* left, *right;
};

struct Node* newNode(int key)
{
	struct Node* temp = new Node;
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
};

/* Inorder traversal of a binary tree*/
void inorder(struct Node* temp)
{
	if (!temp)
		return;
	inorder(temp->left);
	cout << temp->key << " ";
	inorder(temp->right);
}

void deletionBT(struct Node* root, int key);

/* Driver program to test size function*/
int main()
{
  int t;
  scanf("%d", &t);
  while (t--)
  {
     map<int, Node*> m;
     int n;
     scanf("%d",&n);
     struct Node *root = NULL;
     struct Node *child;
     while (n--)
     {
        Node *parent;
        char lr;
        int n1, n2;
        scanf("%d %d %c", &n1, &n2, &lr);
        if (m.find(n1) == m.end())
        {
           parent = newNode(n1);
           m[n1] = parent;
           if (root == NULL)
             root = parent;
        }
        else
           parent = m[n1];
        child = newNode(n2);
        if (lr == 'L')
          parent->left = child;
        else
          parent->right = child;
        m[n2]  = child;
     }
     int key;
     cin>>key;
     deletionBT(root, key);
     inorder(root);
     cout<<endl;
  }
  return 0;
}

/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*
Structre of the node of the tree is as
struct Node
{
	int key;
	Node* left, *right;
};
*/
// you are required to complete this function
void deletionBT(Node *root, const int key)
{
    if (!root) return;
    
    Node *dest {nullptr}, *src_parent {nullptr};
    
    queue<Node *> q;
    for (q.push(root); !q.empty(); ) {
        root = q.front();
        q.pop();
        
        if (root->key == key) dest = root;
        
        if (root->left || root->right) {
            src_parent = root;
            if (root->left) q.push(root->left);
            if (root->right) q.push(root->right);
        }
    }
    
    if (dest && src_parent) {
        auto& src = (src_parent->right ? src_parent->right : src_parent->left);
        dest->key = src->key;
        delete src;
        src = nullptr;
    }
}
