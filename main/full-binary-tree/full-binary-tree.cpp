/*Complete the function below
Node is as follows:
struct Node
{
    int key;
    struct Node *left, *right;
};
*/
bool isFullTree (struct Node* root)
{
    return !root || (!root->left == !root->right // root has 0 or 2 children
                     && isFullTree(root->left) && isFullTree(root->right));
}
