// C/C++ program to print corner node at each level
// of binary tree
#include "leftmost-and-rightmost-nodes-of-binary-tree.h" //#include <bits/stdc++.h>
using namespace std;

/* A binary tree node has key, pointer to left
child and a pointer to right child */
struct Node
{
    int key;
    struct Node* left, *right;
};

/* To create a newNode of tree and return pointer */
struct Node* newNode(int key)
{
    Node* temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return (temp);
}

/* Function to print corner node at each level */
void printCorner(Node *root);

void insert(struct Node *root, int n1, int n2, char lr)
{
    if (root == NULL)
        return;
    if (root->key == n1)
    {
        switch (lr)
        {
        case 'L': root->left = newNode(n2);
            break;
        case 'R': root->right = newNode(n2);
            break;
        }
    }
    else
    {
        insert(root->left, n1, n2, lr);
        insert(root->right, n1, n2, lr);
    }
}
// Driver program to test above function
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        struct Node *root = NULL;
        while (n--)
        {
            char lr;
            int n1, n2;
            cin >> n1 >> n2;
            cin >> lr;
            if (root == NULL)
            {
                root = newNode(n1);
                switch (lr) {
                case 'L': root->left = newNode(n2);
                    break;
                case 'R': root->right = newNode(n2);
                    break;
                }
            }
            else
            {
                insert(root, n1, n2, lr);
            }
        }
        printCorner(root);
        cout << endl;
    }
    return 0;
}

namespace {
    constexpr auto debugTreeStructure = true;

    void printTree(const Node *root)
    {
        cout << "[ ";

        queue<const Node *> q;
        if (root != nullptr) q.push(root);

        while (!q.empty()) {
            root = q.front();
            q.pop();

            if (root->left != nullptr) {
                cout << root->key << ' ' << root->left->key << " L ";
                q.push(root->left);
            }

            if (root->right != nullptr) {
                cout << root->key << ' ' << root->right->key << " R ";
                q.push(root->right);
            }
        }

        cout << "]\n";
    }
}

/* Function to print corner node at each level */
void printCorner(Node *root)
{
    if (debugTreeStructure) printTree(root);
    if (root == nullptr) return;
    
    queue<const Node *> q;
    for (q.push(root); ; ) {
        auto width = q.size();
        
        switch (width) {
        case 0u:
            return;
            
        case 1u:
            cout << q.front()->key << ' ';
            break;
            
        default:
            cout << q.front()->key << ' ' << q.back()->key << ' ';
            break;
        }
        
        do {
            if (q.front()->left != nullptr) q.push(q.front()->left);
            if (q.front()->right != nullptr) q.push(q.front()->right);
            q.pop();
        }
        while (--width != 0u);
    }
}
