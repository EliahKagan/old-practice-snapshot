/* Tree node structure  used in the program
 struct Node
 {
     int data;
     Node* left, *right;
}; */

/* Prints the nodes having no siblings.  */
void printSibling(Node* root)
{
    assert(root != nullptr);
    
    vector<int> found; // les enfants uniques :)
    
    stack<const Node*> s;
    for (s.push(root); !s.empty(); ) {
        const auto p = s.top();
        s.pop();
        
        const auto size = s.size();
        if (p->right != nullptr) s.push(p->right);
        if (p->left != nullptr) s.push(p->left);
        if (s.size() - size == 1u) found.push_back(s.top()->data);
    }
    
    sort(begin(found), end(found));
    for (const auto data : found) cout << data << ' ';
}
