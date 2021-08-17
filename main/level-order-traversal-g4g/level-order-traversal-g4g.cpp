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
    for (q.push(node); !q.empty(); ) {
        node = q.front();
        q.pop();
        
        if (node == nullptr) continue;
        
        cout << node->data << ' ';
        
        q.push(node->left);
        q.push(node->right);
    }
}
