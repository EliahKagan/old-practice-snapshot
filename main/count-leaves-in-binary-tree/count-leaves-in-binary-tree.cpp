/* A binary tree node has data, pointer to left child
   and a pointer to right child  
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
}; */

/* Should return count of leaves. For example, return
    value should be 2 for following tree.
         10
      /      \ 
   20       30 */
int countLeaves(struct Node* root)
{
    if (root == nullptr) return 0;
    const auto n = countLeaves(root->left) + countLeaves(root->right);
    return n == 0 ? 1 : n;
}

