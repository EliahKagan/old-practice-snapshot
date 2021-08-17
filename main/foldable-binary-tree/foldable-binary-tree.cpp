
namespace {
    bool isFoldable(const struct node *const left,
                    const struct node *const right)
    {
        if (left == nullptr) return right == nullptr;
        if (right == nullptr) return false;
        
        return isFoldable(left->left, right->right)
                && isFoldable(left->right, right->left);
    }
}

/* Returns true if the given tree is foldable */
bool isFoldable(struct node *root)
{
    return root == nullptr || isFoldable(root->left, root->right);
}
