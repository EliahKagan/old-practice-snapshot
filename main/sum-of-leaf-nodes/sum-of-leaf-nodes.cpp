/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Structure of the node of the binary tree is as
struct Node
{
	int data;
	Node *left, *right;
};*/
// function should return the sum of all the
// leaf nodes of the binary tree
int sumLeaf(Node* root)
{
    if (root == nullptr) return 0;

    if (root->left == nullptr && root->right == nullptr) return root->data;

    return sumLeaf(root->left) + sumLeaf(root->right);
}
