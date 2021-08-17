/*The Node structure is
struct Node {
int data;
Node * right, * left;
};*/

/*You are required to complete below method */
int maxDiff(Node *root, const int k) // Should be called minDiff!
{
    auto best_val = -1, best_diff = numeric_limits<int>::max();
    
    stack<Node *> s;
    for (s.push(root); !s.empty(); ) {
        root = s.top();
        s.pop();
        if (root == nullptr) continue;
        
        const auto diff = abs(root->data - k);
        if (diff < best_diff) {
            best_diff = diff;
            best_val = root->data;
        }
        
        s.push(root->left);
        s.push(root->right);
    }
    
    return best_val;
}
