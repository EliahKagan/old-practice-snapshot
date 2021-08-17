/*
Structure of the node of the tree is as
struct Node
{
	int key;
	struct Node* left, *right;
};
*/

namespace {
    bool isSymmetric(const struct Node* const left,
                     const struct Node* const right)
    {
        if (left == nullptr) return right == nullptr;
        
        if (right == nullptr || left->key != right->key) return false;
        
        return isSymmetric(left->left, right->right)
                && isSymmetric(left->right, right->left);
    }
}

// complete this function
// return true/false if the is Symmetric or not
bool isSymmetric(struct Node* const root)
{
    return root == nullptr || isSymmetric(root->left, root->right);
}
