/* A binary tree node has data, pointer to left child
   and a pointer to right child /
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

void printKdistance(Node* root, int k)
{
    queue<Node*> q;
    for (q.push(root); !q.empty(); --k) {
        for (auto width = q.size(); width != 0u; --width) {
            root = q.front();
            q.pop();
            if (root == nullptr) continue;
            
            if (k == 0) cout << root->data << ' ';
            else {
                q.push(root->left);
                q.push(root->right);
            }
        }
    }
}
