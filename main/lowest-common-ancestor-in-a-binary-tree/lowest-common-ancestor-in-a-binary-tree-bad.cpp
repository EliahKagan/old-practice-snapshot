/* A binary tree node
struct Node
{
    int data;
    Node* left, * right;
}; */

namespace {
    // Peforms a breadth-first search, returning the node and its depth.
    tuple<const Node*, int> bfs(const Node* root, const int key)
    {
        queue<const Node*> q;
        q.push(root);
        
        for (auto depth = 0; !q.empty(); ++depth) {
            for (auto width = q.size(); width != 0u; --width) {
                root = q.front();
                q.pop();
                
                if (root != nullptr) {
                    if (root->data == key) return make_tuple(root, depth);
                    q.push(root->left);
                    q.push(root->right);
                }
            }
        }
        
        throw domain_error{"key not found"};
    }
}

Node* LCA(Node* const root, const int n1, const int n2)
{
    const Node* p1 {}, * p2 {};
    int d1 {}, d2 {};
    tie(p1, d1) = bfs(root, n1);
    tie(p2, d2) = bfs(root, n2);
    
    for (; d1 > d2; --d1) p1 = p1
}
