/* A binary tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

/* Should return true if trees with roots as r1 and 
   r2 are identical */
bool isIdentical(Node *r1, Node *r2)
{
    if (r1 == nullptr) return r2 == nullptr;
    if (r2 == nullptr) return false;
    
    return r1->data == r2->data
            && isIdentical(r1->left, r2->left)
            && isIdentical(r1->right, r2->right);
}
