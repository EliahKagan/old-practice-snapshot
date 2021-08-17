/* struct Node
{
  int data;
  Node *left,  *right;
  Node *nextRight;  // This has garbage value in input trees
}; */

// Should set the nextRight for all nodes
void connect(Node *root)
{
    if (root == nullptr) return;
    
    queue<Node *> q;
    for (q.push(root); !q.empty(); ) {
        for (auto width = q.size(); width != 0u; --width) {
            root = q.front();
            q.pop();
            root->nextRight = (width == 1u ? nullptr : q.front());
            
            if (root->left != nullptr) q.push(root->left);
            if (root->right != nullptr) q.push(root->right);
        }
    }
}
