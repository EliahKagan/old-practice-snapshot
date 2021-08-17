/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Structure of the node of the binary tree is as
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
*/
// function should return the sum of all
// right leaf nodes
int rightLeafSum(Node* root)
{
    if (!root) return 0;

    if (root->right && !root->right->right && !root->right->left)
        return root->right->data + rightLeafSum(root->left);

    return rightLeafSum(root->right) + rightLeafSum(root->left);
}
