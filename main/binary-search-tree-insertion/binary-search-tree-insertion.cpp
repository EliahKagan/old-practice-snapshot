/*
Node is defined as 

typedef struct node
{
   int data;
   node * left;
   node * right;
}node;

*/


node * insert(node * const root, const int value)
{
    const auto leaf = new node{value, nullptr, nullptr};
    
    if (root == nullptr) return leaf;
    
    for (auto cur = root; ; ) {
        if (value < cur->data) {
            if (cur->left == nullptr) {
                cur->left = leaf;
                break;
            }
            
            cur = cur->left;
        } else {
            if (cur->right == nullptr) {
                cur->right = leaf;
                break;
            }
            
            cur = cur->right;
        }
    }
    
    return root;
}
