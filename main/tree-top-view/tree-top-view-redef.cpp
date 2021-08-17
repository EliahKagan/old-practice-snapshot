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
        if (!root) return;
        
        map<int, int> tops;
        queue<tuple<int, const Node*>> q;
        q.emplace(0, root);
        
        while (!q.empty()) {
            int column {};
            const Node* subroot {};
            tie(column, subroot) = q.front();
            q.pop();
            
            tops.emplace(column, subroot->data);
            if (subroot->left) q.emplace(column - 1, subroot->left);
            if (subroot->right) q.emplace(column + 1, subroot->right);
        }
        
        for (const auto kv : tops) std::cout << kv.second << ' ';
    }
