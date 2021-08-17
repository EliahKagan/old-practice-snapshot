/* Tree node structure  used in the program
 struct Node
 {
     int data;
     struct Node* left;
     struct Node* right;
}; */

/* Computes the number of nodes in a tree. */
int getSize(struct Node* node)
{
    return node == nullptr
            ? 0
            : getSize(node->left) + getSize(node->right) + 1;
}

