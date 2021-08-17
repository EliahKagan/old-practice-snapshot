/* Tree node structure  used in the program
 struct Node
 {
     int data;
     Node* left, *right;
}; */

/*You are required to complete below method */
long long treePathsSum(Node *const root)
{
    using Dfs = function<void(const Node*, long long)>;
    
    if (root == nullptr) return 0LL;
    
    auto sum = 0LL;
    const Dfs dfs {[&sum, &dfs](const Node* const cur, long long acc) {
        static constexpr auto radix = 10;
        //for (auto data = cur->data; data != 0; data /= radix)
        //    acc = acc * radix + data % radix;
        acc = acc * radix + cur->data;
        
        if (cur->left != nullptr || cur->right != nullptr) {
            if (cur->left != nullptr) dfs(cur->left, acc);
            if (cur->right != nullptr) dfs(cur->right, acc);
        }
        else sum += acc;
    }};
    
    dfs(root, 0LL);
    return sum;
}
