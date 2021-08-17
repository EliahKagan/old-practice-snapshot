/*  Tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

namespace {
    constexpr auto bad = -1;
    
    int verifySums(const Node* const root)
    {
        if (root == nullptr) return 0;
        
        if (root->left == nullptr && root->right == nullptr) return root->data;
        
        const auto left = verifySums(root->left);
        if (left == bad) return bad;
        
        const auto right = verifySums(root->right);
        if (right == bad) return bad;
        
        return root->data == left + right ? root->data * 2 : bad;
    }
}

// Should return true if tree is Sum Tree, else false
bool isSumTree(Node* const root)
{
    return verifySums(root) != bad;
}
