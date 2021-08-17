/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


/*Complete the function below
Node is as follows:
struct Node
{
    int data;
    Node *left, *right;
};
*/
namespace {
    void collapse(Node*& root)
    {
        while ((root->left == nullptr) != (root->right == nullptr)) {
            const auto old_root = root;
            root = (root->left ? root->left : root->right);
            delete old_root;
        }
    }

    void collapseAll(Node*& root)
    {
        if (root) {
            collapse(root);
            collapseAll(root->left);
            collapseAll(root->right);
        }
    }
}

Node *removeHalfNodes(Node *root)
{
    collapseAll(root);
    return root;
}
