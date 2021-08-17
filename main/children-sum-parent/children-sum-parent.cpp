/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below
Node is as follows:
struct Node{
	int data;
	Node *left,*right;
};
*/
int isSumProperty(Node *node)
{
    if (!node || !(node->left || node->right)) return true;

    auto diff = node->data;
    if (node->left) diff -= node->left->data;
    if (node->right) diff -= node->right->data;

    return diff == 0 && isSumProperty(node->left)
                     && isSumProperty(node->right);
}
