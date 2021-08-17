/* A binary tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

/*you are required to 
complete this function */
bool hasPathSum(Node *const node, const int sum)
{
    using Dfs = function<void(const Node*, int)>;
    
    if (node == nullptr) return false;
    
    unordered_set<int> path_sums;
    const Dfs dfs {[&path_sums, &dfs](const Node* const cur, int acc) {
        acc += cur->data;
        
        if (cur->left != nullptr || cur->right != nullptr) {
            if (cur->left != nullptr) dfs(cur->left, acc);
            if (cur->right != nullptr) dfs(cur->right, acc);
        }
        else path_sums.insert(acc);
    }};
    
    dfs(node, 0);
    return path_sums.find(sum) != path_sums.end();
}
