/*
Please note that it's Function problem i.e.
you need to write your solution in the form Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


// Method to find next right of given key (key), it returns NULL if key is
// not present in tree or key is the rightmost node of its level
node* nextRight(node *root, const int key)
{
    if (root == nullptr) return nullptr;
    
    queue<node*> q;
    for (q.push(root); !q.empty(); ) {
        for (auto width = q.size(); width != 0u; --width) {
            root = q.front();
            q.pop();
            
            if (root->key == key) return width == 1 ? nullptr : q.front();
            
            if (root->left != nullptr) q.push(root->left);
            if (root->right != nullptr) q.push(root->right);
        }
    }
    
    return nullptr;
}
