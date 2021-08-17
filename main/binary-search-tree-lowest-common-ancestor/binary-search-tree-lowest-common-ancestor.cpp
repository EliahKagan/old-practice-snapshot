/*
Node is defined as 

typedef struct node
{
   int data;
   node * left;
   node * right;
}node;

*/

node * lca(node * root, const int v1, const int v2)
{
    while (root != nullptr && root->data != v1 && root->data != v2) {
        const auto next1 = (v1 < root->data ? root->left : root->right);
        const auto next2 = (v2 < root->data ? root->left : root->right);
        
        if (next1 != next2) break;
        
        root = next1;
    }
    
    return root;
}
