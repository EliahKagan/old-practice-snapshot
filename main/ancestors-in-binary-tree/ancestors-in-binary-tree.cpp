
namespace {
    bool dfsPrint(const struct Node* const root, const int target)
    {
        if (root == nullptr) return false;
        if (root->data == target) return true;
        
        if (dfsPrint(root->left, target) || dfsPrint(root->right, target)) {
            cout << root->data << ' ';
            return true;
        }
        
        return false;
    }
}

/*
Structure of a node is as following
struct Node
{
     int data;
     struct Node* left;
     struct Node* right;
};
*/
// Function should print all the ancestor of the target node
bool printAncestors(struct Node *const root, const int target)
{
    const auto ret = dfsPrint(root, target);
    cout << '\n';
    return ret;
}
