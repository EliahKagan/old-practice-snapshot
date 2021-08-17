/*Complete the function below
Node is as follows:
struct Node{
	int data;
	Node *left,*right;
};
*/
int maxNodeLevel(Node *root)
{
    auto best_width = 0, best_level = 0;
    
    queue<Node *> q;
    if (root != nullptr) q.push(root);
    
    for (auto level = 0; !q.empty(); ++level) {
        auto width = q.size();
        if (width > best_width) {
            best_width = width;
            best_level = level;
        }
        
        for (; width != 0; --width) {
            root = q.front();
            q.pop();
            
            if (root->left != nullptr) q.push(root->left);
            if (root->right != nullptr) q.push(root->right);
        }
    }
    
    return best_level;
}
