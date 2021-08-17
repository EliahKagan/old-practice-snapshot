/*  Tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

/*You are required to complete below method */
void pathCounts(Node *root)
{
    using Dfs = function<void(const Node*, int)>;
    assert(root != nullptr);
    
    map<int, int> counts; // length => count
    const Dfs dfs {[&counts, &dfs](const Node* const cur, const int len) {
        if (cur->left != nullptr || cur->right != nullptr) {
            if (cur->left != nullptr) dfs(cur->left, len + 1);
            if (cur->right != nullptr) dfs(cur->right, len + 1);
        }
        else ++counts[len];
    }};
    
    dfs(root, 1);
    for (const auto& kv : counts) cout << kv.first << ' ' << kv.second << " $";
}
