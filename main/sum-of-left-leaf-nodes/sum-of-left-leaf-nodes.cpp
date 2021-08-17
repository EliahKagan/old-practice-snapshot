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
// left leaf nodes
int leftLeafSum(Node* root)
{
    if (!root) return 0;

    if (root->left && !root->left->left && !root->left->right)
        return root->left->data + leftLeafSum(root->right);

    return leftLeafSum(root->left) + leftLeafSum(root->right);
}
