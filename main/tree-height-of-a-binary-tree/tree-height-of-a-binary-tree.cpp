/*The tree node has data, left child and right child 
struct node
{
    int data;
    node* left;
    node* right;
};

*/

int height(node * root)
{
    return root == nullptr
            ? -1
            : max(height(root->left), height(root->right)) + 1;
}
