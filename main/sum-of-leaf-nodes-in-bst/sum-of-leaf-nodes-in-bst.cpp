/* The structure of Node
struct Node{
    int data;
    Node *left,*right;
}; */


/*You are required to complete below method */
int sumOfLeafNodes(Node *const root)
{
    if (root == nullptr) return 0;
    
    if (root->left == nullptr && root->right == nullptr) return root->data;
    
    return sumOfLeafNodes(root->left) + sumOfLeafNodes(root->right);
}
