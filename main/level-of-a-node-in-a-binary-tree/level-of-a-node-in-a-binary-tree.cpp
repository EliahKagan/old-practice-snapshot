/*
Structure of the node of the binary tree is
struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
};
*/
// function should return level of the target node
int getLevel(struct Node *node, const int target)
{
    queue<Node *> q;
    q.push(node);
    
    for (auto level = 1; !q.empty(); ++level) {
        for (auto width = q.size(); width != 0u; --width) {
            node = q.front();
            q.pop();
            
            if (node != nullptr) {
                if (node->data == target) return level;
                
                q.push(node->left);
                q.push(node->right);
            }
        }
    }
    
    return 0;
}
