/* The structure of the binary tree is as follows
struct Node
{
    int data;
    Node* left;
    Node* right;
};
*/

/*You are required to complete this method*/
bool check(Node* root)
{
    assert(root != nullptr);
    
    queue<Node*> q;
    q.push(root);
    
    for (auto got_leaf = false; !got_leaf; ) {
        for (auto width = q.size(); width != 0; --width) {
            root = q.front();
            q.pop();
            
            const auto size = q.size();
            if (root->left != nullptr) q.push(root->left);
            if (root->right != nullptr) q.push(root->right);
            if (q.size() == size) got_leaf = true;
        }
    }
    
    return q.empty();
}
