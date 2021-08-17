namespace {
    template<class Compare>
    int findMin(const struct node* const root, const Compare comp)
    {
        auto acc = root->data;

        if (root->left != nullptr)
            acc = min(acc, findMin(root->left, comp), comp);

        if (root->right != nullptr)
            acc = min(acc, findMin(root->right, comp), comp);

        return acc;
    }
}

// Returns maximum value in a given Binary Tree
int findMax(struct node* root)
{
    return findMin(root, greater<int>{});
}

// Returns minimum value in a given Binary Tree
int findMin(struct node* root)
{
    return findMin(root, less<int>{});
}
