/* The Node structure is
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

/*You are required to complete this method*/
int minDepth(Node* root)
{
    if (root == nullptr) return 0;
    
    queue<Node*> q;
    q.push(root);
    
    for (auto depth = 1; ; ++depth) {
        for (auto width = q.size(); width != 0u; --width) {
            root = q.front();
            q.pop();
            
            const auto size = q.size();
            if (root->left != nullptr) q.push(root->left);
            if (root->right != nullptr) q.push(root->right);
            if (q.size() == size) return depth; // got leaf
        }
    }
}
