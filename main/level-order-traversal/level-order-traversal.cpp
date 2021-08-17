/* A binary tree Node
struct Node
{
    int data;
    Node* left, * right;
}; */

//You are required to complete this method
void levelOrder(Node* node)
{
    queue<Node*> q;
    q.push(node);
    
    while (!q.empty()) {
        auto occupied = false; // records if the current level has any nodes
        
        for (auto width = q.size(); width != 0u; --width) {
            node = q.front();
            q.pop();
            if (node == nullptr) continue;
            
            occupied = true;
            cout << node->data << ' ';
            
            q.push(node->left);
            q.push(node->right);
        }
        
        if (occupied) cout << "$ ";
    }
}
