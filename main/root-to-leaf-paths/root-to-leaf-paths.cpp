/* Structure of Node
struct Node
{
    int data;
    Node* left;
    Node* right;
};*/

namespace {
    void printPaths(const Node* const root, const string& prefix)
    {
        if (root == nullptr) return;

        ostringstream out;
        out << prefix << root->data << ' ';
        const auto path = out.str();

        if (root->left == nullptr && root->right == nullptr)
            cout << path << '#';

        printPaths(root->left, path);
        printPaths(root->right, path);
    }
}

/* The function should print all the paths from root
 to leaf nodes of the binary tree */
void printPaths(Node* const root)
{
    printPaths(root, string{});
    cout << '\n';
}
