/* The Node structure is
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

/*You are required to complete this function*/
int getLevelDiff(Node *root)
{
    queue<Node *> q;
    q.push(root);
    
    auto acc = 0;
    
    for (auto sign = 1; !q.empty(); sign = -sign) {
        for (auto width = q.size(); width != 0u; --width) {
            root = q.front();
            q.pop();
            
            if (root != nullptr) {
                acc += root->data * sign;
                q.push(root->left);
                q.push(root->right);
            }
        }
    }
    
    return acc;
}
