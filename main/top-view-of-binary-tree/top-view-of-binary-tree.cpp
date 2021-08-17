//Structure of binary tree
/*struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};*/

// function should print the topView of the binary tree
void topView(struct Node *root)
{
    if (!root) return;
    
    const auto print = [&root]() { cout << root->data << ' '; };
    
    queue<tuple<Node *, int>> q; // (node, position as offset from center)
    auto pos = 0;
    
    const auto emplace_children = [&root, &q, &pos]() {
        q.emplace(root->left, pos - 1);
        q.emplace(root->right, pos + 1);
    };
    
    print();
    emplace_children();
    
    for (auto ledge = 0, redge = 0; !q.empty(); ) {
        tie(root, pos) = q.front();
        q.pop();
        if (root == nullptr) continue;
        
        if (pos < ledge) {
            ledge = pos;
            print();
        }
        
        if (pos > redge) {
            redge = pos;
            print();
        }
        
        emplace_children();
    }
}
