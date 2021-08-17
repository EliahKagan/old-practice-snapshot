/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/* The Node structure is
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

namespace {
    template<typename F>
    void dfs_each(Node *const root, const F action)
    {
        if (root) {
            dfs_each(root->left, action);
            action(root->data);
            dfs_each(root->right, action);
        }
    }
}

Node* binaryTreeToBST(Node* const root)
{
    vector<int> a;
    dfs_each(root, [&a](const int data) { a.push_back(data); });
    sort(begin(a), end(a));

    auto p = begin(a);
    dfs_each(root, [&p](int& data) { data = *p; ++p; });
    assert(p == end(a));

    return root;
}
