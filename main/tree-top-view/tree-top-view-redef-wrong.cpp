/*
class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

*/

    void topView(const Node* const root) const {
        map<int, int> tops;
        
        const function<void(int, const Node*)>
        dfs = [&tops, &dfs](const int column, const Node* const subroot) {
            if (!subroot) return;
            
            tops.emplace(column, subroot->data);
            dfs(column - 1, subroot->left);
            dfs(column + 1, subroot->right);
        };
        
        dfs(0, root);
        for (const auto kv : tops) std::cout << kv.second << ' ';
    }
