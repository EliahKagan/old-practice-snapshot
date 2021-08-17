/*
 A binary tree node has data, pointer to left child
   and a pointer to right child 
struct Node
{
    int data;
    Node* left;
    Node* right;
};
*/

namespace {
    enum class Side { left, right };
    
    inline void toggleSide(Side& side)
    {
        switch (side) {
        case Side::left:
            side = Side::right;
            break;
            
        case Side::right:
            side = Side::left;
            break;
        }
    }
}

/* Function to print nodes of extreme corners
of each level in alternate order */
void printExtremeNodes(Node* root)
{
    if (root == nullptr) throw invalid_argument{"tree is empty"};
    
    queue<Node*> q;
    q.push(root);
    
    for (auto side = Side::right; !q.empty(); toggleSide(side)) {
        if (side == Side::left) cout << q.front()->data << ' ';
        
        for (auto width = q.size(); width != 0; --width) {
            root = q.front();
            q.pop();
            
            if (root->left != nullptr) q.push(root->left);
            if (root->right != nullptr) q.push(root->right);
        }
        
        if (side == Side::right) cout << root->data << ' ';
    }
}
